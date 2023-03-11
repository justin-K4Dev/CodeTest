for n, v in pairs (CustomClass) do print (n, v) end

local a = CustomClass.new ()
local b = CustomClass.new (99, 100)

caller = CustomClass.callFunction

print (a, caller (a))
print (b, caller (b))


function CustomClass:show (msg)
    print (msg, self, self:callFunction ())
    return self
end

function CustomClass:point (t)
    assert (type (t) == 'table')
    self:setX (t.x or t[1]):setY (t.y or t[2])
    return self
end

setmetatable (CustomClass, { __call = function (self, x, y)
        local bar = self.new (x, y)
        print ('created', bar)
        return bar
    end }
)

local p = CustomClass (1, 2)
p:show ('p is')
p:setX (3):show'p is':setY (4):show'p is'
p:point { 33, 44 }:show'p is'
p = nil

collectgarbage ()

a:point { x = 500, y = 1000 }

a:show'a is'
b:show'b is'

r = CustomClass.add (a, b)
r:show'r is'

a:show'a is'
b:show'b is'
s = a + b
s:show's is'
