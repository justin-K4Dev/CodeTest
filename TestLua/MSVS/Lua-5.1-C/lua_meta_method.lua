--[[
-- set __index for Meta Method key mechanism in Lua example
local metaArray = getmetatable (array.new (1))
metaArray.__index = array.get
metaArray.__newindex = array.set
metaArray.__len = array.size
--]]

a = array.new (1000)
a[10] = true    --> setArray
print(a[10])    --> getArray    --> true
print(#a)       --> getSize     --> 1000