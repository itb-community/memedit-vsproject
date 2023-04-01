#ifndef LUA_USERDATA_H
#define LUA_USERDATA_H

#include "lua.hpp"
#include "lua_obj.h"

class lua_userdata : public lua_obj
{
public:
	lua_userdata(lua_State* L, int index);
	~lua_userdata();

	using lua_obj::get;
	using lua_obj::set;

	template <typename type>
	static int get(lua_State* L);
	template <typename type>
	static int set(lua_State* L);
};

#endif
