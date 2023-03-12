
xor_sum = 0
len = 20

for i in range(0, len) :
    print ( xor_sum , bin(xor_sum) , i , bin(i) , i + 1 , bin(i + 1) )
    xor_sum = xor_sum ^ i ^ (i + 1)
    print ( xor_sum , bin(xor_sum) )

print ( xor_sum ^ (len + 1) , xor_sum , (len + 1) )
