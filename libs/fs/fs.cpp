#include <lua.hpp>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>

static int writeFile(lua_State* L) {
    const char* filename = lua_tostring(L, 1);
    const char* content = lua_tostring(L, 2);

    FILE* file = fopen(filename, "w");
    if (!file) {
        lua_pushboolean(L, 0);
        lua_pushfstring(L, "Cannot open file '%s' for writing", filename);
        return 2;
    }

    size_t len = strlen(content);
    size_t written = fwrite(content, sizeof(char), len, file);
    fclose(file);

    if (written == len) {
        lua_pushboolean(L, 1);
        return 1;
    } else {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "Error writing to file");
        return 2;
    }
}
static int readFile(lua_State* L) {
    const char* filename = lua_tostring(L, 1);

    std::ifstream file(filename);
    if (!file.is_open()) {
        lua_pushnil(L);
        lua_pushfstring(L, "Cannot open file '%s'", filename);
        return 2;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    lua_pushstring(L, contents.c_str());
    return 1;
}

extern "C" int luaopen_fs(lua_State* L) {
    lua_newtable(L);

    lua_pushcfunction(L, readFile);
    lua_setfield(L, -2, "readFile");
    
    lua_pushcfunction(L, writeFile);
    lua_setfield(L, -2, "writeFile");

    return 1;
}
