#include "stdafx.h"
#include "lua_weapon.h"
#include "lua_pawn.h"
#include "lua_vector.h"

/*
	Creates an object based on the weapon beloning
	to the userdata at the given valid index, or
	the pawn with the id at the given valid index;
	which can be used to easily manipulate its
	associated memory values.
*/
lua_weapon::lua_weapon(lua_State* L, int index) : lua_obj(L) {
	lua_pawn pawn = lua_pawn(L, index);

	this->L = L;
	this->userdata = pawn.getUserdata();
	this->weaponIndex = luaL_checkinteger(L, index + 1);
	// userdata can remain as the pawn userdata

	weaponList = pawn.getWeaponList();

	if (weaponIndex < 1 || weaponList->size() <= weaponIndex )
		luaL_error(L, "no weapon at index");
	else {
		Weapon weapon = weaponList->at(weaponIndex);
		addr = (size_t)weapon.get();
	}
}

lua_weapon::~lua_weapon() {}

bool lua_weapon::isSafe() {
	return lua_pawn::weapon_list_delta != NULL;
}

template <typename type>
int lua_weapon::get(lua_State* L) {
	return lua_weapon(L, 1).get<type>();
}
template <typename type>
int lua_weapon::set(lua_State* L) {
	return lua_weapon(L, 1).set<type>(3);
}

template int lua_weapon::get<int>(lua_State* L);
template int lua_weapon::get<unsigned int>(lua_State* L);
template int lua_weapon::get<unsigned char>(lua_State* L);
template int lua_weapon::get<double>(lua_State* L);
template int lua_weapon::get<const char*>(lua_State* L);
template int lua_weapon::get<bool>(lua_State* L);
template int lua_weapon::get<IntList>(lua_State* L);
template int lua_weapon::get<SharedVoidPtrList>(lua_State* L);

template int lua_weapon::set<int>(lua_State* L);
template int lua_weapon::set<unsigned int>(lua_State* L);
template int lua_weapon::set<unsigned char>(lua_State* L);
template int lua_weapon::set<double>(lua_State* L);
template int lua_weapon::set<const char*>(lua_State* L);
template int lua_weapon::set<bool>(lua_State* L);
template int lua_weapon::set<IntList>(lua_State* L);
template int lua_weapon::set<SharedVoidPtrList>(lua_State* L);
