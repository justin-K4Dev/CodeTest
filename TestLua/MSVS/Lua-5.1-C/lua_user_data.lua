
a = array.new (1000)

print (a)               --> userdata: 0x8064d48
print (array.size (a))  --> 1000

for i = 1, 1000 do
    array.set (a, i, i % 5 == 0)
end

print (array.get (a, 10))   --> true