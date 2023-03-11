#pragma once

#include "stdafx.h"
#include "LuaMeta.hpp"

namespace CustomMetaData
{
	class Account
	{
	protected:
		lua_Number m_balance;

	public:
		static const char className[8];
		static Lua::LuaMeta<Account>::RegType methods[4];

		Account(lua_State *L) { m_balance = luaL_checknumber(L, 1); }
		virtual ~Account() { printf("deleted Account (%p)\n", this); }

		int deposit(lua_State *L) { m_balance += luaL_checknumber(L, 1); return 0; }
		int withdraw(lua_State *L) { m_balance -= luaL_checknumber(L, 1); return 0; }
		int balance(lua_State *L) { lua_pushnumber(L, m_balance); return 1; }
	};

	const char Account::className[] = "Account";

	Lua::LuaMeta<Account>::RegType Account::methods[] = {
		method(Account, deposit),
		method(Account, withdraw),
		method(Account, balance),
		{ 0,0 }
	};
}
