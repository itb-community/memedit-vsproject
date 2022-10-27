#ifndef LUA_FUNCTION_H
#define LUA_FUNCTION_H

#include "lua.hpp"

struct LuaFunction {
	std::string name;
	lua_CFunction func;
	static int get_default(lua_State* L);
	static int set_default(lua_State* L);
};

#endif
