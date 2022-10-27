#include "stdafx.h"
#include "debug.h"
#include "lua_obj.h"

const size_t STRING_LENGTH = 0x10;

int get_object_address(lua_State* L) {
	lua_obj obj(L, 1);
	lua_pushinteger(L, obj.getAddr());
	return 1;
}

bool is_ascii(BYTE c) {
	return c >= 0x0 && c <= 0x7F;
}

bool is_ascii(size_t addr, size_t size) {
	for (size_t c = 0x0; c < size + 0x1; c++)
		if (!is_ascii(*(BYTE*)(addr + c)))
			return false;

	return true;
}

bool has_access_to_memory(size_t addr, size_t size) {
	return (!IsBadReadPtr((void*)addr, size));
}

bool is_terminating_character(size_t addr) {
	return (*(BYTE*)(addr) == NULL);
}

/*
	Makes a guess on whether an address is a string or not.
	Return table:
	0: definitely not a string.
	1: possible string < 16 characters and a terminating character.
	2: possible std::string >= 16 characters and a terminating character.
*/
int get_string_code(lua_State* L, size_t addr) {
	size_t character_count = *(size_t*)(addr + STRING_LENGTH);

	if (character_count == 0)
		return 0;

	else if (character_count <= 0xFF) {
		if (character_count > 0xF)
			addr = *(size_t*)addr;

		if (!has_access_to_memory(addr, character_count))
			return 0;

		if (!is_ascii(addr, character_count))
			return 0;

		if (!is_terminating_character(addr + character_count))
			return 0;

		if (character_count > 0xF)
			return 2;
		else
			return 1;
	}

	return 0;
}

int is_address_not_pointer(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	size_t size = luaL_checkinteger(L, 2);
	lua_pushboolean(L, IsBadReadPtr(addr, size));
	return 1;
}

int get_addr_int(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	lua_pushinteger(L, *(int*)addr);
	return 1;
}

int get_addr_bool(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	lua_pushboolean(L, *(bool*)addr);
	return 1;
}

int get_addr_byte(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	lua_pushinteger(L, *(BYTE*)addr);
	return 1;
}

int get_addr_string(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	lua_pushstring(L, (static_cast<std::string*>(addr))->c_str());
	return 1;
}

int get_addr_value(lua_State* L) {
	void* addr = (void*)luaL_checkinteger(L, 1);
	int string_code = get_string_code(L, (size_t)addr);

	if (string_code == 1)
		lua_pushstring(L, (const char*)(addr));
	else if (string_code == 2)
		lua_pushstring(L, (const char*)(*(void**)addr));
	else
		lua_pushinteger(L, *(int*)addr);

	return 1;
}

void add_debug_functions(lua_State* L) {
	if (!lua_istable(L, -1))
		luaL_error(L, "add_debug_functions failed: parent table does not exist");

	if (VERBOSE) {
		log(L, "Add isAddrNotPointer");
		log(L, "Add getObjAddr");
		log(L, "Add getAddrInt");
		log(L, "Add getAddrBool");
		log(L, "Add getAddrByte");
		log(L, "Add getAddrString");
		log(L, "Add getAddrValue");
	}

	lua_pushstring(L, "isAddrNotPointer");
	lua_pushcfunction(L, is_address_not_pointer);
	lua_rawset(L, -3);

	lua_pushstring(L, "getObjAddr");
	lua_pushcfunction(L, get_object_address);
	lua_rawset(L, -3);

	lua_pushstring(L, "getAddrInt");
	lua_pushcfunction(L, get_addr_int);
	lua_rawset(L, -3);

	lua_pushstring(L, "getAddrBool");
	lua_pushcfunction(L, get_addr_bool);
	lua_rawset(L, -3);

	lua_pushstring(L, "getAddrByte");
	lua_pushcfunction(L, get_addr_byte);
	lua_rawset(L, -3);

	lua_pushstring(L, "getAddrString");
	lua_pushcfunction(L, get_addr_string);
	lua_rawset(L, -3);

	lua_pushstring(L, "getAddrValue");
	lua_pushcfunction(L, get_addr_value);
	lua_rawset(L, -3);
}
