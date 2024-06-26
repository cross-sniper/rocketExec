#include "raylib/raylib.cpp"
#include "ray-cam/init.cpp"

extern "C" int luaopen_raylib(lua_State*ctx){
	initRaylib(ctx);
	return 1;
}
