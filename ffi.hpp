#pragma once
#include <cstring>
#include <lauxlib.h>
#include <lua.hpp>
#include <dlfcn.h>
#include <unistd.h>
#include <string>
#include <iostream>

#ifndef LUA_FFI_HPP
#define LUA_FFI_HPP
typedef int (*lua_func) (lua_State *ctx); ;
typedef struct lua_funcs {
	const char* name;
	static int func;
} lua_funcs;

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
