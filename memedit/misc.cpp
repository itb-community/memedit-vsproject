#include "stdafx.h"
#include "misc.h"
#include "lua_weapon.h"
#include "lua_pawn.h"

int set_userdata_metatable(lua_State* L) {
	void* userdata = (void*)lua_touserdata(L, 1);
	luaL_argcheck(L, userdata != NULL, 1, "`userdata` expected");
	luaL_argcheck(L, lua_istable(L, 2) == TRUE, 2, "`table` expected");

	lua_setmetatable(L, 1);

	return 0;
}

void add_misc_functions(lua_State* L) {
	if (!lua_istable(L, -1))
		luaL_error(L, "add_misc_functions failed: parent table does not exist");

	if (VERBOSE)
		log(L, "Add setUserdataMetatable");
	
	lua_pushstring(L, "setUserdataMetatable");
	lua_pushcfunction(L, set_userdata_metatable);
	lua_rawset(L, -3);
}
