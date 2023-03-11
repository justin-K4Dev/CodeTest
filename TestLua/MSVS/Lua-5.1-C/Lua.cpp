#include "stdafx.h"
#include "Lua.h"

#include "Debug.h"

namespace Lua
{
	static void delete_lua_resource(lua_State* pLS)
	{
		lua_pop(pLS, 1);
	}

	LuaError::LuaError(lua_State* pLS)
	: m_pLS(pLS), m_luaResource(pLS, delete_lua_resource)
	{
	}
	LuaError::LuaError(const LuaError& other)
	: m_pLS(other.m_pLS), m_luaResource(other.m_luaResource)
	{
	}
	LuaError::~LuaError()
	{
	}

	LuaError& LuaError::operator=(const LuaError& other)
	{
		if (this != &other) {
			this->m_pLS = other.m_pLS;
			this->m_luaResource = other.m_luaResource;
		}

		return *this;
	}

	const char* LuaError::what() const throw()
	{
		const char * s = lua_tostring(m_pLS, -1);
		if (NULL == s) {
			s = "unrecognized Lua error !!!";
		}
		return s;
	}

	int ErrorReport(lua_State* pLS, int state)
	{
		if (state && !lua_isnil(pLS, -1)) {
			const char* msg = lua_tostring(pLS, -1);
			if (nullptr == msg) {
				msg = "error object is not string";
			}

			lua_getfield(pLS, LUA_GLOBALSINDEX, "debug");
			Debug::DumpStack(pLS);
			if (!lua_istable(pLS, -1)) {
				lua_pop(pLS, 1);
				return 1;
			}

			lua_getfield(pLS, -1, "traceback");
			Debug::DumpStack(pLS);
			if (!lua_isfunction(pLS, -1)) {
				lua_pop(pLS, 2);
				return 1;
			}

			lua_pushvalue(pLS, 1);
			lua_pushinteger(pLS, 2);
			Debug::DumpStack(pLS);
			lua_call(pLS, 2, 1);
			Debug::DumpStack(pLS);

			printf("Lua Error: %s\n", lua_tostring(pLS, -1));
			lua_pop(pLS, 1);
		}

		return 0;
	}

	void Error(lua_State* pLS, const char* format, ...)
	{
		va_list argList;

		va_start(argList, format);

		vfprintf(stderr, format, argList);
		if (nullptr != format) {
			fprintf(stderr, ", ");
		}
		fprintf(stderr, "LuaError:%s", lua_tostring(pLS, -1));

		va_end(argList);

		lua_close(pLS);

		system("pause");

		exit(EXIT_FAILURE);
	}

	void Execute(lua_State* pLS, const char* pFuncName, const char* szSignature, ...)
	{
		va_list vl;

		va_start(vl, szSignature);

		lua_getglobal(pLS, pFuncName);

		// parse argument
		for ( int argCount = 0; *szSignature; ++argCount ) {
			
			// check stack state
			luaL_checkstack( pLS, 1, "too many arguments !!!" );

			switch (*szSignature++) {

			case 'd' :
				lua_pushnumber(pLS, va_arg(vl, double));
				break;
			
			case 'i':
				lua_pushinteger(pLS, va_arg(vl, int));
				break;

			case 's':
				lua_pushstring(pLS, va_arg(vl, char*));
				break;

			case '>':
				goto ArgEnd;
			
			default:
				Error(pLS, "invalid option (%c)", *(szSignature - 1));

			}
		}

	ArgEnd:
		int retCount = 0;
		retCount = -retCount;
		while (*szSignature) {

			switch (*szSignature++) {
			case 'd':
				if (!lua_isnumber(pLS, retCount)) {
					Error(pLS, "wrong result type");
				}

				*va_arg(vl, double*) = lua_tonumber(pLS, retCount);
				break;

			case 'i':
				if (!lua_isnumber(pLS, retCount)) {
					Error(pLS, "wrong result type");
				}

				*va_arg(vl, int*) = lua_tointeger(pLS, retCount);
				break;

			case 's':
				if (!lua_isstring(pLS, retCount)) {
					Error(pLS, "wrong result type");
				}

				*va_arg(vl, const char**) = lua_tostring(pLS, retCount);
				break;

			default:
				Error(pLS, "invalid option (%c)", *(szSignature - 1));
				break;
			}

			retCount++;
		}
	}
}