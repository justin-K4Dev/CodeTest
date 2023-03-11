#include "stdafx.h"
#include "Function.h"

#include "Lua.h"


namespace LuaUserData
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

		return 1;
	}

	int setArray(lua_State* pLS)
	{
		// Lua The first argument passed to the function must be userdata
		// The meta table for this object must also be in the registry myarray Associated table.

		// Otherwise the function fails and terminates the program
		NumArray* pArray = (NumArray*)lua_touserdata(pLS, 1);

		int index = luaL_checkint(pLS, 2) - 1;

		// Because any type of data can be Boolean,
		// So here used any Just to make sure that there is 3 One parameter ¡£
		luaL_checkany(pLS, 3);

		luaL_argcheck(pLS, pArray != NULL, 1, "'array' expected.");

		luaL_argcheck(pLS, 0 <= index && index < pArray->size, 2, "index out of range.");

		if (lua_toboolean(pLS, 3)) {
			pArray->valueList[I_WORD(index)] |= I_BIT(index);
		}
		else {
			pArray->valueList[I_WORD(index)] &= ~I_BIT(index);
		}

		return 0;
	}

	int getArray(lua_State* pLS)
	{
		NumArray* pArray = (NumArray*)lua_touserdata(pLS, 1);

		int index = luaL_checkint(pLS, 2) - 1;

		luaL_argcheck(pLS, pArray != NULL, 1, "'array' expected.");

		luaL_argcheck(pLS, 0 <= index && index < pArray->size, 2, "index out of range");

		lua_pushboolean(pLS, pArray->valueList[I_WORD(index)] & I_BIT(index));

		return 1;

	}

	int getSize(lua_State* pLS)
	{
		NumArray* pArray = (NumArray*)lua_touserdata(pLS, 1);

		luaL_argcheck(pLS, pArray != NULL, 1, "'array' expected.");

		lua_pushinteger(pLS, pArray->size);

		return 1;
	}

	static luaL_Reg arrayLib[] = {

			{ "new", newArray }
		, 	{ "set", setArray }
		,	{ "get", getArray }
		,	{ "size", getSize }
		,	{ NULL, NULL } // print(a) time Lua Would call the meta method
	};

	void user_data_use()
	{
		lua_State *pLS = luaL_newstate();
		if (nullptr == pLS) {
			std::cout << "Lua state assign failed" << std::endl;
			return;
		}

		// load all lua standard libraries
		luaL_openlibs(pLS);

		luaL_register(pLS, "array", arrayLib);

		char luaFilename[] = { "./lua_user_data.lua" };

		// run the script : luaL_loadfile() + lua_pcall() !!!
		if (luaL_dofile(pLS, luaFilename)) {
			throw Lua::LuaError(pLS);
		}

		lua_close(pLS);

		system("pause");
	}


	void Test()
	{
		user_data_use();
	}
}