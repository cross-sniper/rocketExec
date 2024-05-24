#pragma once
#include <raylib.h>
#include <lua.hpp>
#include <cstring>
static void lua_pushColor(lua_State *L, Color color, const char *name) {
  lua_newtable(L);

  lua_pushstring(L, "r");
  lua_pushinteger(L, color.r);
  lua_settable(L, -3);

  lua_pushstring(L, "g");
  lua_pushinteger(L, color.g);
  lua_settable(L, -3);

  lua_pushstring(L, "b");
  lua_pushinteger(L, color.b);
  lua_settable(L, -3);

  lua_pushstring(L, "a");
  lua_pushinteger(L, color.a);
  lua_settable(L, -3);

  lua_setglobal(L, name);
}

static Color lua_getColor(lua_State *L, int StartOfTable) {
  Color color = {0}; // Default to black in case of failure

  // Check if the provided argument is a table
  if (!lua_istable(L, StartOfTable)) {
    luaL_error(L, "Argument is not a table");
    return color;
  }

  // Iterate through the table
  lua_pushnil(L); // Push a nil key to start the iteration

  while (lua_next(L, StartOfTable) != 0) {
    // Key is at index -2 and value is at index -1

    // Assuming you have 'r', 'g', 'b', and 'a' keys in the table
    const char *key = lua_tostring(L, -2);

    if (key) {
      if (strcmp(key, "r") == 0) {
        color.r = lua_tointeger(L, -1);
      } else if (strcmp(key, "g") == 0) {
        color.g = lua_tointeger(L, -1);
      } else if (strcmp(key, "b") == 0) {
        color.b = lua_tointeger(L, -1);
      } else if (strcmp(key, "a") == 0) {
        color.a = lua_tointeger(L, -1);
      }
    }

    // Pop the value, leaving the key for the next iteration
    lua_pop(L, 1);
  }

  return color;
}

// Function to create a new color from a lua/lua table
static int lua_create_color(lua_State *L) {
  // Check if the argument is a table
  if (!lua_istable(L, 1)) {
    return luaL_error(L, "Argument is not a table");
  }
  const char *name = luaL_checkstring(L, 2);

  // Default color
  Color color = lua_getColor(L, 1);
  printf("%i\n", color.r);
  printf("%i\n", color.g);
  printf("%i\n", color.b);
  printf("%i\n", color.a);
  printf("%s\n", name);

  // Push the color onto the lua stack with a specified name
  lua_pushColor(L, color, name);

  return 0; // Number of return values
}

static int lua_init_colors(lua_State *L) {
  lua_pushColor(L, RED, "red");
  lua_pushColor(L, GREEN, "green");
  lua_pushColor(L, BLUE, "blue");
  lua_pushColor(L, WHITE, "white");
  lua_pushColor(L, LIGHTGRAY, "lightgray");
  lua_pushColor(L, BLACK, "black");
  return 1;
}