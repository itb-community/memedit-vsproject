#ifndef DEBUG_H
#define DEBUG_H

#include "lua.hpp"
/*
	DEBUG MODE:
	  This mode is intended to be used to diagnose this dll itself.
	  While in debug mode, only the most generic functions are enabled:

	  returns the address of the object,
	  so we can query it further.
	  .getObjAddr(obj)

	  returns address value as an integer.
	  this function is safe as long as we own the address.
	  .getAddrInt(addr)

	  returns address value as an float.
	  this function is safe as long as we own the address.
	  .getAddrFloat(addr)

	  returns address value as a boolean.
	  this function is safe as long as we own the address.
	  .getAddrBool(addr)

	  returns address value as a string.
	  this function will cause a crash if the value is not a string.
	  .getAddrString(addr)

	  this function is biased in attempting to always return
	  a string if at all possible; otherwise it returns an integer.
	  .getAddrValue(addr)

	  returns true if we don't own the bytes [addr -> addr + size].
	  querying the value of any address we don't own will cause a crash.
	  .isAddrNotPointer(addr, size)
*/

void add_debug_functions(lua_State* L);

#endif
