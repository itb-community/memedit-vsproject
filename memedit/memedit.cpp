// memedit.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "lua.hpp"
#include "misc.h"
#include "address.h"
#include "lua_vector.h"
#include "lua_pawn.h"
#include "lua_board.h"
#include "lua_tile.h"
#include "lua_weapon.h"
#include "lua_game.h"

#define DLLEXPORT __declspec(dllexport)

extern "C" DLLEXPORT int luaopen_memedit(lua_State* L) {
	int n = lua_gettop(L);

	// Validate input
	if (n == 0)
		lua_newtable(L);
	else if (n == 1) {
		if (lua_isnil(L, 1)) {
			lua_pop(L, 1);
			lua_newtable(L);
		}
		luaL_argcheck(L, lua_istable(L, 1), 1, "Expected table");
	}
	else
		luaL_error(L, "Too many arguments");

	DEBUG_MODE = Options::get(L, "debug", false);
	HEX = Options::get(L, "hex", true);
	VERBOSE = Options::get(L, "verbose", false);

	if (VERBOSE) {
		log(L, "memedit options:");
		logf(L, "debug: %s", DEBUG_MODE);
		logf(L, "hex: %s", HEX);
		logf(L, "verbose: %s", VERBOSE);
	}

	// Build functions from input
	BASE_OFFSETS = Options::getBaseOffsets(L, "vital");
	GAME_ADDRESSES = Options::getAddrList(L, OBJ_TYPE_GAME, "game");
	BOARD_ADDRESSES = Options::getAddrList(L, OBJ_TYPE_BOARD, "board");
	TILE_ADDRESSES = Options::getAddrList(L, OBJ_TYPE_TILE, "tile");
	PAWN_ADDRESSES = Options::getAddrList(L, OBJ_TYPE_PAWN, "pawn");
	WEAPON_ADDRESSES = Options::getAddrList(L, OBJ_TYPE_WEAPON, "weapon");


	// Set base offsets
	Options::setBaseOffset(lua_pawn::weapon_list_delta, "delta_weapons");
	Options::setBaseOffset(lua_tile::rows_delta, "delta_rows");
	Options::setBaseOffset(lua_tile::rows_step, "step_rows");
	Options::setBaseOffset(lua_tile::tile_size, "size_tile");


	// Linebreak
	if (VERBOSE) log(L, "");

	// Pop input
	lua_pop(L, 1);

	// Push output table
	lua_newtable(L);


	/* ----------------- Create metatables ----------------- */
	lua_vector<IntList>::createMetatable(L);
	lua_vector<SharedVoidPtrList>::createMetatable(L);


	/* ---------------- Add Debug functions ----------------- */
	if (DEBUG_MODE) {
		lua_pushstring(L, "debug");
		lua_newtable(L);
		add_debug_functions(L);
		lua_rawset(L, -3);
	}

	/* ---------------- Add Misc functions ------------------ */
	lua_pushstring(L, "misc");
	lua_newtable(L);
	add_misc_functions(L);
	lua_rawset(L, -3);


	/* ------------ Add Board & Tile functions -------------- */
	lua_pushstring(L, "board");
	lua_newtable(L);

	if (lua_board::isSafe())
		Address::addLuaFunctions(L, BOARD_ADDRESSES);

	else if (VERBOSE)
		log(L, "Skip Board functions - missing base offsets!");

	if (lua_tile::isSafe())
		Address::addLuaFunctions(L, TILE_ADDRESSES);

	else if (VERBOSE)
		log(L, "Skip Tile functions - missing base offsets!");

	lua_rawset(L, -3);


	/* ----------------- Add Pawn function ------------------ */
	lua_pushstring(L, "pawn");
	lua_newtable(L);

	if (lua_pawn::isSafe())
		Address::addLuaFunctions(L, PAWN_ADDRESSES);

	else if (VERBOSE)
		log(L, "Skip Pawn functions - missing base offsets!");

	lua_rawset(L, -3);


	/* ----------------Add Weapon functions ----------------- */
	lua_pushstring(L, "weapon");
	lua_newtable(L);

	if (lua_weapon::isSafe())
		Address::addLuaFunctions(L, WEAPON_ADDRESSES);

	else if (VERBOSE)
		log(L, "Skip Weapon functions - missing base offsets!");

	lua_rawset(L, -3);


	/* ---------------- Add Game functions ------------------ */
	lua_pushstring(L, "game");
	lua_newtable(L);

	if (lua_game::isSafe())
		Address::addLuaFunctions(L, GAME_ADDRESSES);

	else if (VERBOSE)
		log(L, "Skip Game functions - missing base offsets!");

	lua_rawset(L, -3);
	/* ----------------------------------------------------- */


	// Set output to global variable
	lua_setglobal(L, "memeditdll");

	return 1;
}

