#ifndef LUA_PAWN_H
#define LUA_PAWN_H

#include "lua.hpp"
#include "lua_obj.h"

typedef std::shared_ptr<void*> Weapon;
typedef std::vector<Weapon>* WeaponList;

class lua_pawn : public lua_obj {
public:
	static size_t weapon_list_delta;
	WeaponList getWeaponList();

	lua_pawn(lua_State* L, int index);
	~lua_pawn();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
