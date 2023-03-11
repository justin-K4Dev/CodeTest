-- cpp_meta.lua
-- (c) David Manura, 2007-02.
-- Licensed under the same terms as Lua itself.

module("cpp_meta", package.seeall)

function import()
    local env = getfenv(2)
    for k,v in pairs(cppmeta) do env[k] = v end
    return cppmeta
end

-- remove leading indents from string
local function unindent(s)
    local spacer = string.match(s, "( *)}%s*$")
    local t = {}
    string.gsub(s, "[^\n]+", function(s) t[#t+1] = s; return "" end)
    for i = 1,#t do
        t[i] = string.gsub(t[i], "^" .. spacer, "")
    end
    s = table.concat(t, "\n")
    return s
end

-- substitute variables in string
function subst(s, vars)
    for k,v in pairs(vars) do
        s = string.gsub(s, "%%%(" .. k .. "%)", v)
    end
    return s
end

-- remove whitespace at beginning and end of string
local function trim(s)
    s = string.gsub(s, "^%s+", "")
    s = string.gsub(s, "%s+$", "")
    return s
end

-- extracts leading C comment (if any) from string.
local function remove_comment(ccode)
    local comment
    ccode = string.gsub(ccode, "^%s*/%*(.-)%*/%s*",
    function(s) comment = s; return "" end)
    return ccode, comment
end

-- format function definition
local function format_funcdef(func, parent)
    -- Remove default assignments from arguments
    local args = func.args
    args = string.gsub(args, "%s*=[^,)]+", "")

    local body = func.body
    if string.sub(body, 1, 1) == "{" then body = " " .. body end

    local mods = (func.mods == "") and "" or " " .. func.mods 

    local prefix = parent and (parent .. "::") or ""

    local cfunc = "  " .. func.type .. "\n"
    .. prefix .. func.name .. "(" .. args .. ")" .. mods
    .. body .. "\n"

    return cfunc  
end

-- parse function from C++ string.
local function parse_func(ccode)
    local comment
    ccode, comment = remove_comment(ccode)
    ccode = unindent(ccode)
    local type, name, args, mods, body
    = string.match(ccode, "^%s*([^(]+)%s+([%w_]+)%s*%((.*)%)%s*([^{]-)%s*({.*})")
    assert(type, ccode)
    --print("F", type,";",name, ";",args, ";",body)
    local func = {name = name, args = args, type = type, mods = mods,
        body = body, comment = comment}
    return func
end

-- parse property from C++ string
local function parse_property(ccode)
    ccode = trim(ccode)
    local type, name, default
    = string.match(ccode, "^%s*(.+)%s+([%w_]+)%s*=%s*(.-)%s*$")
    --print('P', type, ';', name, ';', default)
    assert(type, ccode)
    local prop = {name = name, type = type, default = default}
    return prop
end

-- parse "include" from C++ string
local function parse_include(ccode)
    ccode = trim(ccode)
    local ccode2 = string.gsub(ccode, "^%s*public%s+", "")
    local visibility = (ccode2 ~= ccode) and "public" or "private"
    local include = {ccode2, visibility = visibility}
    return include
end

Class = {}
Class.__index = Class
setmetatable(Class, {__call = function(self, ...) return Class.new(...) end})
-- Construct class.
function Class.new(name)
    return setmetatable({
        name = name,
        properties = {},
        funcs = {},
        includes = {}
    }, Class)
end
-- Use property in class.
function Class:property(ccode)
    local prop = parse_property(ccode)
    table.insert(self.properties, prop)
    return self
end
-- Use (member) function in class.
function Class:func(ccode)
    local func = parse_func(ccode)
    table.insert(self.funcs, func)
    return self
end
-- Use include in class.
function Class:include(ccode)
    local include = parse_include(ccode)
    table.insert(self.includes, include)
    return self
end
-- Return string of C++ code for class declaration.
function Class:declaration()
    local cfields = ""
    for _,prop in ipairs(self.properties) do
        local cfield = "  %type %name;\n"
        cfield = string.gsub(cfield, "%%type", prop.type)
        cfield = string.gsub(cfield, "%%name", prop.name)
        cfields = cfields .. cfield
    end

    local cpubs = ""
    for _,prop in ipairs(self.properties) do
        local cfield =
        "  %type get_%name() const { return %name; }\n" ..
        "  void set_%name(%type _) { %name = _; }\n"
        cfield = string.gsub(cfield, "%%type", prop.type)
        cfield = string.gsub(cfield, "%%name", prop.name)
        cpubs = cpubs .. cfield
    end

    for _,func in ipairs(self.funcs) do
        local mods = (func.mods == "") and "" or " " .. func.mods
        local cfunc = "  " .. func.type .. " " .. func.name .. "(" .. func.args .. ")" .. mods .. ";\n"
        cpubs  = cpubs .. cfunc
    end

    local c = subst([[
class %(name) {
public:
  %(name)::%(name)();
  explicit %(name)::%(name)(const %(name) & other);
  %(name) & operator=(const %(name) & other);
%(cpubs)
private:
%(cfields)
};
]], {name = self.name, cpubs = cpubs, cfields = cfields})
    return c
end
-- Return string of C++ code for class implementation.
function Class:implementation()
    local cinit = ""
    if #self.properties > 0 then
        for _,prop in ipairs(self.properties) do
            cinit = cinit .. ", " .. prop.name .. "(" .. prop.default .. ")"
        end
        cinit = ":" .. string.sub(cinit, 2)
    end

    local cinit3 = ""
    if #self.properties > 0 then
        for _,prop in ipairs(self.properties) do
            cinit3 = cinit3 .. ", " .. prop.name .. "(other." .. prop.name .. ")"
        end
        cinit3 = ":" .. string.sub(cinit3, 2)
    end

    local cassigninit = ""
    if #self.properties > 0 then
        for _,prop in ipairs(self.properties) do
            cassigninit = cassigninit .. "  " .. prop.name .. " = other." .. prop.name .. ";\n"
        end
    end

    local cfuncs = ""
    for _,func in ipairs(self.funcs) do
        local cfunc = format_funcdef(func, self.name)
        cfuncs  = cfuncs .. cfunc
    end

    local c = subst([[
%(name)::%(name)() %(cinit)
{
}
%(name)::%(name)(const %(name) & other) %(cinit3)
{
}
  %(name) &
%(name)::operator=(const %(name) & other) {
%(cassigninit)
}
%(cfuncs)
]], {cinit3 = cinit3, cassigninit = cassigninit, cinit = cinit,
        name = self.name, cfuncs = cfuncs})
    return c
end

Module = {}
Module.__index = Module
setmetatable(Module, {__call = function(self, ...) return Module.new(...) end})
-- Construct module.
function Module.new(name)
    return setmetatable({
        name = name,
        includes = {},
        using_namespaces = {},
        classes = {},
        funcs = {}
    }, Module)
end
-- Use include in module.
function Module:include(ccode)
    local include = parse_include(ccode)
    table.insert(self.includes, include)
    return self
end
-- Use namespace in module.
function Module:using_namespace(name)
    name = trim(name)
    table.insert(self.using_namespaces, name)
    return self
end
-- Define class in module.
function Module:class(o)
    table.insert(self.classes, o)
    return self
end
-- Define function in module.
function Module:func(ccode)
    local func = parse_func(ccode)
    table.insert(self.funcs, func)
    return self
end
-- Return srting of C++ code for module header.
function Module:header()
    local cincludes = ""
    local includes = {}
    for _,v in ipairs(includes) do includes[#includes+1] = v end
    for _,class in ipairs(self.classes) do
        for _,v in ipairs(class.includes) do includes[#includes+1] = v end
    end
    local found = {}
    for _,v in ipairs(includes) do
        if v.visibility == "public" and not found[v[1]] then
            cincludes = cincludes .. "#include " .. v[1] .. "\n"
            found[v[1]] = true
        end
    end

    local cclassdecs = ""
    for _,class in ipairs(self.classes) do
        cclassdecs = cclassdecs .. class:declaration()
    end

    local c = subst([[
#ifndef MODULE_%(name)
#define MODULE_%(name)
%(cincludes)
%(cclassdecs)
#endif // first include
]], {name = self.name, cincludes = cincludes, cclassdecs = cclassdecs})
    return c
end

-- Return string of C++ code for module implementation.
function Module:implementation()
    local cincludes = ""
    local found = {}
    for _,class in ipairs(self.classes) do
        local includes = class.includes
        for _,v in ipairs(includes) do
            if v.visibility == "private" and not found[v[1]] then
                cincludes = cincludes .. "#include " .. v[1] .. "\n"
                found[v[1]] = true
            end
        end
    end

    local cusings = ""
    for _,ns in ipairs(self.using_namespaces) do
        cusings = cusings .. "using namespace " .. ns .. ";\n";
    end

    local cdefs = ""
    for _,class in ipairs(self.classes) do
        cdefs = cdefs .. class:implementation() .. "\n"
    end

    local cfuncs = ""
    for _,func in ipairs(self.funcs) do
        local cfunc = format_funcdef(func)
        cfuncs  = cfuncs .. cfunc
    end

    local c = subst([[
#include "%(name).h"
%(cincludes)
%(cusings)
%(cdefs)
%(cfuncdefs)
]], {name = self.name, cdefs = cdefs, cincludes = cincludes,
        cfuncdefs = cfuncs, cusings = cusings})

    return c
end

-- Write module sources to files.
function Module:write()
    local fh = assert(io.open(self.name .. ".h", "w"))
    fh:write(self:header())
    fh:close()
    local fh = assert(io.open(self.name .. ".cpp", "w"))
    fh:write(self:implementation())
    fh:close()
end



-- Insert into any class a member function returning class name.
-- This is a helper function, achieving aspect oriented programming somewhat.
function name_class(class)
    local ccode = cppmeta.subst([[
    /* Return name of class as string. */
    std::string get_class_name() { return "%(name)"; }
  ]], {name = class.name})
    class:func(ccode):include("public <string>")
    return c
end


-- Generate cpp class
function generate_class(class, compilation_unit)

    name_class(class) -- add other functions to class.

    compilation_unit:write() -- generate source files for C++ compiler.

    -- Just for fun, print out a list of method names and descriptions too.
    for _,v in ipairs(class.funcs) do
        print(v.name, v.comment)
    end

end