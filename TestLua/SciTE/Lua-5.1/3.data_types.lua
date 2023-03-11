--[[
	3. Data Types
]]
	-- Lua is a dynamically typed language.
	-- There are no type definitions in the language; each value carries its own type.

	-- In Lua, though we don't have variable data types, but we have types for the values.
	-- The list of data types for values are given below.
	
		--[[
			Value Type			Description
			nil					Used to differentiate the value from having some data or no(nil) data.
			boolean				Includes true and false as values. Generally used for condition checking.
			number				Represents real(double precision floating point) numbers.
			string				Represents array of characters.
			function			Represents a method that is written in C or Lua.
			userdata			Represents arbitrary C data.
			thread				Represents independent threads of execution and it is used to implement coroutines.
			table				Represent ordinary arrays, symbol tables, sets, records, graphs, trees, etc.,
								and implements associative arrays. It can hold any value (except nil).
		]]

	-- In Lua, there is a function called 'type' that enables us to know the type of the variable.
	-- Some examples are given in the following code.

		print(type("Hello world")) 	--> string
		print(type(10.4*3))        	--> number
		print(type(print))         	--> function
		print(type(type))          	--> function
		print(type(true))          	--> boolean
		print(type(nil))			--> nil
		print(type(type(X)))       	--> string

	-- The last example will result in "string" no matter the value of X,
	-- because the result of type is always a string.

		print(type(a))  	--> nil (`a' is not initialized)
		a = 10
		print(type(a))   	--> number
		a = "a string!!"
		print(type(a))   	--> string
		a = print        	--> yes, this is valid!
		a(type(a))       	--> function

	-- Notice the last two lines: Functions are first-class values in Lua;
	-- so, we can manipulate them like any other value.

	-- Usually, when you use a single variable for different types, the result is messy code.
	-- However, sometimes the judicious use of this facility is helpful,
	-- for instance in the use of nil to differentiate a normal return value from an exceptional condition.


--[[
	3.1 Numbers and Maths
]]
	-- Numbers are quite simple in Lua.
	-- There's no distinction between doubles, floats, integers, or unsigned integers;
	-- everything is a double (or, double-precision floating-point).
	-- Programming in Lua states that doubles have no rounding errors when representing integers,
	-- and are also very efficient on modern CPUs.
	-- Since all numbers are the same type,
	-- there's no type conversion to worry about when performing arithmetic.

	-- Here's a few examples of how numbers can be written:
	-- 4, 0.4, .4, 4.3, 0xFF, 0xA33FF0E, 8.7e12, 8.7e+12, 8e-12.

		print(4, 0.4, .4, 4.3, 0xFF, 0xA33FF0E, 8.7e12, 8.7e+12, 8e-12)

	-- The math module contains many of the mathematical functions you would expect from a language such as math.sin,
	-- math.cos, math.floor, etc.
	-- There's a few things you'll want to be aware of:

		-- * math.huge is the largest value a number can be.
		-- * Although math.floor and math.ceil are present, there's no math.round.
		--   Not to worry though, you can easily achieve the same thing with code like math.floor(x + .5).
		-- * You can use math.random to generate pseudo-random numbers.
		--   Before using it, it's a good idea to set the seed with math.randomseed.
		--   A common thing to do is math.randomseed(os.time()).


--[[
	3.2 Tables
]]
	-- Tables are essentially associative arrays which can have keys and values of any type.
	-- Tables are incredibly flexible, and are the only data structure in Lua,
	-- so knowledge of them is crucial.

	-- Here's an example of how to use them:

		x = 5
		a = {} -- empty table
		b = { key = x, anotherKey = 10 } -- strings as keys
		c = { [x] = b, ["string"] = 10, [34] = 10, [b] = x } -- variables and literals as keys

		-- assignment
		a[1] = 20
		a["foo"] = 50
		a[x] = "bar"

		-- retrieval
		print(b["key"]) --> 5
		print(c["string"]) --> 10
		print(c[34]) --> 10
		print(c[b]) --> 5

	-- Curly brackets are used to create them.
	-- You can use any kind of expression as a key as long as it's surrounded by square brackets.
	-- If you'd like the key to be a string then you don't need square brackets or quotes,
	-- as demonstrated by the definition of b.


--[[
	3.2.1 Syntactic Sugar
]]
	-- Tables have some awesome syntax when it comes to string keys:

		t = { foo = 1, bar = 2 }
		print(t.foo) --> 1
		t.bar = 3

	-- This makes many uses of tables a lot more visually pleasing.
	-- One example is the Lua standard libraries;
	-- instead of writing something like math["sqrt"](x) we can write math.sqrt(x).


--[[
	3.2.2 Arrays and Indices
]]
	-- Lua has additional support for traditional, integer-indexed arrays:

		a = { 11, 22, "foo", "bar" }
		a[3] = "foooo"

		print(a[1]) --> 11
		print(a[3]) --> foooo
		print(#a) --> 4

	-- If you don't supply keys along with values when creating a table they will be automatically assigned indices.
	-- Also notice how the length operator returns the number of elements in a table.

	-- Lua is different from most languages when it comes to indices; they start at 1 rather than 0.
	-- That means that instead of half-open ranges ([0, length)), closed ranges ([1, length]) are used.
	-- This concept is built into Lua at multiple levels,
	-- so although it's possible to still use indices starting at 0,
	-- it's highly impractical.
	

--[[
	3.3 Strings
]]
	-- Strings work as you'd expect; you can declare them with double or single quotes,
	-- and use backslash to escape characters.
	-- For strings spanning multiple lines you can use square brackets in the format [[...]].
	-- Here's an example:

		s = "foo\nbar"
		t = 'he said "hello world"'
		u = "Hello \"world\""
		v = [[
		<html>
		<body>
			<p>Hello world!</p>
		</body>
		</html>
		]]


--[[
	3.4 Functions
]]
	-- Functions are first-class values in Lua.
	-- That means that functions can be stored in variables, passed as arguments to other functions, and returned as results.
	-- Such facilities give great flexibility to the language: A program may redefine a function to add new functionality,
	-- or simply erase a function to create a secure environment when running a piece of untrusted code
	-- (such as code received through a network).
	-- Moreover, Lua offers good support for functional programming,
	-- including nested functions with proper lexical scoping; just wait.
	-- Finally, first-class functions play a key role in Lua's object-oriented facilities, as we will see in Chapter 16.

	-- Lua can call functions written in Lua and functions written in C.
	-- All the standard library in Lua is written in C.
	-- It comprises functions for string manipulation, table manipulation, I/O,
	-- access to basic operating system facilities, mathematical functions, and debugging.
	-- Application programs may define other functions in C.


--[[
	3.5. Userdata and Threads
]]
	-- The userdata type allows arbitrary C data to be stored in Lua variables.
	-- It has no predefined operations in Lua, except assignment and equality test.
	-- Userdata are used to represent new types created by an application program or a library written in C;
	-- for instance, the standard I/O library uses them to represent files.
	-- We will discuss more about userdata later, when we get to the C API.
	-- We will explain the thread type, we discuss coroutines.