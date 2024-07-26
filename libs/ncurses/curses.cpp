#include <lua.hpp>
#include "../../ffi.hpp"
namespace curses {
  #include <ncurses.h>
}

// Declare the global window pointer
static curses::WINDOW *win = nullptr;

// Initialize the ncurses library
static int initscr(lua_State* L) {
  win = curses::initscr();
  if (!win) {
    lua_pushstring(L, "Failed to initialize ncurses");
    lua_error(L);
  }
  return 0;
}

// End the ncurses session
static int endwin(lua_State* L) {
  if (win) {
    curses::endwin();
    win = nullptr;  // Reset the win pointer
  }
  return 0;
}

// Retrieve a character from the window
static int lua_getch(lua_State* L) {
  if (!win) {
    lua_pushstring(L, "Ncurses not initialized");
    lua_error(L);
  }
  int ch = curses::wgetch(win);
  lua_pushnumber(L, ch);
  return 1;
}

static int printw(lua_State* L){
	int x, y;
	const char* str;
	str = lua_tostring(L,1);
	x = lua_tonumber(L, 2);
	y = lua_tonumber(L, 3);

	curses::printw(str,y,x);
	return 0;
}

// Register the functions with Lua
static luaL_Reg luaCursesFunctions[] = {
  {"initscr", initscr},
  {"endwin", endwin},
  {"getch", lua_getch},
  {"printw", printw},
  {NULL, NULL}
};

// Open the curses library in Lua
extern "C" int luaopen_curses(lua_State *L) {
  for (int i = 0; luaCursesFunctions[i].name; i++) {
    lua_pushcfunction(L, luaCursesFunctions[i].func);
    lua_setglobal(L, luaCursesFunctions[i].name);
  }
  return 0;
}
