#ifndef LUA_SPACEDAMAGE_H
#define LUA_SPACEDAMAGE_H

#include "lua.hpp"
#include "lua_obj.h"

class lua_space_damage : public lua_obj
{
public:
	static size_t space_damage_size; // Size of a space damage object

	lua_space_damage(lua_State* L, int index);
	~lua_space_damage();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
