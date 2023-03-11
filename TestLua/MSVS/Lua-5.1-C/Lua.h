#pragma once

namespace Lua
{
	class LuaError : public std::exception
	{
	protected:
		lua_State* m_pLS;

		std::shared_ptr<lua_State> m_luaResource;

		LuaError& operator=(const LuaError& other);
	
	public:
		LuaError(lua_State* pLS);
		LuaError(const LuaError& other);
		virtual ~LuaError();

		virtual const char * what() const throw();
	};

	int ErrorReport(lua_State* pLS, int state);

	void Error(lua_State* pLS, const char* format, ...);

	// jump point
	static std::jmp_buf HandleExceptionJump;

	// custom panic handler
	static int HandleException(lua_State *pLS)
	{
		printf("Lua Error: call panic - %s\n", lua_tostring(pLS, -1));

		longjmp(HandleExceptionJump, 1);
		/* will never return */

		return 0;
	}

	void Execute(lua_State* pLS, const char* pFuncName, const char* szSignature, ...);
}