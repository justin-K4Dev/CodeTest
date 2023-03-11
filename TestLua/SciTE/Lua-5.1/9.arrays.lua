--[[
	9. Arrays
]]
	-- Arrays are ordered arrangement of objects,
	-- which may be a one dimensional array containing a collection of rows
	-- or a multi-dimensional array containing multiple rows and columns.

	-- In Lua, arrays are implemented using indexing tables with integers.
	-- The size of an array is not fixed and it can grow based on our requirements,
	-- subject to memory constraints.

--[[
	9.1 One-Dimensional Array
]]
	-- A one-dimensional array can be represented using a simple table structure
	-- and can be initialized and read using a simple for loop.
	-- An example is shown below.

		array = {"Lua", "Tutorial"}

		for i= 0, 2 do
		print(array[i])
		end
	
	-- When we run the above code, we wil get the following output.
	--[[
		nil
		Lua
		Tutorial
	]]
	
	-- As you can see in the above code,
	-- when we are trying to access an element in an index that is not there in the array,
	-- it returns nil.
	-- In Lua, indexing generally starts at index 1.
	-- But it is possible to create objects at index 0 and below 0 as well.
	-- Array using negative indices is shown below
	-- where we initialize the array using a for loop.

		array = {}

		for i= -2, 2 do
			array[i] = i * 2
		end

		for i = -2, 2 do
			print(array[i])
		end
	
	-- When we run the above code, we will get the following output.
	--[[
		-4
		-2
		0
		2
		4
	]]


--[[	
	9.2 Multi-Dimensional Array
]]
	-- Multi-dimensional arrays can be implemented in two ways.

		-- * Array of arrays
		-- * Single dimensional array by manipulating indices
	
	-- An example for multidimensional array of 3. 3 is shown below using array of arrays.

		-- Initializing the array
		array = {}
		for i = 1, 3 do
			array[i] = {}
			for j = 1, 3 do
				array[i][j] = i * j
			end
		end

		-- Accessing the array
		for i = 1, 3 do
			for j = 1, 3 do
				print(array[i][j])
			end
		end
	
	-- When we run the above code, we will get the following output.
	--[[
		1
		2
		3
		2
		4
		6
		3
		6
		9
	]]
	
	-- An example for multidimensional array is shown below using manipulating indices.

		-- Initializing the array
		array = {}
		maxRows = 3
		maxColumns = 3

		for row = 1, maxRows do
			for col = 1, maxColumns do
				array[row * maxColumns + col] = row*col
			end
		end

		-- Accessing the array
		for row = 1, maxRows do
			for col = 1, maxColumns do
				print(array[row * maxColumns + col])
			end
		end
	
	-- When we run the above code, we will get the following output.
	--[[
		1
		2
		3
		2
		4
		6
		3
		6
		9
	]]
	
	-- As you can see in the above example, data is stored based on indices.
	-- It is possible to place the elements in a sparse way and it is the way Lua implementation of a matrix works.
	-- Since it does not store nil values in Lua,
	-- it is possible to save lots of memory without any special technique in Lua
	-- as compared to special techniques used in other programming languages.