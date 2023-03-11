--[[
	4. Operators
]]
	-- An operator is a symbol that tells the interpreter to perform specific mathematical
	-- or logical manipulations.
	-- Lua language is rich in built-in operators and provides the following type of operators −

		-- Arithmetic Operators : + , - , * , / , % , -(unary) , ^
		-- Relational Operators : < , > , <= , >= , ~= , ==
		-- Logical Operators : or , and , not
		-- Misc Operators : .. , #(unary)

	-- Here are the differences between your standard C-based operator set:

		-- * The logical AND, OR, and NOT operators are the keywords and, or, and not, respectively.
		-- * The inequality operator is ~= instead of !=.
		-- * .. is the operator for string concatenation.
		-- * ^ raises a number to a power, for example 10 ^ 2 would yield 100 (or, ten-squared).
		--   In most other languages, this performs the binary XOR operation.
		-- * # is an operator used to get the length of tables and strings.
		--   We'll see this used in part two.

	-- If you're wondering where bitwise operators are, there aren't any.
	-- However, Lua 5.2 added the bit32 library which you can use for bitwise operations.
	-- If you're using earlier versions of Lua check out this page for some solutions.

	-- Finally, there are two things to note about assignment.
	-- First, compound assignment isn't supported,
	-- thus an expression such as i += 3 must be written as i = i + 3.
	-- Second, the syntax of the operator itself is quite limited.
	-- You can't do things like foo(a = 3) or a = b = 1.


