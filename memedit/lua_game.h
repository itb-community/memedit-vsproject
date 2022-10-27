#ifndef LUA_GAME_H
#define LUA_GAME_H

#include "lua.hpp"
#include "lua_obj.h"

class lua_game : public lua_obj {
public:
	lua_game(lua_State* L);
	~lua_game();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
