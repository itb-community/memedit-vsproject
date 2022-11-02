#ifndef LUA_WEAPON_H
#define LUA_WEAPON_H

#include "lua.hpp"
#include "lua_obj.h"

typedef std::shared_ptr<void*> Weapon;
typedef std::vector<Weapon>* WeaponList;

class lua_weapon : public lua_obj {
public:
	WeaponList weaponList;
	size_t weaponIndex;
	Weapon weapon;

	lua_weapon(lua_State* L, int index);
	~lua_weapon();

	static bool isSafe();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
