--[[
	Lua 5.1 was released near the start of 2006, so is now more than four years old.
	Hence the time is coming for an updated version, which will be 5.2.
	Yesterday, the Lua team released Lua 5.2,
	which is a snapshot of the current state of their internal 5.2 repository.
	This means that 5.2 is not a release candidate, and everything can still change
	(for example, environments have changed a lot since 5.2),
	but we can expect that many of the changes in 5.2 will make it into the final release of Lua 5.2.
	Hence it is useful to identify all of the changes between 5.1 and 5.2
	so that we can have a relatively good idea of the changes which 5.2 will bring.
--]]

--[[
	1. New model for environments / global variables
--]]

--[[
	In Lua 5.1, every closure (function) had an associated environment table.
	This table was used for every read/write to a global variable from within the function,
	and the table could be changed at runtime using setfenv / getfenv:
--]]

--[[
-- Lua 5.1
x = 3
function print_x() print(x) end
print_x() --> 3
setfenv(print_x, {print = print, x = 4})
print_x() --> 4
print(getfenv(print_x).x) --> 4
--]]

--[[
	In Lua 5.2, this environment table is gone.
	Instead, globals are resolved in a special upvalue called _ENV,
	and every piece of code loaded (even if it doesn't access any globals)
	is done so in the context of an upvalue called _ENV,
	which is initialised to the value of the globals table
	(LUA_RIDX_GLOBALS in the registry, see later) at the time of the loading.
	This means that code like the following works:
--]]

-- Lua 5.2
do
  local outer = _ENV
  local _ENV = {}
  function outer.set_x(value) x = value end
  function outer.get_x() return x end
  function outer.set_inner_env(e) _ENV = e end
end
set_x(5)
print(x) --> nil
print(get_x()) --> 5
set_inner_env{x = 10}
print(get_x()) --> 10

--[[
	Note that _ENV behaves like a shared upvalue,
	which is different to how setfenv/getfenv used to work, and different to _G.
	Specifically, all functions within a chunk (a piece of loaded code)
	share the same environment unless they specifically redeclare a local called _ENV,
	so setting the environment of one of them (e.g. with debug.setupvalue) will affect all of them.
	The global variable _G is still present,
	and the initial value of _G is the same as the initial value of _ENV,
	but changing one has no effect on the other, though as _G is a global,
	it really means _ENV._G in 5.2,
	so changing _ENV to something without a _G field will make _G evaluate to nil.
	Also note that as an upvalue, _ENV can take any type of value, not just a table.
	Hence the following can be done:
--]]

-- Lua 5.2
local print = print
do
  local _ENV = "some string"
  print(gsub) --> function (string.gsub)
end
do
  local _ENV = nil
  print(io) --> Error: attempt to index _ENV (a nil value)
end

--[[
	For consistency, C functions don't have environment either,
	and are recommended to use a (shared) table upvalue where they used to use environments.
	Also note that the in env do ...
	end construct present in earlier work versions of Lua 5.2 is not present in work3.
	Addendum: Another nice idiom presented by LHF is to have a function,
	one of whose parameters is called _ENV,
	hence allowing the environment to be provided at call-time.
--]]

--[[
	2. Coroutines can yield in many more places
--]]

--[[
	In Lua 5.1, a coroutine (Lua thread) couldn't yield across a C call boundary,
	unless a modification like Coco was used.
	Lua 5.2 introduces three new functions to the C API:
		lua_callk, lua_pcallk, and lua_yieldk.
	These functions behave similarly to their existing non-k counterparts,
	except that they take a continuation function as a parameter,
	which allows coroutines to yield over them,
	with execution subsequently resuming in the continuation function.
	Many of the standard library functions have been changed to use these new API functions,
	including dofile, pcall, table.foreach, table.foreachi, and xpcall.
	For example, the following code now works:
--]]

-- Lua 5.2
F = coroutine.wrap(function(...)
  return pcall(function(...)
    return coroutine.yield(...)
  end, ...)
end)
print(F("Hello")) --> Hello (in 5.1, gives: false  attempt to yield across metamethod/C-call boundary)
print(F("World")) --> true  World

--[[
	Also changed in 5.2 is that coroutines can yield across metamethod calls
	(as long as the metamethod wasn't invoked by unsuspecting C code),
	as in the following example:
--]]

-- Lua 5.2
F = coroutine.wrap(function()
  while true do
    local t = setmetatable({}, {
      __eq = function(...)
        return coroutine.yield(...)
      end}
    )
    local t2 = setmetatable({}, getmetatable(t))
    print("Are they equal?", t == t2)
  end
end)
print(F()) --> table, table (In 5.1, gives error: attempt to yield across metamethod/C-call boundary)
F(true) --> Are they equal? true
F(false) --> Are they equal? false

--[[
	Note that there is also a new API function called lua_getctx,
	which is useful when implementing continuation functions.
--]]

--[[
	3. Userdata environments can be nil
--]]
--[[
	In Lua 5.1, userdata environments (just like function environments) had to be some table,
	and when a userdata was created, its environment was initialised to that of the calling C function.
	In Lua 5.2, userdata environments can be a table, or can be nil,
	and their initial value is nil.
--]]


New bit operations library - Lua 5.2-work3 adds a new standard library called bit, which contains bit.band, bit.bnot, bit.bor, bit.rol, bit.ror, bit.lshift, bit.rshift, bit.btest, and bit.bxor. All of these functions operate on numbers as if they were 32-bit unsigned integers. Note that the b prefix on the names is due to and, not, and or being keywords in Lua.
Note: The above function list was incorrect in the original post.
Coroutines can start in a C function - In Lua 5.2-work3, a coroutine can have a C function as its entry point, meaning that the following Lua 5.1 code:
-- Lua 5.1
function Lua_print(...) return print(...) end
coroutine.wrap(Lua_print)("Hello") --> Hello
Can be simplified to just:

-- Lua 5.2-work3
coroutine.wrap(print)("Hello") --> Hello
New light-C-function type - With the abolition of function environments, a C function with no upvalues doesn't have any state other than the function pointer. Hence in 5.2-work3, there is a new type called the light C function, which is just a function pointer (in the same way as light userdata is just a void pointer). This change isn't visible in the C API - lua_type will still return LUA_TFUNCTION, and lua_iscfunction will still return 1, but it does have effects in certain areas. In terms of creation, a light C function is created when you call lua_pushcfunction, or when you call lua_pushcclosure with a zero upvalue count, and a normal C function (C closure) is created when you call lua_pushcclosure with a non-zero upvalue count. One benefit of this change is that pushing a light C function onto the stack will never throw an error in 5.2-work3 (whereas in 5.1, creating the closure structure could throw a memory error). One side effect of this change is that light C functions compare equal under function pointer equality, so the following code has different behaviour in 5.2-work3 as compared to 5.1:
static int some_function(lua_State *L) {
  lua_pushcfunction(L, some_function);
  lua_pushcfunction(L, some_function);
  lua_pushboolean(L, lua_equal(L, -1, -2)); /* true in 5.2-work3, false in 5.1 */
  return 1;
}
Another side effect of this change is that light C functions behave like strong values when placed in weak tables, so the following code behaves differently:

weak = setmetatable({}, {__mode = "v"})
weak.f = select
select = nil
collectgarbage()
print(weak.f) --> function in 5.2-work3, nil in 5.1
Ephemeron tables - In Lua 5.1, cycles in weak tables could result in unintended behaviour as things didn't get garbage collected even if the only reference to an object was through the weak reference. The following example is typical of this:
weak = setmetatable({}, {__mode = "k"})
t = {}
weak[t] = {self_reference = t}
t = nil
collectgarbage()
print(next(weak)) --> table, table in Lua 5.1, nil in Lua 5.2-work3
In Lua 5.2-work3, tables with weak keys and strong values (as in the above example) as treated as ephemeron tables, and references to a weak key which come from the associated value do not count as a reference in the eyes of the garbage collector any more.

(lua_|debug.)[sg]etfenv renamed - As a consequence of functions no longer having environments, the lua_getfenv, lua_setfenv, debug.getfenv, and debug.setfenv functions have all lost the letter f from their names in 5.2-work3. Obviously their behaviour has also changed - they only work on userdata (i.e. not functions or threads), and they can be passed / return the value nil.
[sg]etfenv deprecated - Another consequence of functions no longer having environments is that the global functions setfenv and getfenv no longer make any sense in 5.2-work3. They still exist, but calling them just results in an error stating that they are deprecated.
loadin function - A common pattern in Lua 5.1 was to load a chunk, assign it an environment, and then run it. As 5.2-work3 has deprecated setfenv, this can no longer be done. Instead, a new function called loadin is provided, which behaves like load (though note that load has also changed slightly, see later) with the addition of an environment parameter:
loadin(env, chunk [, source [, mode]])
New escape sequences in strings - Two new escape sequences are recognised in (non-long) strings in 5.2-work3. The first of these is hexadecimal character escapes, so that "\xFF" functions as it does in C, and also a slightly stranger escape sequence "\*" skips all following whitespace. For example:
-- Lua 5.2-work3
print("\x48ello \*     
               World") --> Hello World
lua_cpcall removed - Lua 5.1 had a function called lua_cpcall in its API. The purpose of this function is very subtle, as it initially looks similar to calling lua_checkstack, lua_pushcfunction, lua_pushlightuserdata, and lua_pcall (in that order). The difference is that lua_cpcall could never throw any errors, whereas in 5.1, lua_checkstack and lua_pushcfunction could both cause errors. Due to light C functions in 5.2-work3, lua_pushcfunction can no longer throw an error, and lua_checkstack has been changed so that it doesn't either. Hence the subtle purpose of lua_cpcall is no longer required, and so it has been removed.
Identifiers can no longer use locale-dependent characters - In Lua 5.1, the standard ctype functions like isalpha were used by the lexer when parsing identifiers and the like. This allowed for locale-dependent characters to be used in identifiers, perhaps even unicode identifiers. In Lua 5.2-work3, there are internal versions of all the used ctype functions, which are no longer dependent upon locale. This means that if a script compiles at one location, it'll compile everywhere else, regardless of differences in locale.
Generational and emergency garbage collection - As well as gaining ephemeron tables, the garbage collector has two other upgrades in 5.2-work3. Firstly there is emergency garbage collection, which causes a garbage collection cycle to happen when an allocation fails, which hopefully frees enough memory to allow the allocation to subsequently succeed. The second, much more experimental, upgrade is generational garbage collection. This is based around the idea that objects recently created are more likely to become garbage than objects which have been around for a while. In theory these two upgrades should result in better behaviour in low-memory systems, and better performance generally. There is also a new status code called LUA_ERRGCMM which can be returned from functions like lua_pcall to indicate that an error occured while executing a __gc metamethod.
Addendum: Note that the experimental generational collector is not enabled by default, nor it is incremental at the current point in time. The information on LUA_ERRGCMM was also incorrect originally.
Order metamethods allowed between different types - In Lua 5.1, the __lt and __le metamethods could only be used to compare two things with the same metamethod. In Lua 5.2-work3, this has been changed to work in a similar way to arithmetic metamethods, so that the following code now works:
-- Lua 5.2-work3
print(setmetatable({}, {__lt = function() return true end}) < 5) --> true
Userdata finalisers must be present when metatable is set - In Lua 5.1, if a userdata had a __gc metamethod at garbage collection time, then that metamethod was called. In 5.2-work3, a __gc field must be present on the metatable when the metatable is assigned to the userdata in order for the userdata's __gc metamethod to be called at garbage collection time. The reason for this might be for efficiency, or it might be to pave the way in future for tables to have __gc metamethods with the same semantics. Either way, this means that the following code no longer does what it did in 5.1:
-- Lua 5.1
ud = newproxy()
require"debug".setmetatable(ud, {})
require"debug".getmetatable(ud).__gc = print
ud = nil
collectgarbage() --> userdata
Addendum: Relevant mailing list thread from February 2008: when do programs set metatable?
Note further that a subtle implication of this change is that the order in which userdata finalisers are called has changed - in Lua 5.1 they were called in the reverse order of construction, whereas in 5.2-work3 they're called in the reverse order of metatable assignment:

A = newproxy()
B = newproxy()
C = newproxy()
require"debug".setmetatable(C, {__gc = function() print "C" end})
require"debug".setmetatable(A, {__gc = function() print "A" end})
require"debug".setmetatable(B, {__gc = function() print "B" end})
A, B, C = nil
collectgarbage() --> CBA in 5.1, BAC in 5.2-work3
luaL_openlib un-deprecated - The luaL_openlib function was present in earlier versions of Lua, and did a similar task to luaL_register while also setting upvalues on each registered function. Lua 5.1 deprecated luaL_openlib, and 5.2-work3 has reinstated it as a proper function in wake of upvalues being the replacement for C function environments.
lua_arith function - Replicating the behaviour of Lua's arithmetic operations using 5.1's C API was possible, but it was a slightly arduous task to get the semantics just right. 5.2-work3 introduces a new function called lua_arith which can be used to perform arithmetic operations in C in the exact same way they're done in Lua.
ipairs, table.maxn, and math.log10 all deprecated - Though the reasons for deprecation are not stated, I'd guess that table.maxn was deprecated as the the length operator makes more sense in most situations and it can be implemented in pure Lua. I'd guess that math.log10 was deprecated as its functionality can be achieved using math.log, and even more so in 5.2-work3, as math.log takes the base as an optional second parameter. The deprecation of ipairs is slightly more surprising, but perhaps the rationale is that having two types of built-in iterator is confusing, or that ipairs is much slower than a numeric for-loop. Note that even with deprecation of ipairs disabled, the behaviour of ipairs differs in 5.2-work3 from that of 5.1; specifically, it queries the length operator when it encounters a nil, and it honours the __ipairs metamethod in 5.2-work3, whereas it went up to the first nil in 5.1.
Note: The above paragraph was slightly incorrect in the original blog post with regards to __len.
Higher limit on size of a function's constant table - One implementation detail of Lua which people sometimes run into is a limit on the number of constants which any individual function can use. This is mainly due to the bytecode used; in Lua 5.1 the largest field within any single instruction was the Bx field at 18 bits wide, whereas Lua 5.2-work3 introduces a new kind of instruction called Ax (used by the new OP_EXTRAARG instruction) which has a massive 26 bit field. This means that any individual function can use upto 2^26-1 different constants rather than the prior limit of 2^18-1:
t = {}
for i = 1, 2^18 do
  t[i] = i .. ", "
end
print(loadstring("return {" .. table.concat(t) .. "}")) --> Error in 5.1, function in 5.2-work3
package.searchpath function - Lua 5.2-work3 introduces a new function called package.searchpath, which scans a list of paths for a file in a similar manner to the require function. This may be useful for packages which contain non-Lua files which they need to find.
Parameters to io.[p]open and os.date are now sanitised - Due to the C specification allowing any behaviour (including crashing) when invalid mode strings are passed to it, Lua 5.2-work3 now checks the mode parameter of io.open and io.popen to ensure that it matches against "[rwa]%+?b?", and also does a more complex check of the format parameter being passed to strftime.
os.exit can now close the state cleanly - The os.exit function has gained an extra parameter in 5.2-work3, which controls whether or not os.exit will cleanly close the Lua state before exiting, whereas in 5.1 it never cleaned up. Hence you can get userdata finalisers to be called when you call os.exit:
-- Lua 5.2-work3
getmetatable(newproxy(true)).__gc = print
os.exit(0, true) --> userdata
LUA_ENVIRONINDEX and LUA_GLOBALSINDEX removed - Yet another consequence of changing function environments is that the C pseudo-index LUA_ENVIRONINDEX doesn't make sense. Hence it is no longer present in 5.2-work3, and at the same time, LUA_GLOBALSINDEX is also gone (though LUA_RIDX_GLOBALS has been added, see later). This means that the only pseudo-indices remaining are LUA_REGISTRYINDEX and lua_upvalueindex(i). This might make it slightly faster to use the remaining pseudo-indices, as the Lua core doesn't have to check for the removed ones.
LUA_RIDX_MAINTHREAD and LUA_RIDX_GLOBALS added - With the cleaning up of pseudo-indices, LUA_GLOBALSINDEX was removed. In place of it is the new value LUA_RIDX_GLOBALS, which is integer key in the registry table of the default globals table, usage of which typically looks like (this is actually the new lua_pushglobaltable macro):
/* Lua 5.2-work3 */
lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
Note that as previously mentioned, LUA_RIDX_GLOBALS is slightly special - whenever a chunk is loaded, its _ENV upvalue is initialised to the current value of registry[LUA_RIDX_GLOBALS]. Also added is LUA_RIDX_MAINTHREAD, which when looked up in the registry gives the main thread of the Lua state. This can be useful in some circumstances, like for getting a non-garbage-collectable lua_State* for performing callbacks on. Note that user code is free to overwrite these indices in the registry, but doing so may cause strange behaviour in other user code which expects them to be present.

String patterns can contain embedded NULs - In Lua 5.1, string patterns (as used by string.gsub, string.match, etc.) couldn't contain embedded "\0" characters, and the "%z" pattern had to be used instead. As of 5.2-work3, embedded NUL characters are now handled correctly, and "%z" is now deprecated. Hence the slight change in behaviour:
print(select(2, ("p\0p"):gsub("%z[p]",""))) --> 1 in 5.1, 1 in 5.2-work3
print(select(2, ("p\0p"):gsub("\0[p]",""))) --> 4 in 5.1, 1 in 5.2-work3
Another related change is that the replacement parameter to string.gsub no longer accepts invalid replacements:

-- Lua 5.2-work3
print(("Jello"):gsub("J","%H")) --> Error
Changed length functions in the C API - lua_objlen has become lua_rawlen with a very slight change in behaviour, lua_len and luaL_len have been addded. The length function(s) changed between Lua 5.0 and 5.1, and they've changed again between 5.1 and 5.2-work3. What used to be called lua_objlen in 5.1 was been renamed to lua_rawlen, with the only difference in behaviour being that lua_rawlen no longer calculates the length of a number by taking the string representation of it; it just returns zero. The new lua_len function behaves exactly like the length operator in Lua code, and the new luaL_len function behaves in a similar way but returns the result as an integer rather than on the stack (and throws an error if the length is not a number).
Enhanced debug API - There are two new functions in 5.2-work3's C API called lua_upvalueid and lua_upvaluejoin (debug.upvalueid and debug.upvaluejoin in Lua). These allow you to detect when two Lua functions are sharing an upvalue and allow you to force two Lua functions to share an upvalue. This should allow for better debugging, and might also permit interesting things like compiling a chunk in the lexical context of another by giving the second chunk dummy locals and then joining them against the original chunk. The (lua_|debug.)getinfo function has also had an upgrade; there is a new "t" option which fills in a field called istailcall, and the existing "u" option now also fills in two fields called nparams and isvararg. Another change to the debug API is that the "tail return" hook has been replaced by a "tail call" hook. Addendum: A non-obvious application of lua_upvaluejoin is that it can also unjoin (split) upvalues by joining an existing upvalue against a freshly created dummy upvalue, as in the following example:
-- Lua 5.2-work3
require "debug"
function upvalue_split(f, n)
  local dummy
  do
    local name, value = debug.getupvalue(f, n)
    dummy = function() return value end
  end
  debug.upvaluejoin(f, n, dummy, 1)
end
do local x = 42 function get_x() return x end end
do local y function set_y(v) y = v end end
print(get_x()) --> 42
set_y(10)
print(get_x()) --> 42
debug.upvaluejoin(set_y, 1, get_x, 1)
print(get_x()) --> 42
set_y(12)
print(get_x()) --> 12
upvalue_split(get_x, 1)
print(get_x()) --> 12
set_y(5)
print(get_x()) --> 12
Enhanced auxiliary library buffer functions - From an implementation point of view, 5.2-work3's luaL_Buffer now uses a userdata to store the string being constructed rather than a complicated tower of strings, which should result in faster performance. In particular, the luaL_addlstring function is now much more efficient as it operates on the entire string at once rather than character by character. There is a new luaL_prepbuffsize function which reserves a block of arbitrary size in the buffer. There is also a new luaL_pushresultsize function which acts like a combined luaL_addsize and luaL_pushresult, and a new luaL_buffinitsize function which acts like a combined luaL_buffinit and luaL_prepbuffersize.
luaL_traceback and luaL_tolstring - The Lua functions tostring and debug.traceback are now implemented in terms to two new functions in the auxiliary library called luaL_tolstring and luaL_traceback. This means that calling these two functions from C code should be easier in 5.2-work3 as it doesn't involving doing lua_getglobal and lua_pcall.
Bytecode is no longer verified when loaded - Due to the number of bugs I've found in Lua 5.1's bytecode verifier, Lua 5.2-work3 has removed the bytecode verifier entirely. In theory, the bytecode verifier was meant to prevent the loading of bytecode which was potentially malicious and could (at least in theory) lead to crashes and/or arbitrary code execution, but the task of doing so is more complex than what the Lua authors are willing to support, and hence the verifier has been dropped. This means that in Lua 5.2-work3 you should be very careful about loading code from untrusted sources (e.g. the user or the network), and unless there is good reason, avoid loading bytecode from untrusted sources altogether. To make this task easier, the load and loadin functions take an optional mode string parameter, which defaults to "bt". If this parameter contains a "b", then loading of bytecode is permitted, and if it contains a "t" then loading of non-bytecode (text) is permitted.
Virtual machine OP_[SG]ETGLOBAL instructions turned into OP_[SG]ETTABUP - The Lua virtual machine is an implementation detail, but an important one. In 5.1, there were two virtual machine operations called OP_SETGLOBAL and OP_GETGLOBAL, which accessed the environment of the active function. With the change to environments, these two operations have morphed into OP_SETTABUP and OP_GETTABUP, which can access any upvalue of the active function which is a table. Potentially this means that indexing upvalues will be slightly faster in 5.2-work3, as compared to 5.1 (where it requires an OP_GETUPVAL followed by an OP_GETTABLE or OP_SETTABLE).
lua_equal and lua_lessthan unified into lua_compare - In Lua 5.1, there were two functions in the C API for perform < and == operations in the standard (metamethod-invoking) manner. In 5.2-work3, these two functions have been removed, and in their place a new lua_compare function has been added, which can perform <, <=, or ==.
Slight behavioural change to the pairs function - The main change to pairs is that in 5.2-work3, it now respects the __pairs metamethod. An extremely subtle change related to the introduction of light C functions is that its first return value is now equal to next (at least in this implementation; the return value of pairs is implementation-dependant):print(pairs{} == next) --> false in 5.1, true in 5.2-work3
Higher limit on maximum stack size - In Lua 5.1, a C function was limited to 8000 stack slots. Seeing as the stack in question is allocated and resized on the heap, this limit is arbitrary. In 5.2-work3, this limit has been raised to one million stack slots (or 15000 if sizeof(int) < 4), meaning that the following code now words:
-- Lua 5.2-work3
print(select('#', ("a"):rep(999):rep(999):byte(1, -1))) --> 998001
xpcall accepts (and forwards) additional arguments - In Lua 5.1, the xpcall function took exactly two parameters - a function to call in protected mode, and an error handler. If you wanted to pass parameters to the function to be called, you'd have to create a closure. In 5.2-work3, this has changed so that xpcall accepts extra arguments:
-- Lua 5.2-work3
xpcall(print, function() end, "Hello", "World") --> Hello  World
The debug library is no longer loaded by default - Programs which use luaL_openlibs to initialise the Lua standard libraries (like the standard Lua interpreter) will find that the debug library is no longer loaded by default in 5.2-work3. Instead it is placed into package.preload, meaning that if you want to use it, you must call require("debug") (which conveniently is harmless in 5.1).
unpack renamed to table.unpack with new semi-inverse table.pack - The global function unpack in Lua 5.1 has been renamed as table.unpack in 5.2-work3. There is also a new function called table.pack, whose implementation is equivalent to:function table.pack(...) return {n = select('#', ...), ...} end
Hence table.pack isn't an inverse of table.unpack when there are trailing nils, as table.unpack doesn't respect the n field of a table by default.
debug.[sg]etupvalue can touch C upvalues - In Lua 5.1, the standard library functions debug.getupvalue and debug.setupvalue couldn't touch upvalues of C functions. In 5.2-work3 this restriction has been lifted, so the following code now does something:-- Lua 5.2-work3
print(require"debug".getupvalue(newproxy, 1)) --> table
lua_pushstring and lua_pushlstring now return the interned string - In Lua 5.1, these two functions returned nothing. In 5.2-work3, they behave in the same way as lua_pushfstring, and return a pointer to Lua's internal copy of the resulting string.
luaL_loadfile no longer accepts bytecode files with a shebang - It is documented behaviour that luaL_loadfile will skip over the first line of a file if that line is a unix shebang (or more precisely, if the first line starts with a #, which also means that if the first line is a C preprocessor command, it'll be ignored). It is also well known behaviour that luaL_loadfile will accept bytecode chunks. Due to a very slight implementation change in 5.2-work3, luaL_loadfile no longer supports both of these things at the same time, meaning that the following code no longer works:
-- Lua 5.1
f = io.open([[C:\temp.lua]], "wb")
f:write("# Blah\n")
f:write(string.dump(function() print "Hello" end))
f:close()
dofile [[C:\temp.lua]] --> Hello
"*L" option to io.read - The io.read function accepts the "*l" option in 5.1 to read a line. This option is still supported in 5.2-work3, though there is now a new similar option "*L" for reading a line and preserving the newline sequence at the end rather than throwing it away. This is potentially useful for reading a file line-by-line and simultaneously writing it line-by-line without changing it in any way.
Addendum: The io.lines function has also been extended - if you pass it a list of options, then on each iteration it'll pass those onto io.read rather than always passing "*l".
lua_version function - Lua 5.0 had a function called lua_version, which was removed in 5.1, and has been reintroduced with new semantics in 5.2-work3. Also new is a function called luaL_checkversion, which can be used to easily check that the Lua library being used matches the version used at compile time, and also that there aren't multiple independent instances of the Lua library present in an executable trying to interact with each other.
Removal of compatibility features present in 5.1 - Many things which were deprecated in Lua 5.1 have been removed in 5.2-work3. On the Lua side, the gcinfo, table.setn, loadlib, math.mod, and math.fmod global functions are gone, as is the old-fashioned vararg mechanism of using a table called arg. On the C API side, lua_open, lua_getregistry, luaL_setn, luaL_getn, and lua_getgccount are gone, as are the old names lua_Chunkreader and lua_Chunkwriter. Nested long strings are now completely ignored by the parser rather than causing a deprecation error, so the following now works:
-- Lua 5.2-work3
print([[Hello [[ World]]) --> Hello [[ World
Better behaviour of math.random with large integers - Due to an implementation detail, Lua 5.1's math.random doesn't behave well when asked to generate an integer within a range whose endpoints are too large to fit into an int. Lua 5.2-work3 fixes this, so that the following works:
-- Lua 5.2-work3
print(math.random(2^32+1, 2^32+3)-2^32) --> 1, 2, or 3
Empty statement permitted by the parser - In Lua 5.1, a semicolon could be used to explicitly mark the end of a statement, though there were extremely few times when this was required. In Lua 5.2-work3, the empty statement is permitted, meaning that you can insert multiple semicolons between statements, which might be useful for computer-generated code. Note that return and break statements can still only be followed by a maximum of one semicolon, as they must be the last statement of a block, and hence cannot be followed by an empty statement. Hence the following is now valid code:
-- Lua 5.2-work3
;;; print("Hello World") ;;; --> Hello World
return;
lua_absindex function - The Lua 5.1 sources had an internal macro for converting relative stack references into absolute stack references, as did many user libraries. These macros depended on implementation details, so to make things cleaner, Lua 5.2-work3 has introduced an official function called lua_absindex for converting a relative (negative but not pseudo) stack index into an absolute (positive) stack index.
lua_copy function - The existing range of stack manipulation functions (lua_replace, lua_pushvalue, lua_pop, etc.) has been augmented in 5.2-work3 by the addition of a lua_copy function, which works like lua_replace, but without popping the element from the top of the stack.
Slight change to how allocator functions are called - All Lua memory (de/re)allocations are done through a user-supplied function (though if luaL_newstate is used, that function is provided for you). This hasn't changed. What has changed is how the allocator function is called in order to perform an allocation. In 5.1, it would be called with existing-size set to zero and existing-pointer set to NULL. In 5.2-work3, it is called with existing-pointer set to NULL and existing-size set to LUA_TSTRING, LUA_TTABLE, LUA_TFUNCTION, LUA_TUSERDATA, or LUA_TTHREAD if and only if one that type of object is being allocated. This should allow for slightly better memory allocation profiling.
luaL_testudata function - Lua 5.2-work3 introduces a new function called  luaL_testudata, which behaves in a very similar way to luaL_checkudata, except that it returns NULL rather than throwing an error.
The unary metamethod is called (nearly) as the manual describes - The Lua 5.1 manual states that the __unm metamethod gets called with a single parameter. In the actual implementation of 5.1 it gets called with two, and in 5.2-work3 this is changed so that it actually does get just one (plus nil). The following code demonstrates this:
x = - setmetatable({}, {__unm = print}) --> table  table in 5.1, table  nil in 5.2-work3
New options for lua_gc / collectgarbage - The garbage collector introspection / control function called lua_gc in C and collectgarbage in Lua has gained three new options in 5.2-work3. There is "isrunning" (LUA_GCISRUNNING) which queries whether the garbage collector is stopped or not, "gen" (LUA_GCGEN) which changes the collector into generational mode, and "inc" (LUA_GCINC) which switches it back into normal incremental mode.
Various error messages worded differently - User code shouldn't be relying on the exact wording of error messages, but if it does then it is important to note that many have changed in 5.2-work3 as compared to 5.1. For example:
print(loadstring(("local x;"):rep(300)))
--> 5.1: main function has more than 200 local variables
--> 5.2-work3: too many local variables (limit is 200) in main function near ';'
print(loadstring(("do "):rep(300)))
--> 5.1: chunk has too many syntax levels
--> 5.2-work3: too many syntax levels (limit is 200) in main function near 'do'
luaL_typerror renamed to luaL_typeerror - This just fixes a typo in the function name which was present in Lua 5.1.
Addendum: pclose reports exit code - Calling the close method on a "file" created by io.popen will return the exit code in 5.2-work3:
-- Lua 5.2-work3
print(io.popen"exit 4":close()) --> 4
Addendum: Frontier pattern finally documented - The "%f[set]" pattern has been accepted by the string library for quite some time now, and matches (without capturing or consuming anything) the transition from something not in the given set to something which is in the given set. In 5.2-work3, it is finally documented, and hence can be used without relying on undocumented behaviour. See the Lua-users wiki for an example of where this is useful.
