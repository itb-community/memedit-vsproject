#include "stdafx.h"
#include "options.h"
#include "log.h"

bool VERBOSE = false;
bool HEX = false;
bool DEBUG_MODE = false;
std::map<std::string, size_t> BASE_OFFSETS;
std::vector<Address> GAME_ADDRESSES;
std::vector<Address> BOARD_ADDRESSES;
std::vector<Address> TILE_ADDRESSES;
std::vector<Address> PAWN_ADDRESSES;
std::vector<Address> WEAPON_ADDRESSES;
std::vector<Address> SPACE_DAMAGE_ADDRESSES;
std::vector<Address> OTHER_ADDRESSES;

std::string getAddrFormat() {
	if (HEX)
		return std::string("0x%X");
	else
		return std::string("%s");
}

int Options::get(lua_State* L, const char* name, int default_value) {
	int result = default_value;
	lua_getfield(L, 1, name);

	if (!lua_isnil(L, -1))
		result = lua_tointeger(L, -1);

	lua_pop(L, 1);
	return result;
}
bool Options::get(lua_State* L, const char* name, bool default_value) {
	bool result = default_value;
	lua_getfield(L, 1, name);

	if (!lua_isnil(L, -1))
		result = lua_toboolean(L, -1);

	lua_pop(L, 1);
	return result;
}
const char* Options::get(lua_State* L, const char* name, const char* default_value) {
	const char* result = default_value;
	lua_getfield(L, 1, name);

	if (!lua_isnil(L, -1))
		result = lua_tostring(L, -1);

	lua_pop(L, 1);
	return result;
}
std::map<std::string, size_t> Options::getBaseOffsets(lua_State* L, const char* name) {
	std::map<std::string, size_t> result{};
	lua_getfield(L, 1, name);

	if (lua_istable(L, -1)) {
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			std::string id = lua_tostring(L, -2);
			int delta = luaL_checkinteger(L, -1);

			result.insert(std::pair<std::string, size_t>(id, delta));

			if (VERBOSE)
				logf(L, "- Base offset " + id + ": 0x%x", delta);

			lua_pop(L, 1);
		}
	}

	lua_pop(L, 1);
	return result;
}
std::vector<Address> Options::getAddrList(lua_State* L, Obj_Type obj_type, const char* name) {
	std::vector<Address> result{};
	lua_getfield(L, 1, name);

	if (lua_istable(L, -1)) {
		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			if (lua_istable(L, -1))
			{
				std::string id = lua_tostring(L, -2);
				lua_pushinteger(L, 1); lua_gettable(L, -2); size_t delta = lua_tointeger(L, -1); lua_pop(L, 1);
				lua_pushinteger(L, 2); lua_gettable(L, -2); Access access = static_cast<Access>((int)lua_tonumber(L, -1)); lua_pop(L, 1);
				lua_pushinteger(L, 3); lua_gettable(L, -2); Addr_Type addr_type = static_cast<Addr_Type>((int)lua_tonumber(L, -1)); lua_pop(L, 1);

				result.push_back(Address::build(id, delta, access, addr_type, obj_type));
				
				if (VERBOSE)
					logf(L, "- Build functions for " + id + " at delta [0x%x]", (int)delta);
			}
			lua_pop(L, 1);
		}
	}

	lua_pop(L, 1);
	return result;
}

void Options::setBaseOffset(size_t& var, std::string key) {
	if (BASE_OFFSETS.find(key) != BASE_OFFSETS.end()) {
		var = BASE_OFFSETS[key];
	}
}
