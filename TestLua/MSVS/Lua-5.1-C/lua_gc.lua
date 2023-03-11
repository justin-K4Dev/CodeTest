local stringBuffer = {}

function eventHandler (cmd)
    if ("reset" == cmd) then
        stringBuffer = {}
    end
end

for i = 0, 200000 do
    stringBuffer[i] = "Loop" .. i .. "Count"
end