#ifndef LUA_OBJ_H
#define LUA_OBJ_H

#include "lua.hpp"

class lua_obj {
public:
	lua_obj(lua_State* L);
	lua_obj(lua_State* L, int index);
	lua_obj();
	~lua_obj();

	static bool isSafe();

	lua_State* getLuaState();
	void*** getUserdata();
	size_t getAddr();

	template <typename type>
	type read(size_t delta);
	template <typename type>
	void write(size_t delta, type value);
	template <typename type>
	int set(int index);
	template <typename type>
	int get();
protected:
	lua_State* L;
	void*** userdata;
	size_t addr;
};

template <typename type>
type def();

#endif
