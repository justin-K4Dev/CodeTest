# Basic Calculation

print ( 512 + 634 ) # + : addition
#output:1146
print ( 100 * 2013 * 1004 ) # * : multiplication
#ouput: 202105200

print ( 2 * 2014 / 333 )
#output: 12.096096096096096
print ( 2 * 2014 // 333 ) # // : share of division
#output: 12
print( 55 // 3 )
#output: 18

print ( 1024 % 100 ) # % : reminder of division
#output: 24
print ( 123 % 5 )
#output: 3

print ( 2 ** 64 ) # ** : square
#output: 18446744073709551616
print ( 2 ** 32 )
#output: 4294967296


# Using Operators with Strings
helloworld = "hello" + " " + "world"
print ( helloworld )
#output: hello world

lotsofhellos = "hello" * 10
print ( lotsofhellos )
#output: hellohellohellohellohellohellohellohellohellohello


# Using Operators with Lists
even_numbers = [2,4,6,8]
odd_numbers = [1,3,5,7]
all_numbers = odd_numbers + even_numbers
print ( all_numbers )
#output: [1, 3, 5, 7, 2, 4, 6, 8]

print ([1,2,3] * 3)
#output: [1, 2, 3, 1, 2, 3, 1, 2, 3]


'''
    bitwise XOR(logical eXclusive OR)
        0101 (decimal 5)
    XOR 0011 (decimal 3)
    =   0110 (decimal 6)     
'''
a = 9
print ( a , bin(a) )
b = 3
print ( b , bin(b) )
c = a ^ b # Binary XOR(eXclusive OR) : It copies the bit if it is set in one operand but not both.
print ( c , bin(c) )
#output: 9 0b1001
#        3 0b0011
#       10 0b1010


'''
    bitwise OR(logical inclusive OR)
        0101 (decimal 5)
    OR  0011 (decimal 3)
    =   0111 (decimal 7)  
'''
a = 9
print ( a , bin(a) )
b = 3
print ( b , bin(b) )
c = a | b # Binary OR : It copies a bit if it exists in either operand.
print ( c , bin(c) )
#output: 9 0b1001
#        3 0b0011
#       11 0b1011


'''
    bitwise AND(logical AND)
        0101 (decimal 5)
    AND 0011 (decimal 3)
    =   0001 (decimal 1)
'''
a = 9
print ( a , bin(a) )
b = 3
print ( b , bin(b) )
c = a & b # Binary AND : Operator copies a bit to the result if it exists in both operands
print ( c , bin(c) )
#output: 9 0b1001
#        3 0b0011
#        1 0b0001


'''
    bitwise NOT(logical negation)
    NOT 0111  (decimal 7)
    =   1000  (decimal 8)
'''
a = 9
print ( a , bin(a) )
a = ~a # Binary Ones Complement : It is unary and has the effect of 'flipping' bits.
print ( bin(a) )
#output: 9 0b1001
#          0b0110


xor_sum = 0
len = 20

for i in range(0, len) :
    print ( xor_sum , bin(xor_sum) , i , bin(i) , i + 1 , bin(i + 1) )
    xor_sum = xor_sum ^ i ^ (i + 1)
    print ( xor_sum , bin(xor_sum) )

print ( xor_sum ^ (len + 1) , xor_sum , (len + 1) )

'''
output:
     0 0b0 0 0b0 1 0b1
     1 0b1
     1 0b1 1 0b1 2 0b10
     2 0b10
     2 0b10 2 0b10 3 0b11
     3 0b11
     3 0b11 3 0b11 4 0b100
     4 0b100
     4 0b100 4 0b100 5 0b101
     5 0b101
     5 0b101 5 0b101 6 0b110
     6 0b110
     6 0b110 6 0b110 7 0b111
     7 0b111
     7 0b111 7 0b111 8 0b1000
     8 0b1000
     8 0b1000 8 0b1000 9 0b1001
     9 0b1001
     9 0b1001 9 0b1001 10 0b1010
    10 0b1010
    10 0b1010 10 0b1010 11 0b1011
    11 0b1011
    11 0b1011 11 0b1011 12 0b1100
    12 0b1100
    12 0b1100 12 0b1100 13 0b1101
    13 0b1101
    13 0b1101 13 0b1101 14 0b1110
    14 0b1110
    14 0b1110 14 0b1110 15 0b1111
    15 0b1111
    15 0b1111 15 0b1111 16 0b10000
    16 0b10000
    16 0b10000 16 0b10000 17 0b10001
    17 0b10001
    17 0b10001 17 0b10001 18 0b10010
    18 0b10010
    18 0b10010 18 0b10010 19 0b10011
    19 0b10011
    19 0b10011 19 0b10011 20 0b10100
    20 0b10100
    1 20 21
'''


