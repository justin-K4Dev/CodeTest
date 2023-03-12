# Variables and Types


# DataType
print ( type(33) )
#output: <class 'int'>
print ( type(3.14) )
#output: <class 'float'>
print ( type(['1', '2', '3']) )
#output: <class 'list'>
print ( type(33331491491492) )
#output: <class 'int'>


# Integer

A = 5
B = 10
print( A, B )
#output: 5 10

print( 0b10, 0o10, 0x10 ) # 0b: binary(2) number, 0o: octal(8) number, 0x: hxadecimal(16) number
#output: 2 8 16

print ( bin(202020) ) # convert binary(2) number
#output: 0b110001010100100100
print ( oct(20114) ) # convert octal(8) number
#output: 0o47222
print ( hex(401000) ) # convert hxadecimal(16) number
#output: 0x61e68


money = 1000
cookiePrice = 600
money = money - cookiePrice
print ( money )
#output: 400
print ( money + cookiePrice )
#output: 1000


money = 1000
# 1000 = money
#output: SyntaxError: can't assign to literal


x = 3 # literal object 3 referance
y = 3 # literal object 3 referance
z = 5 # literal object 5 referance
print ( id(x), id(y), id(3), id(z), id(5) )
#output: 507098848 507098848 507098848 507098912 507098912


#4apple = 10 # SyntaxError: invalid syntax
admin = 50
Item = 100
print ( admin, Item )
#output: 50 100


# float

A = 3.14
B = 5.1402020319
print ( A, B )
#ouput: 3.14, 5.1402020319


myfloat = 7.0
myfloat = float(7)
print( myfloat )
#output: 7.0


print ( 0.2319320202032E8 ) # E: Exponent, 10^8
#ouput: 23193202.032
print ( 1412232.22E-10 ) # E: Exponent, 10^-10
#ouput: 0.000141223222


print( 5.4 + 1.2 )
#output: 6.6000000000000005
print( 1.4 - 1.1 )
#output: 0.2999999999999998


print( 0.125 * 2 )
#output: 0.25
print( 0.25 * 2 )
#output: 0.5
print( 0.5 * 2 )
#output: 1.0


print( 0.1 * 2 )
#output: 0.2
print( 0.2 * 2 )
#output: 0.4
print( 0.4 * 2 )
#output: 0.8
print( 0.8 * 2 )
#output: 1.6


# Strings

mystring = 'hello'
mystring = "hello"
print( mystring )
#output: hello


mystring = "Don't worry about apostrophes"
print( mystring )
#output: Don't worry about apostrophes


# Complex

x = 7 - 3j
print ( type(x) )
#output: <class 'complex'>
print ( x.imag ) # imag: 
#output: -3.0
print ( x.real ) # real:
#output: 7.0
print ( x.conjugate() ) # conjugate
#output: (7+3j)


# Assignments can be done on more than one variable "simultaneously" on the same line like
a, b = 3, 4
print( a, b )
#output: 3, 4