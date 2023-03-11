--[[ 
   gameobject comes from the global parameters and is a pointer to
   the REAL C++ data.  This is saved as lightuserdata in Lua and we preserve
   this pointer in the LuaGameObject.  From there, we can manipulate
   ANYTHING from this pointer.
--]]

-- Lua Functions
function printf(...) io.write(string.format(unpack(arg))) end

-- This function uses the getX() methods in our target class
function LuaGameObject:show()
    printf("LuaGameObject attribute = %d - %s\n", self:getAttr(), self:getMessage())
end

-- Start up a new LuaGameObject wrapper class and pass the global gameobject
-- C++ lightuserdata pointer into it
b = LuaGameObject(gameobject)

-- Call a Lua function on this object
b:show()

print('Now to work on the C++ object')
-- Modify some of the parameters (gameobject->modify)
b:setAttr(120)
b:setMessage('Hey - Lua changes a string!')
print('Lua is done changing...')
b:show()