--[[
	4.1 Arithmetic Operators
]]
	-- Lua supports the usual arithmetic operators:
	-- the binary `+´ (addition), `-´ (subtraction), `*´ (multiplication), `/´ (division), and the unary `-´ (negation).
	-- All of them operate on real numbers.
	-- Lua also offers partial support for `^´ (exponentiation).
	-- One of the design goals of Lua is to have a tiny core.
	-- An exponentiation operation (implemented through the pow function in C) would mean
	-- that we should always need to link Lua with the C mathematical library.
	-- To avoid this need, the core of Lua offers only the syntax for the `^´ binary operator,
	-- which has the higher precedence among all operations.
	-- The mathematical library (which is standard, but not part of the Lua core) gives to this operator its expected meaning.

	-- Following table shows all the arithmetic operators supported by Lua language.
	-- Assume variable A holds 10 and variable B holds 20, then −

	--[[
		Operator	Description														Example
		+			Adds two operands												A + B will give 30
		-			Subtracts second operand from the first							A - B will give -10
		*			Multiply both operands											A * B will give 200
		/			Divide numerator by de-numerator								B / A will give 2
		%			Modulus Operator and remainder of after an integer division		B % A will give 0
		^			Exponent Operator takes the exponents							A^2 will give 100
		-			Unary - operator acts as negation								-A will give -10
	]]

	-- Example
	-- Try the following example to understand all the arithmetic operators available in the Lua programming language −

		a = 21
		b = 10
		c = a + b

		print("Line 1 - Value of c is ", c )
		c = a - b

		print("Line 2 - Value of c is ", c )
		c = a * b

		print("Line 3 - Value of c is ", c )
		c = a / b

		print("Line 4 - Value of c is ", c )
		c = a % b

		print("Line 5 - Value of c is ", c )
		c = a^2

		print("Line 6 - Value of c is ", c )
		c = -a

		print("Line 7 - Value of c is ", c )

	-- When you execute the above program, it produces the following result −
	--[[
		Line 1 - Value of c is 	31
		Line 2 - Value of c is 	11
		Line 3 - Value of c is 	210
		Line 4 - Value of c is 	2.1
		Line 5 - Value of c is 	1
		Line 6 - Value of c is 	441
		Line 7 - Value of c is 	-21
	]]


--[[
	4.2 Relational Operators
]]
	-- Following table shows all the relational operators supported by Lua language.
	-- Assume variable A holds 10 and variable B holds 20 then −

	--[[
		Operator	Description													Example
		==			Checks if the values of two operands are equal or not,
					if yes then condition becomes true.							(A == B) is not true.
		~=			Checks if the values of two operands are equal or not,
		            if values are not equal then condition becomes true.		(A ~= B) is true.
		>			Checks if the value of left operand is
					greater than the value of right operand,
		        	if yes then condition becomes true.							(A > B) is not true.
		<			Checks if the value of left operand is
					less than the value of right operand,
					if yes then condition becomes true.							(A < B) is true.
		>=			Checks if the value of left operand is
					greater than or equal to the value of right operand,
					if yes then condition becomes true.							(A >= B) is not true.
		<=			Checks if the value of left operand is
					less than or equal to the value of right operand,
					if yes then condition becomes true.							(A <= B) is true.
	]]

	-- Example
	-- Try the following example to understand all the relational operators available in Lua programming language −

		a = 21
		b = 10

		if( a == b ) then
			print("Line 1 - a is equal to b" )
		else
			print("Line 1 - a is not equal to b" )
		end

		if( a ~= b ) then
			print("Line 2 - a is not equal to b" )
		else
			print("Line 2 - a is equal to b" )
		end

		if ( a < b ) then
			print("Line 3 - a is less than b" )
		else
			print("Line 3 - a is not less than b" )
		end

		if ( a > b ) then
			print("Line 4 - a is greater than b" )
		else
			print("Line 5 - a is not greater than b" )
		end

		-- Lets change value of a and b
		a = 5
		b = 20

		if ( a <= b ) then
			print("Line 5 - a is either less than or equal to  b" )
		end

		if ( b >= a ) then
			print("Line 6 - b is either greater than  or equal to b" )
		end

	-- When you build and execute the above program, it produces the following result −
	--[[
		Line 1 - a is not equal to b
		Line 2 - a is not equal to b
		Line 3 - a is not less than b
		Line 4 - a is greater than b
		Line 5 - a is either less than or equal to  b
		Line 6 - b is either greater than  or equal to b
	]]


--[[
	4.3 Logical Operators
]]
	-- Following table shows all the logical operators supported by Lua language.
	-- Assume variable A holds true and variable B holds false then −

	--[[
		Operator	Description											Example
		and			Called Logical AND operator.
					If both the operands are non-zero,
					then condition becomes true.						(A and B) is false.
		or			Called Logical OR Operator.
					If any of the two operands is non-zero
					then condition becomes true.						(A or B) is true.
		not			Called Logical NOT Operator.
					Used to reverse the logical state of its operand.
					If a condition is true,
					then Logical NOT operator will make false.			!(A and B) is true.
	]]

	-- The logical operators are and, or, and not.
	-- Like control structures, all logical operators consider false and nil as false and anything else as true.
	-- The operator and returns its first argument if it is false; otherwise, it returns its second argument.
	-- The operator or returns its first argument if it is not false;
	-- otherwise, it returns its second argument:

		print( 4 and 5 )        	--> 5
		print( nil and 13 )    		--> nil
		print( false and 13 )   	--> false
		print( 4 or 5 )          	--> 4
		print( false or 5 )     	--> 5

	-- Both and and or use short-cut evaluation, that is, they evaluate their second operand only when necessary.
	-- A useful Lua idiom is x = x or v, which is equivalent to

		if not x then x = v end

	-- i.e., it sets x to a default value v when x is not set (provided that x is not set to false).
	-- Another useful idiom is (a and b) or c (or simply a and b or c, because and has a higher precedence than or),
	-- which is equivalent to the C expression

		a ? b : c

	-- provided that b is not false.
	-- For instance, we can select the maximum of two numbers x and y with a statement like

		max = (x > y) and x or y

	-- When x > y, the first expression of the and is true,
	-- so the and results in its second expression (x) (which is also true, because it is a number),
	-- and then the or expression results in the value of its first expression, x. When x > y is false,
	-- the and expression is false and so the or results in its second expression, y.

	-- The operator not always returns true or false:

		print( not nil )   	--> true
		print( not false ) 	--> true
		print( not 0 )     		--> false
		print( not not nil )	--> false

	-- Example
	-- Try the following example to understand all the logical operators available in the Lua programming language −

		a = 5
		b = 20

		if ( a and b )
		then
		print("Line 1 - Condition is true" )
		end

		if ( a or b )
		then
		print("Line 2 - Condition is true" )
		end

		--lets change the value ofa and b
		a = 0
		b = 10

		if ( a and b )
		then
		print("Line 3 - Condition is true" )
		else
		print("Line 3 - Condition is not true" )
		end

		if ( not( a and b) )
		then
		print("Line 4 - Condition is true" )
		else
		print("Line 3 - Condition is not true" )
		end
		When you build and execute the above program, it produces the following result −

		Line 1 - Condition is true
		Line 2 - Condition is true
		Line 3 - Condition is true
		Line 3 - Condition is not true

--[[
	4.4 Misc Operators
]]
	-- Miscellaneous operators supported by Lua Language include concatenation and length.

	--[[
		Operator	Description									Example
		..			Concatenates two strings.					a..b where a is "Hello " and b is "World",
																will return "Hello World".
		#			An unary operator that return
					the length of the a string or a table.		#"Hello" will return 5
	]]

	-- Example
	-- Try the following example to understand the miscellaneous operators available in the Lua programming language −

		a = "Hello "
		b = "World"

		print("Concatenation of string a with b is ", a..b )
		print("Length of b is ", #b )
		print("Length of b is ", #"Test" )

	-- When you build and execute the above program, it produces the following result −
	--[[
		Concatenation of string a with b is 	Hello World
		Length of b is 	5
		Length of b is 	4
	]]



