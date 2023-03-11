#pragma once

namespace Debug { void DumpStack(lua_State *pLS); }

namespace Debug { void GetTableInfoAll(lua_State *pLS, int tableIndexInStack, OUT std::string& debugInfo); }

namespace Debug { void DumpTableInfoAll(lua_State *pLS, const char* szTableName); }
