#include "stdafx.h"
#include "lua_space_damage.h"
#include "lua_vector.h"

size_t lua_space_damage::space_damage_size = NULL;

/*
	Creates an object based on the space damage at
	the given valid index; which can be used to
	easily manipulate its associated memory values.
*/
lua_space_damage::lua_space_damage(lua_State* L, int index) : lua_obj(L)
{
	luaL_checktype(L, index, LUA_TUSERDATA);
	userdata = (void***)lua_touserdata(L, index);

	if ( userdata == NULL )
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_space_damage::~lua_space_damage() {}

template <typename type>
int lua_space_damage::get(lua_State* L)
{
	return lua_space_damage(L, 1).get<type>();
}
template <typename type>
int lua_space_damage::set(lua_State* L)
{
	return lua_space_damage(L, 1).set<type>(2);
}

template int lua_space_damage::get<int>(lua_State* L);
template int lua_space_damage::get<unsigned int>(lua_State* L);
template int lua_space_damage::get<unsigned char>(lua_State* L);
template int lua_space_damage::get<double>(lua_State* L);
template int lua_space_damage::get<const char*>(lua_State* L);
template int lua_space_damage::get<bool>(lua_State* L);
template int lua_space_damage::get<IntList>(lua_State* L);
template int lua_space_damage::get<SharedVoidPtrList>(lua_State* L);

template int lua_space_damage::set<int>(lua_State* L);
template int lua_space_damage::set<unsigned int>(lua_State* L);
template int lua_space_damage::set<unsigned char>(lua_State* L);
template int lua_space_damage::set<double>(lua_State* L);
template int lua_space_damage::set<const char*>(lua_State* L);
template int lua_space_damage::set<bool>(lua_State* L);
template int lua_space_damage::set<IntList>(lua_State* L);
template int lua_space_damage::set<SharedVoidPtrList>(lua_State* L);
