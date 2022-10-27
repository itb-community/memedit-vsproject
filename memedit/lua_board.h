#ifndef LUA_BOARD_H
#define LUA_BOARD_H

#include "lua.hpp"
#include "lua_obj.h"

// forward declaration
class lua_tile;

class lua_board : public lua_obj {
public:
	lua_board(lua_State* L);
	~lua_board();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
