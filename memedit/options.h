#ifndef OPTIONS_H
#define OPTIONS_H

#include "lua.hpp"
#include "stdafx.h"
#include "address.h"

extern bool VERBOSE;
extern bool HEX;
extern bool DEBUG_MODE;
extern std::map<std::string, size_t> BASE_OFFSETS;
extern std::vector<Address> GAME_ADDRESSES;
extern std::vector<Address> BOARD_ADDRESSES;
extern std::vector<Address> TILE_ADDRESSES;
extern std::vector<Address> PAWN_ADDRESSES;
extern std::vector<Address> WEAPON_ADDRESSES;
extern std::vector<Address> SPACE_DAMAGE_ADDRESSES;

std::string getAddrFormat();

class Options {
public:
	static int get(lua_State* L, const char* name, int default_value);
	static bool get(lua_State* L, const char* name, bool default_value);
	static const char* get(lua_State* L, const char* name, const char* default_value);
	static std::map<std::string, size_t> getBaseOffsets(lua_State* L, const char* name);
	static std::vector<Address> getAddrList(lua_State* L, Obj_Type obj_type, const char* name);
	static void setBaseOffset(size_t&, std::string);
};

#endif
