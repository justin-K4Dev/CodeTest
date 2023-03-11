--[[
	5. Loops
]]
	-- There may be a situation when you need to execute a block of code several number of times.
	-- In general, statements are executed sequentially −
	-- the first statement in a function is executed first,
	-- followed by the second, and so on.

	-- Programming languages provide various control structures that allow for more complicated execution paths.
	-- A loop statement allows us to execute a statement or group of statements multiple times.
	-- Following is the general form of a loop statement in most of the programming languages −

		-- reference loop_architecture.jpg file

	-- Lua provides the following types of loops to handle looping requirements.
		--[[
			Loop Type				Description
			while loop				Repeats a statement or group of statements while a given condition is true.
									It tests the condition before executing the loop body.
			for loop				Executes a sequence of statements multiple times and abbreviates the code
									that manages the loop variable.
			repeat...until loop		Repeats the operation of group of statements till the until condition is met.
			nested loops			You can use one or more loop inside any another while, for or do..while loop.
		]]


--[[
	5.1 while loop
]]
	-- A while loop statement in Lua programming language repeatedly
	-- executes a target statement as long as a given condition is true.

	-- Syntax
	-- The syntax of a while loop in Lua programming language is as follows −
		--[[
			while(condition) do
				statement(s)
			end
		]]
	
	-- Here, statement(s) may be a single statement or a block of statements.
	-- The condition may be any expression, and true is any non-zero value.
	-- The loop iterates while the condition is true.

	-- When the condition becomes false, the program control passes to the line immediately following the loop.

	-- Flow Diagram

		-- Reference loop_while_loop.jpg file

	-- Here, the key point to note is that the while loop might not be executed at all.
	-- When the condition is tested and the result is false,
	-- the loop body will be skipped and the first statement after the while loop will be executed.

	-- Example
		a=10

		while( a < 20 ) do
			print("value of a:", a)
			a = a + 1
		end
	-- When the above code is built and executed, it produces the following result −
	--[[
		value of a:	10
		value of a:	11
		value of a:	12
		value of a:	13
		value of a:	14
		value of a:	15
		value of a:	16
		value of a:	17
		value of a:	18
		value of a:	19
	]]

--[[
	5.2 for loop
]]
	-- A for loop is a repetition control structure that allows you to efficiently write a loop
	-- that needs to execute a specific number of times.

	-- Syntax
	-- The syntax of a for loop in Lua programming language is as follows −
		--[[
			for init, max/min value, increment do
				statement(s)
			end
		]]
	
	-- Here is the flow of control in a for loop −

		-- * The init step is executed first, and only once.
		--   This step allows you to declare and initialize any loop control variables.

		-- * Next, the max/min. This is the maximum or minimum value till which the loop continues to execute.
		--   It creates a condition check internally to compare between the initial value and maximum/minimum value.

		-- * After the body of the for loop executes,
		--   the flow of the control jumps back up to the increment/decrement statement.
		--   This statement allows you to update any loop control variables.

		-- * The condition is now evaluated again.
		--   If it is true, the loop executes and the process repeats itself
		--   (body of loop, then increment step, and then again condition).
		--   After the condition becomes false, the for loop terminates.

	-- Flow Diagram

		-- Reference lua_for_loop.jpg file
	
	-- Example
		for i = 10, 1, -1 do 
   			print(i) 
		end

		a = { x = 400, y = 300, [20] = "foo" } -- table
		for key, value in pairs(a) do
			print(key, value)
		end

		b = { 20, 30, 40 } -- array
		for index, value in ipairs(b) do
			print(index, value)
		end
	
	-- When the above code is built and executed, it produces the following result −
	--[[
		10
		9
		8
		7
		6
		5
		4
		3
		2
		1
		y    300
		x    400
		20   foo
		1    20
		2    30
		3    40	
	]]

    -- print all values of array `a'
		a = { 1, 2, 3 }

		for i, v in ipairs(a) do
			print(v) -- 1, 2, 3
		end
	-- For each step in that code, i gets an index, while v gets the value associated with that index.
	
	-- A similar example shows how we traverse all keys of a table:
    -- print all keys of table `t'
		t = { 1, 2, 3 }

		for k in pairs(t) do
			print(k) -- 1, 2, 3
		end


