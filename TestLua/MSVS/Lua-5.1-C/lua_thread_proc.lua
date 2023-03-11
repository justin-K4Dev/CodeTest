--[[
local i = 0
while true do
  print('iterate', i)
  sleep(1000000)
  i = i + 1
  if i == 4 then
    print('bkrea!')
    break
  end
end
--]]

function step ()
    print('next', next(1))
    print('next', next('hello', 2))
    print('next', next(function () end))
end

--finish()
print('load proc.lua')