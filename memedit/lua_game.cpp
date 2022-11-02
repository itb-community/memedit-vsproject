#include "stdafx.h"
#include "lua_game.h"
#include "lua_vector.h"

/*
	Creates an object with the address of the Game
	userdata object; which can be used to easily
	manipulate its associated memory values.
*/
lua_game::lua_game(lua_State* L) : lua_obj(L) {
	lua_getglobal(L, "Game");
	luaL_checktype(L, -1, LUA_TUSERDATA);

	userdata = (void***)lua_touserdata(L, -1);

	lua_pop(L, 1);

	if (userdata == NULL)
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_game::~lua_game() {}

template <typename type>
int lua_game::get(lua_State* L) {
	return lua_game(L).get<type>();
}
template <typename type>
int lua_game::set(lua_State* L) {
	return lua_game(L).set<type>(1);
}

template int lua_game::get<int>(lua_State* L);
template int lua_game::get<unsigned int>(lua_State* L);
template int lua_game::get<unsigned char>(lua_State* L);
template int lua_game::get<double>(lua_State* L);
template int lua_game::get<const char*>(lua_State* L);
template int lua_game::get<bool>(lua_State* L);
template int lua_game::get<IntList>(lua_State* L);
template int lua_game::get<SharedVoidPtrList>(lua_State* L);

template int lua_game::set<int>(lua_State* L);
template int lua_game::set<unsigned int>(lua_State* L);
template int lua_game::set<unsigned char>(lua_State* L);
template int lua_game::set<double>(lua_State* L);
template int lua_game::set<const char*>(lua_State* L);
template int lua_game::set<bool>(lua_State* L);
template int lua_game::set<IntList>(lua_State* L);
template int lua_game::set<SharedVoidPtrList>(lua_State* L);
