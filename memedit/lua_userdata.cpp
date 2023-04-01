#include "stdafx.h"
#include "lua_userdata.h"
#include "lua_vector.h"

/*
	Creates an object based on the userdata at
	the given valid index; which can be used to
	easily manipulate its associated memory values.
*/
lua_userdata::lua_userdata(lua_State* L, int index) : lua_obj(L)
{
	luaL_checktype(L, index, LUA_TUSERDATA);
	userdata = (void***)lua_touserdata(L, index);

	if ( userdata == NULL )
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_userdata::~lua_userdata() {}

template <typename type>
int lua_userdata::get(lua_State* L)
{
	return lua_userdata(L, 1).get<type>();
}
template <typename type>
int lua_userdata::set(lua_State* L)
{
	return lua_userdata(L, 1).set<type>(2);
}

template int lua_userdata::get<int>(lua_State* L);
template int lua_userdata::get<unsigned int>(lua_State* L);
template int lua_userdata::get<unsigned char>(lua_State* L);
template int lua_userdata::get<double>(lua_State* L);
template int lua_userdata::get<const char*>(lua_State* L);
template int lua_userdata::get<bool>(lua_State* L);
template int lua_userdata::get<IntList>(lua_State* L);
template int lua_userdata::get<SharedVoidPtrList>(lua_State* L);

template int lua_userdata::set<int>(lua_State* L);
template int lua_userdata::set<unsigned int>(lua_State* L);
template int lua_userdata::set<unsigned char>(lua_State* L);
template int lua_userdata::set<double>(lua_State* L);
template int lua_userdata::set<const char*>(lua_State* L);
template int lua_userdata::set<bool>(lua_State* L);
template int lua_userdata::set<IntList>(lua_State* L);
template int lua_userdata::set<SharedVoidPtrList>(lua_State* L);
