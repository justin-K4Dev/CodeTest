--[[
	6. Decision Marking
]]
	-- Decision making structures require
	-- that the programmer specifies one or more conditions to be evaluated
	-- or tested by the program, along with a statement or statements to be executed,
	-- if the condition is determined to be true, and optionally,
	-- other statements to be executed if the condition is determined to be false.

	-- Following is the general form of a typical decision making structure found in
	-- most of the programming languages −

		-- Referece decision_making.jpg file

	-- Lua programming language assumes any combination of Boolean true and non-nil values as true,
	-- and if it is either boolean false or nil, then it is assumed as false value.
	-- It is to be noted that in Lua, zero will be considered as true.

	-- Lua programming language provides the following types of decision making statements.
	--[[
		Statement				Description
		if statement			An if statement consists of a boolean expression followed by one
								or more statements.
		if...else statement		An if statement can be followed by an optional else statement,
								which executes when the boolean expression is false.
		nested if statements	You can use one if or else if statement inside another if
								or else if statement(s).
	]]

--[[
	6.1 if statement
]]
	-- An if statement consists of a Boolean expression followed by one or more statements.

	-- Syntax
	-- The syntax of an if statement in Lua programming language is −
	--[[
		if(boolean_expression)
		then
		--[ statement(s) will execute if the boolean expression is true --]
		end
	]]
	
	-- If the Boolean expression evaluates to true,
	-- then the block of code inside the if statement will be executed.
	-- If Boolean expression evaluates to false,
	-- then the first set of code after the end of the if statement(after the closing curly brace) will be executed.

	-- Lua programming language assumes any combination of Boolean true and non-nil values as true,
	-- and if it is either Boolean false or nil, then it is assumed as false value.
	-- It is to be noted that in Lua, zero will be considered as true.

	-- Flow Diagram

		-- Reference if_statment.jpg file

	-- Example
		--[ local variable definition --]
		a = 10;

		--[ check the boolean condition using if statement --]
		if( a < 20 ) then
			--[ if condition is true then print the following --]
			print("a is less than 20" );
		end

		print("value of a is :", a);
	
	-- When you build and run the above code, it produces the following result.
	--[[
		a is less than 20
		value of a is : 10
	]]


--[[
	6.2 if...else statement
]]
	-- An if statement can be followed by an optional else statement
	-- which executes when the Boolean expression is false.

	-- Syntax
	-- The syntax of an if...else statement in Lua programming language is −
	--[[
		if(boolean_expression) then
			--[ statement(s) will execute if the boolean expression is true --]
		else
			--[ statement(s) will execute if the boolean expression is false --]
		end
	]]

	-- If the Boolean expression evaluates to true, then the if block of code will be executed,
	-- otherwise else block of code will be executed.

	-- Lua programming language assumes any combination of Boolean true and non-nil values as true,
	-- and if it is either Boolean false or nil, then it is assumed as false value.
	-- It is to be noted that in Lua, zero will be considered as true.

	-- Flow Diagram

		-- Reference if_else_statement.jpg file

	-- Example
		--[ local variable definition --]
		a = 100;

		--[ check the boolean condition --]
		if( a < 20 ) then
			--[ if condition is true then print the following --]
			print("a is less than 20" )
		else
			--[ if condition is false then print the following --]
			print("a is not less than 20" )
		end

		print("value of a is :", a)
	
	-- When you build and run the above code, it produces the following result.
	--[[
		a is not less than 20
		value of a is :	100
	]]

--[[
	6.2.1 The if...else if...else Statement
]]	
	-- An if statement can be followed by an optional else if...else statement,
	-- which is very useful to test various conditions using single if...else if statement.

	-- While using if , else if , else statements, there are a few points to keep in mind −
		-- * An if can have zero or one else's and it must come after any else if's.
		-- * An if can have zero to many else if's and they must come before the else.
		-- * Once an else if succeeds, none of the remaining else if's or else's will be tested.

	-- Syntax
	-- The syntax of an if...else if...else statement in Lua programming language is −

		if(boolean_expression 1) then
			--[ Executes when the boolean expression 1 is true --]
		else if( boolean_expression 2)
			--[ Executes when the boolean expression 2 is true --]
		else if( boolean_expression 3)
			--[ Executes when the boolean expression 3 is true --]
		else 
			--[ executes when the none of the above condition is true --]
		end
	
	-- Example
		--[ local variable definition --]
		a = 100

		--[ check the boolean condition --]
		if( a == 10 ) then
			--[ if condition is true then print the following --]
			print("Value of a is 10" )
		else if( a == 20 ) then   
			--[ if else if condition is true --]
			print("Value of a is 20" )
		else if( a == 30 ) then
			--[ if else if condition is true  --]
			print("Value of a is 30" )
		else
			--[ if none of the conditions is true --]
			print("None of the values is matching" )
		end
		
		print("Exact value of a is: ", a )

	-- When you build and run the above code, it produces the following result.
	--[[
		None of the values is matching
		Exact value of a is:	100
	]]


--[[
	6.3 Nested if statements
]]
	-- It is always legal in Lua programming to nest if-else statements, which means you can use one if or else if statement inside another if or else if statement(s).

	-- Syntax
	-- The syntax for a nested if statement is as follows −
	--[[
		if( boolean_expression 1) then
			--[ Executes when the boolean expression 1 is true --]
			if(boolean_expression 2) then
				--[ Executes when the boolean expression 2 is true --]
			end
		end
	]]

	-- You can nest else if...else in the similar way as you have nested if statement.

	-- Example
		--[ local variable definition --]
		a = 100;
		b = 200;

		--[ check the boolean condition --]
		if( a == 100 ) then
			--[ if condition is true then check the following --]
			if( b == 200 ) then
				--[ if condition is true then print the following --]
				print("Value of a is 100 and b is 200" );
			end
		end

		print("Exact value of a is :", a );
		print("Exact value of b is :", b );
	
	-- When you build and run the above code, it produces the following result.
	--[[
		Value of a is 100 and b is 200
		Exact value of a is :	100
		Exact value of b is :	200
	]]