#include "stdafx.h"
#include "lua_function.h"
#include "lua.hpp"

int LuaFunction::get_default(lua_State* L) {
	lua_pushnil(L);
	return 1;
}
int LuaFunction::set_default(lua_State* L) {
	return 0;
}
