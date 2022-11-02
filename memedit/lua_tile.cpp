#include "stdafx.h"
#include "lua_tile.h"
#include "lua_board.h"
#include "lua_vector.h"

size_t lua_tile::rows_delta = NULL;
size_t lua_tile::rows_step = NULL;
size_t lua_tile::tile_size = NULL;

/*
	Creates an object with the address of a tile
	on the board; which can be used to easily
	manipulate its associated memory values.
	Tile can be specified with a Point userdata,
	or with x and y integer coordinate values.
*/
lua_tile::lua_tile(lua_State* L, int index) {
	lua_board board = lua_board(L);

	if (lua_isuserdata(L, index)) {
		lua_getfield(L, index, "y");
		lua_getfield(L, index, "x");
		lua_replace(L, index);
		lua_insert(L, index + 1);
	}

	this->L = L;
	this->userdata = board.getUserdata();
	this->x = luaL_checkinteger(L, index);
	this->y = luaL_checkinteger(L, index + 1);
	// userdata can remain as the board userdata

	if (x < 0 || x > 7 || y < 0 || y > 7)
		luaL_error(L, "invalid point");
	else {
		size_t tiles_row = *(size_t*)(board.getAddr() + lua_tile::rows_delta);
		size_t tiles_column = *(size_t*)(tiles_row + lua_tile::rows_step * x);
		addr = tiles_column + lua_tile::tile_size * y;
	}
}

lua_tile::~lua_tile() {}

bool lua_tile::isSafe() {
	return (true
		&& lua_tile::rows_delta != NULL
		&& lua_tile::rows_step != NULL
		&& lua_tile::tile_size != NULL
	);
}

template <typename type>
int lua_tile::get(lua_State* L) {
	return lua_tile(L, 1).get<type>();
}
template <typename type>
int lua_tile::set(lua_State* L) {
	return lua_tile(L, 1).set<type>(3);
}

template int lua_tile::get<int>(lua_State* L);
template int lua_tile::get<unsigned int>(lua_State* L);
template int lua_tile::get<unsigned char>(lua_State* L);
template int lua_tile::get<double>(lua_State* L);
template int lua_tile::get<const char*>(lua_State* L);
template int lua_tile::get<bool>(lua_State* L);
template int lua_tile::get<IntList>(lua_State* L);
template int lua_tile::get<SharedVoidPtrList>(lua_State* L);

template int lua_tile::set<int>(lua_State* L);
template int lua_tile::set<unsigned int>(lua_State* L);
template int lua_tile::set<unsigned char>(lua_State* L);
template int lua_tile::set<double>(lua_State* L);
template int lua_tile::set<const char*>(lua_State* L);
template int lua_tile::set<bool>(lua_State* L);
template int lua_tile::set<IntList>(lua_State* L);
template int lua_tile::set<SharedVoidPtrList>(lua_State* L);
