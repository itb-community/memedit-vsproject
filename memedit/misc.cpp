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

int remove_weapon(lua_State* L) {
	lua_weapon weapon = lua_weapon(L, 1);
	weapon.remove();

	return 0;
}

int get_weapon_count(lua_State* L) {
	lua_pawn pawn = lua_pawn(L, 1);
	// "Move" is in the weapon list.
	// Subtract 1 to get true weapon count.
	lua_pushinteger(L, pawn.getWeaponCount() - 1);

	return 1;
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

void add_misc_weapon_functions(lua_State* L) {
	if (!lua_istable(L, -1))
		luaL_error(L, "add_misc_functions failed: parent table does not exist");

	if (VERBOSE) {
		log(L, "Add removeWeapon");
		log(L, "Add getWeaponCount");
	}

	lua_pushstring(L, "removeWeapon");
	lua_pushcfunction(L, remove_weapon);
	lua_rawset(L, -3);

	lua_pushstring(L, "getWeaponCount");
	lua_pushcfunction(L, get_weapon_count);
	lua_rawset(L, -3);
}
