#include "stdafx.h"
#include "Function.h"

#include "Lua.h"


namespace LuaOOP
{
	#define BITS_PER_WORD	(CHAR_BIT * sizeof(int))

	#define I_WORD(i)		((unsigned int)(i)) / BITS_PER_WORD

	#define I_BIT(i)		(1 << ((unsigned int)(i) % BITS_PER_WORD))

	struct NumArray
	{
		int size;
		unsigned int valueList[1];
	};

	int newArray(lua_State* pLS)
	{
		// Check whether the first argument is an integer
		// And whether the value of the parameter is greater than or equal to 1.
		int n = luaL_checkint(pLS, 1);

		luaL_argcheck(pLS, n >= 1, 1, "invalid size.");

		size_t nbytes = sizeof(NumArray) + I_WORD(n - 1) * sizeof(int);

		// Parameter representation Lua by userdata Number of bytes allocated
		// At the same time will be assigned after the userdata Object pressed into the stack
		NumArray* pArray = (NumArray*)lua_newuserdata(pLS, nbytes);

		pArray->size = n;

		for (int i = 0; i < I_WORD(n - 1); ++i) {
			pArray->valueList[i] = 0;
		}

		// Get registry variables myarray, this key The value of metatable
		luaL_getmetatable(pLS, "Book.array");

		// Take userdata The meta table is set to myarray Associated table
		// At the same time the top element of the stack
		lua_setmetatable(pLS, -2);

		return 1;
	}

	uint32_t* getIndex(lua_State* pLS, uint32_t *pMask)
	{
		NumArray* pArray = (NumArray*)luaL_checkudata(pLS, 1, "Book.array");

		luaL_argcheck(pLS, pArray != NULL, 1, "'Book.array' expected.");

		int index = luaL_checkint(pLS, 2) - 1;

		luaL_argcheck(pLS, 0 <= index && index < pArray->size, 2, "index out of range.");

		*pMask = I_BIT(index);

		return &pArray->valueList[I_WORD(index)];
	}

	int setArray(lua_State* pLS)
	{
		uint32_t mask;
		uint32_t *entry = getIndex(pLS, &mask);

		luaL_checkany(pLS, 3);

		if (lua_toboolean(pLS, 3)) {
			*entry |= mask;
		}
		else {
			*entry &= ~mask;
		}

		return 0;
	}

	int getArray(lua_State* pLS)
	{
		uint32_t mask;
		uint32_t *entry = getIndex(pLS, &mask);

		lua_pushboolean(pLS, *entry & mask);

		return 1;

	}

	int getSize(lua_State* pLS)
	{
		NumArray* pArray = (NumArray*)luaL_checkudata(pLS, 1, "Book.array");

		luaL_argcheck(pLS, pArray != NULL, 1, "'Book.array' expected.");

		lua_pushinteger(pLS, pArray->size);

		return 1;
	}

	int array2string(lua_State* pLS)
	{
		NumArray* pArray = (NumArray*)luaL_checkudata(pLS, 1, "Book.array");

		luaL_argcheck(pLS, pArray != NULL, 1, "'Book.array' expected.");

		lua_pushfstring(pLS, "array(%d)", pArray->size);

		return 1;
	}

	static luaL_Reg arrayLib_f[] = {

		{ "new", newArray }
		,{ NULL, NULL } // print(a) time Lua Would call the meta method
	};
	
	static luaL_Reg arrayLib_m[] = {

			{ "set", setArray }
		,	{ "get", getArray }
		,	{ "size", getSize }
		,	{ "__tostring", array2string }
		,	{ NULL, NULL } // print(a) time Lua Would call the meta method
	};

	int register_array(lua_State* pLS)
	{
		luaL_newmetatable(pLS, "Book.array");

		lua_pushstring(pLS, "__index");
		lua_pushvalue(pLS, -2);	// pushes the metatable
		lua_settable(pLS, -3);	// metatable.__index = metatable !!!

		luaL_register(pLS, NULL, arrayLib_m);
		luaL_register(pLS, "array", arrayLib_f);

		return 1;
	}

	void lua_oop_use()
	{
		try {
			lua_State *pLS = luaL_newstate();
			if (nullptr == pLS) {
				std::cout << "Lua state assign failed" << std::endl;
				return;
			}

			// load all lua standard libraries
			luaL_openlibs(pLS);

			register_array(pLS);

			char luaFilename[] = { "./lua_oop.lua" };

			// run the script : luaL_loadfile() + lua_pcall() !!!
			if (luaL_dofile(pLS, luaFilename)) {
				throw Lua::LuaError(pLS);
			}

			lua_close(pLS);
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}

		system("pause");
	}


	void Test()
	{
		lua_oop_use();
	}
}