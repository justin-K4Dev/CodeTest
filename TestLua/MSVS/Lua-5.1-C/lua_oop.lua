--[[
-- set __index for OOP key mechanism in Lua example
local metaArray = getmetatable (array.new (1))
metaArray.__index = metaArray;
metaArray.set = array.set
metaArray.get = array.get
metaArray.size = array.size
--]]

a = array.new (1000)
print (a:size ())   --> 1000
a:set (10, 3.4)
print (a:get (10))  --> 3.4