--[[
	5.3 for repeat...until loop
]]
	-- Unlike the for and while loops, which test the loop condition at the top of the loop,
	-- the repeat...until loop in Lua programming language checks its condition at the bottom of the loop.

	-- A repeat...until loop is similar to a while loop,
	-- except that a do...while loop is guaranteed to execute at least one time.

	-- Syntax
	-- The syntax of a repeat...until loop in Lua programming language is as follows −
		--[[
			repeat
			statement(s)
			while( condition )
		]]

	-- Notice that the conditional expression appears at the end of the loop,
	-- so the statement(s) in the loop execute(s) once before the condition is tested.

	-- If the condition is false, the flow of control jumps back up to do,
	-- and the statement(s) in the loop execute again.
	-- This process repeats until the given condition becomes true.

	-- Flow Diagram

		-- Reference lua_repeat_until_loop.jpg

	-- Example
		--[ local variable definition --]
		a = 10

		--[ repeat loop execution --]
		repeat
			print("value of a:", a)
			a = a + 1
		until( a > 15 )
	
	-- When you build and execute the above program, it produces the following result −
	--[[
		value of a:	10
		value of a:	11
		value of a:	12
		value of a:	13
		value of a:	14
		value of a:	15
	]]


--[[
	5.4 nested loops
]]
	-- Lua programming language allows to use one loop inside another loop.
	-- Following section shows few examples to illustrate the concept.

	-- Syntax
	-- The syntax for a nested for loop statement in Lua is as follows −
		--[[
			for init, max/min value, increment do
				for init, max/min value, increment do
					statement(s)
				end
				statement(s)
			end
		]]

	-- The syntax for a nested while loop statement in Lua programming language is as follows −
		--[[
			while(condition) do
				while(condition) do
					statement(s)
				end
				statement(s)
			end
		]]
	
	-- The syntax for a nested repeat...until loop statement in Lua programming language is as follows −
		--[[
			repeat
				statement(s)
				repeat
					statement(s)
				until( condition )
			until( condition )
		]]
	
	-- A final note on loop nesting is that you can put any type of loop inside of any other type of loop.
	-- For example, a for loop can be inside a while loop or vice versa.

	-- Example
	-- The following program uses a nested for loop −

		j =2
		for i=2, 10 do
			for j=2, (i/j), 2 do
				
				if(not(i%j)) then
					break 
				end
					
				if(j > (i/j)) then
					print("Value of i is",i)
				end
			end
		end

	-- When you build and run the above code, it produces the following result.
	--[[
		Value of i is	8
		Value of i is	9
		Value of i is	10
	]]


--[[
	5.5 Loop Control Statement
]]
	-- Loop control statement changes execution from its normal sequence.
	-- When execution leaves a scope,
	-- all automatic objects that were created in that scope are destroyed.

	-- Lua supports the following control statements.

	--[[
		Control Statement		Description
		break statement			Terminates the loop
								and transfers execution to the statement immediately following the loop or switch.
	]]


--[[
	5.5.1 break statement
]]
	-- When the break statement is encountered inside a loop,
	-- the loop is immediately terminated
	-- and the program control resumes at the next statement following the loop.

	-- If you are using nested loops (i.e., one loop inside another loop),
	-- the break statement will stop execution of the innermost loop
	-- and start executing the next line of code after the block.

	-- Syntax
	-- The syntax for a break statement in Lua is as follows −

		-- break

	-- Flow Diagram

		-- Reference lua_break_statement.jpg file

	-- Example
		--[ local variable definition --]
		a = 10

		--[ while loop execution --]
		while( a < 20 )	do
			print("value of a:", a)
			a = a + 1
			
			if( a > 15)
			then
				--[ terminate the loop using break statement --]
				break
			end
		end

	-- When you build and run the above code, it produces the following result.
	--[[
		value of a:	10
		value of a:	11
		value of a:	12
		value of a:	13
		value of a:	14
		value of a:	15
	]]


--[[
	5.6 The Infinite Loop
]]
	-- A loop becomes infinite loop if a condition never becomes false.
	-- The while loop is often used for this purpose.
	-- Since we directly give true for the condition, it keeps executing forever.
	-- We can use the break statement to break this loop.

		while( true ) do
			print("This loop will run forever.")
		end