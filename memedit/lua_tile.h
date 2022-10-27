#ifndef LUA_TILE_H
#define LUA_TILE_H

#include "lua.hpp"
#include "lua_obj.h"

// forward declaration
class lua_board;

class lua_tile : public lua_obj {
public:
	static size_t rows_delta;   // Delta to list of rows
	static size_t rows_step;    // Step between each row
	static size_t tile_size;    // Size of a tile object
	int x;
	int y;

	lua_tile(lua_State* L, int index);
	~lua_tile();

	static bool isSafe();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
