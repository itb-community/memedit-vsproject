#include "stdafx.h"
#include "lua_vector.h"

template <>
const char* lua_vector<IntList>::name() {
	return "IntList";
}
template <>
const char* lua_vector<SharedVoidPtrList>::name() {
	return "SharedVoidPtrList";
}

template <typename type>
int lua_vector<type>::size(lua_State* L) {
	auto &udata = *(lua_vector<type>*)luaL_checkudata(L, 1, lua_vector<type>::name());
	lua_pushinteger(L, udata.list->size());
	return 1;
}
template <typename type>
int lua_vector<type>::erase(lua_State* L) {
	auto &udata = *(lua_vector<type>*)luaL_checkudata(L, 1, lua_vector<type>::name());
	size_t index = luaL_checkinteger(L, 2);

	if (index < udata.list->size())
		udata.list->erase(udata.list->begin()+index);
	else
		luaL_error(L, "index is out of bounds");

	return 0;
}
template <typename type>
int lua_vector<type>::at(lua_State* L) {
	luaL_error(L, "illegal operation");

	return 0;
}
template <>
int lua_vector<IntList>::at(lua_State* L) {
	auto &udata = *(lua_vector<IntList>*)luaL_checkudata(L, 1, "IntList");
	size_t index = luaL_checkinteger(L, 2);

	if (index < udata.list->size())
		lua_pushinteger(L, udata.list->at(index));
	else
		luaL_error(L, "index is out of bounds");

	return 1;
}

template <typename type>
int lua_vector<type>::index(lua_State* L) {
	luaL_checkudata(L, 1, lua_vector<type>::name());
	const std::string key = luaL_checkstring(L, 2);
	int result = 1;

	if (key == "size")
		lua_pushcfunction(L, lua_vector<type>::size);

	else if (key == "erase")
		lua_pushcfunction(L, lua_vector<type>::erase);

	else if (key == "at")
		lua_pushcfunction(L, lua_vector<type>::at);
	else
		result = 0;

	return result;
}

template int lua_vector<IntList>::index(lua_State* L);
template int lua_vector<SharedVoidPtrList>::index(lua_State* L);

template <typename type>
int lua_vector<type>::createMetatable(lua_State* L) {
	luaL_newmetatable(L, lua_vector<type>::name());
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, lua_vector<type>::index);
	lua_settable(L, -3);
	lua_pop(L, 1);
	return 0;
}

template int lua_vector<IntList>::createMetatable(lua_State* L);
template int lua_vector<SharedVoidPtrList>::createMetatable(lua_State* L);
