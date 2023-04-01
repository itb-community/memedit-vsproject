#ifndef ADDRESS_H
#define ADDRESS_H

#include "lua.hpp"
#include "lua_function.h"

enum Access { R, W, RW, NONE };
enum Obj_Type {
	OBJ_TYPE_BOARD,
	OBJ_TYPE_TILE,
	OBJ_TYPE_PAWN,
	OBJ_TYPE_GAME,
	OBJ_TYPE_WEAPON,
};
enum Addr_Type {
	TYPE_INT,
	TYPE_UNSIGNED_INT,
	TYPE_UNSIGNED_CHAR,
	TYPE_BOOL,
	TYPE_DOUBLE,
	TYPE_CONST_CHAR_PTR,
	TYPE_LIST_INT,
	TYPE_LIST_SHARED_VOID_PTR,
};

struct Address {
	std::string id = "UNKNOWN";
	size_t delta = 0x0;
	Access access = NONE;
	LuaFunction get;
	LuaFunction set;

	void addLuaFunction(lua_State*, size_t, LuaFunction*);
	static void addLuaFunction(lua_State*, Address);
	static void addLuaFunctions(lua_State*, std::vector<Address>);

	template <class obj, typename type>
	static Address build(std::string, size_t, Access);
	template <typename type>
	static Address build(std::string, size_t, Access, Addr_Type);
	static Address build(std::string, size_t, Access, Addr_Type, Obj_Type);
};

#endif
