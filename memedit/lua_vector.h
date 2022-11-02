#ifndef LUA_VECTOR_H
#define LUA_VECTOR_H

#include "lua.hpp"

typedef std::shared_ptr<void*> SharedVoidPtr;
typedef std::vector<int>* IntList;
typedef std::vector<SharedVoidPtr>* SharedVoidPtrList;

template <typename type>
struct lua_vector {
	type list;
	static const char* name();
	static int erase(lua_State*);
	static int size(lua_State*);
	static int at(lua_State*);
	static int index(lua_State*);
	static int createMetatable(lua_State*);
};

#endif
