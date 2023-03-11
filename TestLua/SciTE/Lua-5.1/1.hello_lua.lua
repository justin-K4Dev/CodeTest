--[[
	1. Hello Lua
]]

--[[
	1.1 What is Lua?
]]
	-- In case you didn't already know, Lua is an interpreted programming language.
	-- It's fast, flexible, embeddable, simple, and easy to learn.
	-- You can get Lua from its download page.
	-- URL: http://www.lua.org/download.html

	-- To keep with the tradition, our first program in Lua just prints "Hello World":

		print("Hello World")

	-- If you are using the stand-alone Lua interpreter,
	-- all you have to do to run your first program is to call the interpreter (usually named lua)
	-- with the name of the text file that contains your program.
	-- For instance, if you write the above program in a file hello.lua,
	-- the following command should run it:

		-- prompt> lua hello.lua
		-- prompt> Hello World

	-- This is a very handy tool for learning and experimentation.
	-- Here's an example:

		x = 0
		while x < 10 do
			x = x + 2
			print(x)
		end
		return x

		--[[
			output:
				2
				4
				6
				8
				10
				10
		]]

--[[
	1.2 General Syntax
]]
	-- There's a small example of Lua syntax. Lua doesn't use semicolons, nor curly braces.
	-- However, it does have braces of a sort in the form of keywords like then and do.
	-- The code above also demonstrates conditional statements.

		function doSomething()
			return
		end

		if state == 5 then
			doSomething()	-- this is a line comment
		else if foo then
			a = true
		else
			b = false
		end

	-- A comment starts anywhere with a double hyphen (--) and runs until the end of the line.
	-- Lua also offers block comments, which start with --[[ and run until the corresponding ]].
	-- A common trick, when we want to comment out a piece of code,
	-- is to write the following:

		--[[
			print(10)	-- no action (comment)
		--]]

		-- Now, if we add a single hyphen to the first line, the code is in again:

		---[[ dsaf
		print(10)		--> 10
		--]]

	-- In the first example, the -- in the last line is still inside the block comment.
	-- In the second example, the sequence ---[[ does not start a block comment;
	-- so, the print is outside comments.
	-- In this case, the last line becomes an independent comment, as it starts with --.	


--[[
	1.3. Some Lexical Conventions
]]
	-- Identifiers in Lua can be any string of letters, digits, and underscores, not beginning with a digit;
	-- for instance

		-- i      j       i10      _ij
		-- aSomewhatLongName    _INPUT

	-- You should avoid identifiers starting with an underscore followed by one or more uppercase letters (e.g., _VERSION);
	-- they are reserved for special uses in Lua.
	-- Usually, I reserve the identifier _ (a single underscore) for a dummy variable.

		print("Lua current version: ",  _VERSION)

	-- In Lua, the concept of what is a letter is locale dependent.
	-- Therefore, with a proper locale, you can use variable names such as indice or acao.
	-- However, such names will make your program unsuitable to run in systems that do not support that locale.

	-- The following words are reserved;
	-- we cannot use them as identifiers:

		-- and       break     do        else      elseif
		-- end       false     for       function  if
		-- in        local     nil       not       or
		-- repeat    return    then      true      until
		-- while

	-- Lua is case-sensitive: and is a reserved word,
	-- but And and AND are two other different identifiers.




























