#include "stdafx.h"

namespace Example
{
	static int l_list_push(lua_State *pLS)
	{ // Push elements from LUA
		assert(lua_gettop(pLS) == 2); // check that the number of args is exactly 2

		std::list<int> **ud = static_cast<std::list<int>**>(luaL_checkudata(pLS, 1, "ListMT")); // first arg is the list
		
		int v = luaL_checkint(pLS, 2); // seconds argument is the integer to be pushed to the std::list<int>
		(*ud)->push_back(v); // perform the push on C++ object through the pointer stored in user data
		
		return 0; // we return 0 values in the lua stack
	}

	static int l_list_pop(lua_State *pLS)
	{
		assert(lua_gettop(pLS) == 1); // check that the number of args is exactly 1
		
		Debug::DumpStack(pLS);

		std::list<int> **ud = static_cast<std::list<int>**>(luaL_checkudata(pLS, 1, "ListMT")); // first arg is the userdata
		if ((*ud)->empty()) {
			lua_pushnil(pLS);
			return 1; // if list is empty the function will return nil
		}
		lua_pushnumber(pLS, (*ud)->front()); // push the value to pop in the lua stack
										   // it will be the return value of the function in lua
		(*ud)->pop_front(); // remove the value from the list
		
		return 1; //we return 1 value in the stack
	}

	class LuaWrapper
	{
	public:
		LuaWrapper();
		virtual ~LuaWrapper();

		void run();

	private:
		lua_State *m_pLS;
		std::list<int> m_list;

		void registerListType();
		void runScript();
	};

	LuaWrapper::LuaWrapper()
	{
		m_pLS = luaL_newstate();
		luaL_openlibs(m_pLS);
	}

	LuaWrapper::~LuaWrapper()
	{
		lua_close(m_pLS);
	}

	void LuaWrapper::runScript()
	{
		lua_settop(m_pLS, 0); // empty the lua stack
		if (luaL_dofile(m_pLS, "./lua_list.lua")) {
			fprintf(stderr, "error: %s\n", lua_tostring(m_pLS, -1));
			Debug::DumpStack(m_pLS);
			lua_pop(m_pLS, 1);
			exit(1);
		}
		assert(lua_gettop(m_pLS) == 0); //empty the lua stack
	}

	void LuaWrapper::registerListType()
	{
		std::cout << "Set the list object in lua" << std::endl;

		luaL_newmetatable(m_pLS, "ListMT");
		Debug::DumpStack(m_pLS);

		lua_pushvalue(m_pLS, -1);
		Debug::DumpStack(m_pLS);

		lua_setfield(m_pLS, -2, "__index"); // ListMT .__index = ListMT
		Debug::DumpStack(m_pLS);

		lua_pushcfunction(m_pLS, l_list_push);
		Debug::DumpStack(m_pLS);

		lua_setfield(m_pLS, -2, "push"); // push in lua will call l_list_push in C++
		Debug::DumpStack(m_pLS);

		lua_pushcfunction(m_pLS, l_list_pop);
		Debug::DumpStack(m_pLS);

		lua_setfield(m_pLS, -2, "pop"); // pop in lua will call l_list_pop in C++
		Debug::DumpStack(m_pLS);
	}

	void LuaWrapper::run()
	{
		for (unsigned int i = 0; i < 10; i++) {
			// add some input data to the list
			m_list.push_back(i * 100);
		}

		registerListType();
		
		std::cout << "creating an instance of std::list in lua" << std::endl;
		std::list<int> **ud = static_cast<std::list<int>**>(lua_newuserdata(m_pLS, sizeof(std::list<int>*)));
		*(ud) = &m_list;

		luaL_getmetatable(m_pLS, "ListMT");
		Debug::DumpStack(m_pLS);

		lua_setmetatable(m_pLS, -2);
		Debug::DumpStack(m_pLS);

		lua_setglobal(m_pLS, "list_container"); // list_container in lua points to the new userdata
		Debug::DumpStack(m_pLS);

		runScript();

		while (!m_list.empty()) {
			// read the data that lua left in the list
			std::cout << "from C++: pop value " << m_list.front() << std::endl;
			m_list.pop_front();
		}
	}

	void lua_list_example()
	{
		LuaWrapper lw;

		lw.run();

		system("pause");
	}

	void LuaListTest()
	{
		lua_list_example();
	}
}