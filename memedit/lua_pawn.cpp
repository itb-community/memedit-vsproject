#include "stdafx.h"
#include "lua_pawn.h"
#include "log.h"

size_t lua_pawn::weapon_list_delta = NULL;

/*
	Creates an object based on the userdata at
	the given valid index, or the pawn with the id
	at the given valid index; which can be used to
	easily manipulate its associated memory values.
*/
lua_pawn::lua_pawn(lua_State* L, int index) : lua_obj(L) {
	if (!lua_isuserdata(L, index)) {
		luaL_checkint(L, index);
		lua_getglobal(L, "Game");

		if (lua_isnil(L, -1))
			luaL_error(L, "'Game' does not exist");

		lua_getfield(L, -1, "GetPawn");
		lua_insert(L, -2);
		lua_pushvalue(L, index);
		lua_remove(L, index);
		lua_call(L, 2, 1);
		lua_insert(L, index);
	}

	luaL_checktype(L, index, LUA_TUSERDATA);
	userdata = (void***)lua_touserdata(L, index);

	if (userdata == NULL)
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_pawn::~lua_pawn() {}

WeaponList lua_pawn::getWeaponList() {
	void* addr_weapons = (void*)(addr + lua_pawn::weapon_list_delta);
	return static_cast<WeaponList>(addr_weapons);
}

size_t lua_pawn::getWeaponCount() {
	return getWeaponList()->size();
}

template <typename type>
int lua_pawn::get(lua_State* L) {
	return lua_pawn(L, 1).get<type>();
}
template <typename type>
int lua_pawn::set(lua_State* L) {
	return lua_pawn(L, 1).set<type>(2);
}

template int lua_pawn::get<int>(lua_State* L);
template int lua_pawn::get<unsigned int>(lua_State* L);
template int lua_pawn::get<unsigned char>(lua_State* L);
template int lua_pawn::get<double>(lua_State* L);
template int lua_pawn::get<const char*>(lua_State* L);
template int lua_pawn::get<bool>(lua_State* L);

template int lua_pawn::set<int>(lua_State* L);
template int lua_pawn::set<unsigned int>(lua_State* L);
template int lua_pawn::set<unsigned char>(lua_State* L);
template int lua_pawn::set<double>(lua_State* L);
template int lua_pawn::set<const char*>(lua_State* L);
template int lua_pawn::set<bool>(lua_State* L);
