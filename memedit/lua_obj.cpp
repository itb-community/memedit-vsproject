#include "stdafx.h"
#include "lua_obj.h"
#include "lua_helpers.h"

lua_obj::lua_obj(lua_State* L) {
	this->L = L;
}

lua_obj::lua_obj(lua_State* L, int index) : lua_obj(L) {
	luaL_checktype(L, index, LUA_TUSERDATA);
	userdata = (void***)lua_touserdata(L, index);

	if (userdata == NULL)
		luaL_error(L, "invalid userdata");

	addr = (size_t)userdata[0][2];
}

lua_obj::lua_obj() {}
lua_obj::~lua_obj() {}

bool lua_obj::isSafe() { return true; }
lua_State* lua_obj::getLuaState() { return L; }
void*** lua_obj::getUserdata() { return userdata; }
size_t lua_obj::getAddr() { return addr; }

template <typename type>
type def() {
	return NULL;
}

template int def<int>();
template unsigned char def<unsigned char>();
template unsigned int def<unsigned int>();
template double def<double>();

template <>
bool def<bool>() {
	return false;
}

template <>
const char* def<const char*>() {
	return "";
}

template <typename type>
type lua_obj::read(size_t delta) {
	if (addr == NULL)
		return def<type>();

	return *(type*)(addr + delta);
}

template int lua_obj::read<int>(size_t);
template unsigned int lua_obj::read<unsigned int>(size_t);
template unsigned char lua_obj::read<unsigned char>(size_t);
template bool lua_obj::read<bool>(size_t);
template double lua_obj::read<double>(size_t);
template <>
const char* lua_obj::read<const char*>(size_t delta) {
	if (addr == NULL)
		return def<const char*>();

	return static_cast<std::string*>((void*)(addr + delta))->c_str();
}
template <>
std::string* lua_obj::read<std::string*>(size_t delta) {
	if (addr == NULL)
		return def<std::string*>();

	return static_cast<std::string*>((void*)(addr + delta));
}

template <typename type>
void lua_obj::write(size_t delta, type value) {
	if (addr == NULL)
		return;

	type* ptr = (type*)(addr + delta);
	*ptr = value;
}

template void lua_obj::write<int>(size_t, int);
template void lua_obj::write<unsigned int>(size_t, unsigned int);
template void lua_obj::write<unsigned char>(size_t, unsigned char);
template void lua_obj::write<bool>(size_t, bool);
template void lua_obj::write<double>(size_t, double);
template <>
void lua_obj::write<const char*>(size_t delta, const char* value) {
	if (addr == NULL)
		return;

	std::string new_string(value);
	std::string* ptr = static_cast<std::string*>((void*)(addr + delta));
	*ptr = new_string;
}
template <>
void lua_obj::write<std::string*>(size_t delta, std::string* value) {
	if (addr == NULL)
		return;

	std::string* ptr = static_cast<std::string*>((void*)(addr + delta));
	*ptr = *value;
}

template <typename type>
int lua_obj::get() {
	lua_pop(L, lua_gettop(L));
	size_t delta = lua_tointeger(L, lua_upvalueindex(1));
	lua_push<type>(L, read<type>(delta));
	return 1;
}
template <typename type>
int lua_obj::set(int index) {
	lua_checktype<type>(L, index);
	type value = lua_to<type>(L, index);

	size_t delta = lua_tointeger(L, lua_upvalueindex(1));
	write<type>(delta, value);
	return 0;
}

template int lua_obj::get<int>();
template int lua_obj::get<unsigned int>();
template int lua_obj::get<unsigned char>();
template int lua_obj::get<double>();
template int lua_obj::get<const char*>();
template int lua_obj::get<bool>();

template int lua_obj::set<int>(int);
template int lua_obj::set<unsigned int>(int);
template int lua_obj::set<unsigned char>(int);
template int lua_obj::set<double>(int);
template int lua_obj::set<const char*>(int);
template int lua_obj::set<bool>(int);
