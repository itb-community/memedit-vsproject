#include "stdafx.h"
#include "lua_board.h"
#include "lua_tile.h"

/*
	Creates an object with the address of the Board
	userdata object; which can be used to easily
	manipulate its associated memory values.
*/
lua_board::lua_board(lua_State* L) : lua_obj(L) {
	lua_getglobal(L, "Board");
	luaL_checktype(L, -1, LUA_TUSERDATA);

	userdata = (void***)lua_touserdata(L, -1);

	lua_pop(L, 1);

	if (userdata == NULL)
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_board::~lua_board() {}

template <typename type>
int lua_board::get(lua_State* L) {
	return lua_board(L).get<type>();
}
template <typename type>
int lua_board::set(lua_State* L) {
	return lua_board(L).set<type>(1);
}

template int lua_board::get<int>(lua_State* L);
template int lua_board::get<unsigned int>(lua_State* L);
template int lua_board::get<unsigned char>(lua_State* L);
template int lua_board::get<double>(lua_State* L);
template int lua_board::get<const char*>(lua_State* L);
template int lua_board::get<bool>(lua_State* L);

template int lua_board::set<int>(lua_State* L);
template int lua_board::set<unsigned int>(lua_State* L);
template int lua_board::set<unsigned char>(lua_State* L);
template int lua_board::set<double>(lua_State* L);
template int lua_board::set<const char*>(lua_State* L);
template int lua_board::set<bool>(lua_State* L);
