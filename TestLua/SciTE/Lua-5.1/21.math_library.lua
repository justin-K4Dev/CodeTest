--[[
	11. Math Library
]]

-- We often need math operations in scientific and engineering calculations and we can avail this using the standard Lua library math. The list of functions available in math library is shown in the following table.

S.N.	Library / Method & Purpose
1.	
math.abs (x)

Returns the absolute value of x.

2.	
math.acos (x)

Returns the arc cosine of x (in radians).

3.	
math.asin (x)

Returns the arc sine of x (in radians).

4.	
math.atan (x)

Returns the arc tangent of x (in radians).

5.	
math.atan2 (y, x)

Returns the arc tangent of y/x (in radians), but uses the signs of both parameters to find the quadrant of the result. (It also handles correctly the case of x being zero.)

6.	
math.ceil (x)

Returns the smallest integer larger than or equal to x.

7.	
math.cos (x)

Returns the cosine of x (assumed to be in radians).

8.	
math.cosh (x)

Returns the hyperbolic cosine of x.

9.	
math.deg (x)

Returns the angle x (given in radians) in degrees.

10.	
math.exp (x)

Returns the value e power x.

11.	
math.floor (x)

Returns the largest integer smaller than or equal to x.

12.	
math.fmod (x, y)

Returns the remainder of the division of x by y that rounds the quotient towards zero.

13.	
math.frexp (x)

Returns m and e such that x = m2e, e is an integer and the absolute value of m is in the range [0.5, 1) (or zero when x is zero).

14.	
math.huge

The value HUGE_VAL, a value larger than or equal to any other numerical valu.

15.	
math.ldexp (m, e)

Returns m2e (e should be an integer).

16.	
math.log (x)

Returns the natural logarithm of x.

17.	
math.log10 (x)

Returns the base-10 logarithm of x.

18.	
math.max (x, ...)

Returns the maximum value among its arguments.

19.	
math.min (x, ...)

Returns the minimum value among its arguments.

20.	
math.modf (x)

Returns two numbers, the integral part of x and the fractional part of x.

21.	
math.pi

The value of pi.

22.	
math.pow (x, y)

Returns xy. (You can also use the expression x^y to compute this value.)

23.	
math.rad (x)

Returns the angle x (given in degrees) in radians.

24.	
math.random ([m [, n]])

This function is an interface to the simple pseudo-random generator function rand provided by ANSI C.When called without arguments, returns a uniform pseudo-random real number in the range [0,1). When called with an integer number m, math.random returns a uniform pseudo-random integer in the range [1, m]. When called with two integer numbers m and n, math.random returns a uniform pseudo-random integer in the range [m, n].

25.	
math.randomseed (x)

Sets x as the "seed" for the pseudo-random generator: equal seeds produce equal sequences of numbers.

26.	
math.sin (x)

Returns the sine of x (assumed to be in radians).

27.	
math.sinh (x)

Returns the hyperbolic sine of x.

28.	
math.sqrt (x)

Returns the square root of x. (You can also use the expression x^0.5 to compute this value.)

29.	
math.tan (x)

Returns the tangent of x (assumed to be in radians).

30.	
math.tanh (x)

Returns the hyperbolic tangent of x.

Trigonometric functions
A simple example using trigonometric function is shown below.

radianVal = math.rad(math.pi / 2)

io.write(radianVal,"\n")

-- Sin value of 90(math.pi / 2) degrees
io.write(string.format("%.1f ", math.sin(radianVal)),"\n")

-- Cos value of 90(math.pi / 2) degrees
io.write(string.format("%.1f ", math.cos(radianVal)),"\n")

-- Tan value of 90(math.pi / 2) degrees
io.write(string.format("%.1f ", math.tan(radianVal)),"\n")

-- Cosh value of 90(math.pi / 2) degrees
io.write(string.format("%.1f ", math.cosh(radianVal)),"\n")

-- Pi Value in degrees
io.write(math.deg(math.pi),"\n")
When we run the above program, we will get the following output.

0.027415567780804
0.0 
1.0 
0.0 
1.0 
180
Other common math functions
A simple example using common math functions is shown below.

-- Floor
io.write("Floor of 10.5055 is ", math.floor(10.5055),"\n")

-- Ceil
io.write("Ceil of 10.5055 is ", math.ceil(10.5055),"\n")

-- Square root
io.write("Square root of 16 is ",math.sqrt(16),"\n")

-- Power
io.write("10 power 2 is ",math.pow(10,2),"\n")
io.write("100 power 0.5 is ",math.pow(100,0.5),"\n")

-- Absolute
io.write("Absolute value of -10 is ",math.abs(-10),"\n")

--Random
math.randomseed(os.time())
io.write("Random number between 1 and 100 is ",math.random(),"\n")

--Random between 1 to 100
io.write("Random number between 1 and 100 is ",math.random(1,100),"\n")

--Max
io.write("Maximum in the input array is ",math.max(1,100,101,99,999),"\n")

--Min
io.write("Minimum in the input array is ",math.min(1,100,101,99,999),"\n")
When we run the above program, we will get the following output.

Floor of 10.5055 is 10
Ceil of 10.5055 is 11
Square root of 16 is 4
10 power 2 is 100
100 power 0.5 is 10
Absolute value of -10 is 10
Random number between 1 and 100 is 0.22876674703207
Random number between 1 and 100 is 7
Maximum in the input array is 999
Minimum in the input array is 1
The above examples are just a few of the common examples, we can use math library based on our need, so try using all the functions to be more familiar.
