#include <lua.hpp>
#include <raylib.h>
#include "../../ffi.hpp"
#define LUA lua_State *ctx
Camera2D globalCam2d;
Camera3D globalCam3d;
int worldToScreen2D(LUA){
	Vector2 result;
	float x, y;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	result = GetWorldToScreen2D({x, y}, globalCam2d);

	lua_newtable(ctx);
	lua_pushnumber(ctx, result.x);
	lua_setfield(ctx, -2, "x");
	lua_pushnumber(ctx, result.y);
	lua_setfield(ctx, -2, "y");
	return 1;
}

int screenToWorld2D(LUA){
	Vector2 result;
	float x, y;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	result = GetScreenToWorld2D({x, y}, globalCam2d);
	lua_newtable(ctx);
	lua_pushnumber(ctx, result.x);
	lua_setfield(ctx, -2, "x");
	lua_pushnumber(ctx, result.y);
	lua_setfield(ctx, -2, "y");
	return 1;
}


int setupCam2D(LUA){
	float x, y, targetX, targetY, rotation, zoom;
	// getArgByName does the boring work of getting the arguments from the tables
	// defined on ffi.hpp as inline int
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	targetX = getArgByName(ctx, "x",2);
	targetY = getArgByName(ctx, "y",2);
	rotation = lua_tonumber(ctx, 3);
	zoom = lua_tonumber(ctx, 4);
	globalCam2d = { {x, y}, {targetX, targetY}, rotation, zoom };
	return 0;
}

int useCam2D(LUA){
	BeginMode2D(globalCam2d);
	return 0;
}

int setupCam3D(LUA){
	float x, y, z, targetX, targetY, targetZ, upX, upY, upZ, fovy;
	int projection;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	z = getArgByName(ctx, "z",1);

	targetX = getArgByName(ctx, "x",2);
	targetY = getArgByName(ctx, "y",2);
	targetZ = getArgByName(ctx, "z",2);

	upX = getArgByName(ctx, "x",3);
	upY = getArgByName(ctx, "y",3);
	upZ = getArgByName(ctx, "z",3);

	fovy = lua_tonumber(ctx, 4);
	projection = lua_tonumber(ctx, 5);

	globalCam3d = { {x, y, z}, {targetX, targetY, targetZ}, {upX, upY, upZ}, fovy, projection };
	return 0;
}

int useCam3D(LUA){
	BeginMode3D(globalCam3d);
	return 0;
}

int stopCam2D(LUA){
	EndMode2D();
	return 0;
}

int stopCam3D(LUA){
	EndMode3D();
	return 0;
}

int setCamera2DTarget(LUA){
	float x, y;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	globalCam2d.target = {x, y};
	return 0;
}

int setCamera2DOffset(LUA){
	float x, y;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	globalCam2d.offset = {x, y};
	return 0;
}

int setCamera2DRotation(LUA){
	float rotation;
	rotation = lua_tonumber(ctx, 1);
	globalCam2d.rotation = rotation;
	return 0;
}

int setCamera2DZoom(LUA){
	float zoom;
	zoom = lua_tonumber(ctx, 1);
	globalCam2d.zoom = zoom;
	return 0;
}

int setCamera3DTarget(LUA){
	float x, y, z;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	z = getArgByName(ctx, "z",1);
	globalCam3d.target = {x, y, z};
	return 0;
}

int setCamera3DPosition(LUA){
	float x, y, z;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	z = getArgByName(ctx, "z",1);
	globalCam3d.position = {x, y, z};
	return 0;
}

int setCamera3DUp(LUA){
	float x, y, z;
	x = getArgByName(ctx, "x",1);
	y = getArgByName(ctx, "y",1);
	z = getArgByName(ctx, "z",1);
	globalCam3d.up = {x, y, z};
	return 0;
}

int setCamera3DFovy(LUA){
	float fovy;
	fovy = lua_tonumber(ctx, 1);
	globalCam3d.fovy = fovy;
	return 0;
}

