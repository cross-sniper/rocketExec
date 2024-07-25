#pragma once
#include <cstring>
#include <lauxlib.h>
#include <lua.hpp>
#include <dlfcn.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <type_traits>
#include <stdexcept>

#ifndef LUA_FFI_HPP
#define LUA_FFI_HPP
typedef int (*lua_func) (lua_State *ctx); ;
typedef struct lua_funcs {
	const char* name;
	static int func;
} lua_funcs;


// Function to get a pointer from Lua stack
template <typename T>
T* getPtr(lua_State* L, int index) {
    if (!lua_isuserdata(L, index)) {
        throw std::runtime_error("Expected userdata at the given index");
    }
    void* userdata = lua_touserdata(L, index);
    return static_cast<T*>(userdata);
}

// Function to push a pointer onto the Lua stack
template <typename T>
void pushPtr(lua_State* L, T* ptr) {
    if (ptr == nullptr) {
        lua_pushnil(L);
    } else {
        void** userdata = static_cast<void**>(lua_newuserdata(L, sizeof(void*)));
        *userdata = static_cast<void*>(ptr);

        // Optionally set a metatable here to manage garbage collection, type checking, etc.
        if (luaL_newmetatable(L, typeid(T).name())) {
            lua_pushstring(L, "__gc");
            lua_pushcfunction(L, [](lua_State* L) -> int {
                void* ud = lua_touserdata(L, 1);
                if (ud) {
                    delete static_cast<T*>(*static_cast<void**>(ud));
                }
                return 0;
            });
            lua_settable(L, -3);
        }
        lua_setmetatable(L, -2);
    }
}
extern "C" {
    inline int getGlobalArgByName(lua_State *state, const char* name) {
        lua_getglobal(state, name);
        if (lua_isnumber(state, -1))
            return lua_tonumber(state, -1);
        return 0; // or any appropriate error handling
    }

    inline int getArgByName(lua_State *state, const char* name, int index) {
        if (!lua_istable(state, index)) {
            lua_pushnil(state);
            if (lua_isnumber(state, -1))
                return lua_tonumber(state, -1);
            return 0; // or any appropriate error handling
        }
        lua_getfield(state, index, name);
        if (lua_isnumber(state, -1))
            return lua_tonumber(state, -1);
        return 0; // or any appropriate error handling
    }

    inline void push_funcs(lua_State *state, luaL_Reg funcs[]) {
        // global
    	for (int i = 0; funcs[i].name; i++) {
	    lua_pushcfunction(state, funcs[i].func);
        }
    }

    inline void newModule(const char* name, luaL_Reg funcs[], lua_State *state) {
        lua_newtable(state);
        push_funcs(state, funcs);
        lua_setglobal(state, name);
    }

    luaL_Reg rocket_init(lua_State *ctx);
}

#endif
