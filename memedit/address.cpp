#include "stdafx.h"
#include "address.h"
#include "lua_helpers.h"
#include "lua_board.h"
#include "lua_tile.h"
#include "lua_pawn.h"
#include "lua_weapon.h"
#include "lua_game.h"

template <typename type>
std::string getter() {
	return "get";
}

template <>
std::string getter<bool>() {
	return "is";
}

template <class obj, typename type>
Address Address::build(std::string id, size_t delta, Access access) {
	return Address{
		id,
		delta,
		access,
		LuaFunction{ getter<type>() + id, obj::template get<type> },
		LuaFunction{ "set" + id, obj::template set<type> }
	};
}

template <class obj>
Address Address::build(std::string id, size_t delta, Access access, Addr_Type addr_type) {
	switch(addr_type)
	{
		case TYPE_INT:
			return Address::build<obj, int>(id, delta, access);
		case TYPE_UNSIGNED_INT:
			return Address::build<obj, unsigned int>(id, delta, access);
		case TYPE_UNSIGNED_CHAR:
			return Address::build<obj, unsigned char>(id, delta, access);
		case TYPE_BOOL:
			return Address::build<obj, bool>(id, delta, access);
		case TYPE_DOUBLE:
			return Address::build<obj, double>(id, delta, access);
		case TYPE_CONST_CHAR_PTR:
			return Address::build<obj, const char*>(id, delta, access);
		default:
			return Address{};
	}
}

template Address Address::build<lua_board>(std::string, size_t, Access, Addr_Type);
template Address Address::build<lua_tile>(std::string, size_t, Access, Addr_Type);
template Address Address::build<lua_pawn>(std::string, size_t, Access, Addr_Type);
template Address Address::build<lua_weapon>(std::string, size_t, Access, Addr_Type);
template Address Address::build<lua_game>(std::string, size_t, Access, Addr_Type);

Address Address::build(std::string id, size_t delta, Access access, Addr_Type addr_type, Obj_Type obj_type) {
	switch (obj_type)
	{
		case OBJ_TYPE_BOARD:
			return Address::build<lua_board>(id, delta, access, addr_type);
		case OBJ_TYPE_TILE:
			return Address::build<lua_tile>(id, delta, access, addr_type);
		case OBJ_TYPE_PAWN:
			return Address::build<lua_pawn>(id, delta, access, addr_type);
		case OBJ_TYPE_WEAPON:
			return Address::build<lua_weapon>(id, delta, access, addr_type);
		case OBJ_TYPE_GAME:
			return Address::build<lua_game>(id, delta, access, addr_type);
		default:
			return Address{};
	}
}

template Address Address::build<lua_board, int>(std::string, size_t, Access);
template Address Address::build<lua_board, unsigned int>(std::string, size_t, Access);
template Address Address::build<lua_board, unsigned char>(std::string, size_t, Access);
template Address Address::build<lua_board, bool>(std::string, size_t, Access);
template Address Address::build<lua_board, double>(std::string, size_t, Access);
template Address Address::build<lua_board, const char*>(std::string, size_t, Access);

template Address Address::build<lua_tile, int>(std::string, size_t, Access);
template Address Address::build<lua_tile, unsigned int>(std::string, size_t, Access);
template Address Address::build<lua_tile, unsigned char>(std::string, size_t, Access);
template Address Address::build<lua_tile, bool>(std::string, size_t, Access);
template Address Address::build<lua_tile, double>(std::string, size_t, Access);
template Address Address::build<lua_tile, const char*>(std::string, size_t, Access);

template Address Address::build<lua_pawn, int>(std::string, size_t, Access);
template Address Address::build<lua_pawn, unsigned int>(std::string, size_t, Access);
template Address Address::build<lua_pawn, unsigned char>(std::string, size_t, Access);
template Address Address::build<lua_pawn, bool>(std::string, size_t, Access);
template Address Address::build<lua_pawn, double>(std::string, size_t, Access);
template Address Address::build<lua_pawn, const char*>(std::string, size_t, Access);

template Address Address::build<lua_weapon, int>(std::string, size_t, Access);
template Address Address::build<lua_weapon, unsigned int>(std::string, size_t, Access);
template Address Address::build<lua_weapon, unsigned char>(std::string, size_t, Access);
template Address Address::build<lua_weapon, bool>(std::string, size_t, Access);
template Address Address::build<lua_weapon, double>(std::string, size_t, Access);
template Address Address::build<lua_weapon, const char*>(std::string, size_t, Access);

template Address Address::build<lua_game, int>(std::string, size_t, Access);
template Address Address::build<lua_game, unsigned int>(std::string, size_t, Access);
template Address Address::build<lua_game, unsigned char>(std::string, size_t, Access);
template Address Address::build<lua_game, bool>(std::string, size_t, Access);
template Address Address::build<lua_game, double>(std::string, size_t, Access);
template Address Address::build<lua_game, const char*>(std::string, size_t, Access);

void Address::addLuaFunction(lua_State* L, size_t addr, LuaFunction* function) {
	if (!lua_istable(L, -1))
		luaL_error(L, "addLuaFunction failed: parent table does not exist");
	if (VERBOSE)
		log(L, "Add " + function->name);

	lua_pushstring(L, function->name.c_str());
	lua_pushinteger(L, addr);
	lua_pushcclosure(L, function->func, 1);
	lua_rawset(L, -3);
}

void Address::addLuaFunction(lua_State* L, Address address) {
	bool readAccess = (address.access == R || address.access == RW);
	bool writeAccess = (address.access == W || address.access == RW);

	if (readAccess)
		address.addLuaFunction(L, address.delta, &address.get);

	if (writeAccess)
		address.addLuaFunction(L, address.delta, &address.set);
}

void Address::addLuaFunctions(lua_State* L, std::vector<Address> addresses) {
	for (auto address : addresses)
		Address::addLuaFunction(L, address);
}