int setCamera3DProjection(LUA){
	int projection;
	projection = lua_tonumber(ctx, 1);
	globalCam3d.projection = projection;
	return 0;
}

int updateCamera3D(LUA){
	int mode = lua_tonumber(ctx, 1);
	UpdateCamera(&globalCam3d, mode);
	return 0;
}

void pushModes(LUA){// this is for the Camera3D table
	lua_pushinteger(ctx, CAMERA_PERSPECTIVE);
	lua_setfield(ctx, -2, "CAMERA_PERSPECTIVE");
	lua_pushinteger(ctx, CAMERA_ORTHOGRAPHIC);
	lua_setfield(ctx, -2, "CAMERA_ORTHOGRAPHIC");
	lua_pushinteger(ctx, CAMERA_FREE);
	lua_setfield(ctx, -2, "CAMERA_FREE");
	lua_pushinteger(ctx, CAMERA_ORBITAL);
	lua_setfield(ctx, -2, "CAMERA_ORBITAL");
	lua_pushinteger(ctx, CAMERA_FIRST_PERSON);
	lua_setfield(ctx, -2, "CAMERA_FIRST_PERSON");
	lua_pushinteger(ctx, CAMERA_THIRD_PERSON);
	lua_setfield(ctx, -2, "CAMERA_THIRD_PERSON");


}

void pushCamera3D(LUA) {
    lua_newtable(ctx);
    lua_pushcfunction(ctx, setupCam3D);
    lua_setfield(ctx, -2, "setup");
    lua_pushcfunction(ctx, useCam3D);
    lua_setfield(ctx, -2, "begin");
    lua_pushcfunction(ctx, stopCam3D);
    lua_setfield(ctx, -2, "stop");
    lua_pushcfunction(ctx, setCamera3DTarget);
    lua_setfield(ctx, -2, "setTarget");
    lua_pushcfunction(ctx, setCamera3DPosition);
    lua_setfield(ctx, -2, "setPosition");
    lua_pushcfunction(ctx, setCamera3DUp);
    lua_setfield(ctx, -2, "setUp");
    lua_pushcfunction(ctx, setCamera3DFovy);
    lua_setfield(ctx, -2, "setFovy");
    lua_pushcfunction(ctx, setCamera3DProjection);
    lua_setfield(ctx, -2, "setProjection");
    lua_pushcfunction(ctx, updateCamera3D);
    lua_setfield(ctx, -2, "update");
    pushModes(ctx);
    lua_setglobal(ctx, "Camera3D");
}

void pushCamera2D(LUA) {
    lua_newtable(ctx);
    lua_pushcfunction(ctx, setupCam2D);
    lua_setfield(ctx, -2, "setup");
    lua_pushcfunction(ctx, useCam2D);
    lua_setfield(ctx, -2, "begin");
    lua_pushcfunction(ctx, stopCam2D);
    lua_setfield(ctx, -2, "stop");
    lua_pushcfunction(ctx, setCamera2DTarget);
    lua_setfield(ctx, -2, "setTarget");
    lua_pushcfunction(ctx, setCamera2DOffset);
    lua_setfield(ctx, -2, "setOffset");
    lua_pushcfunction(ctx, setCamera2DRotation);
    lua_setfield(ctx, -2, "setRotation");
    lua_pushcfunction(ctx, setCamera2DZoom);
    lua_setfield(ctx, -2, "setZoom");
    lua_pushcfunction(ctx, screenToWorld2D);
    lua_setfield(ctx, -2, "screenToWorld");
    lua_pushcfunction(ctx, worldToScreen2D);
    lua_setfield(ctx, -2, "worldToScreen");
    lua_setglobal(ctx, "Camera2D");
}

void initRaylibCamera(LUA) {
    pushCamera2D(ctx);
    pushCamera3D(ctx);
}
