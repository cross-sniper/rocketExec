#include <lua.hpp>
#include <raylib.h>
#include "../../ffi.hpp"
#include "ray-color.cpp" // Ensure this file provides lua_getColor function

typedef struct Img {
    Image sourceImage;
    Texture2D texture;
} Img;

static int loadImage(lua_State* L) {
    // Check if the function argument is a string (path to the image file)
    const char* filePath = luaL_checkstring(L, 1);

    // Load the image
    Image image = LoadImage(filePath);
    if (image.data == nullptr) {
        lua_pushnil(L);
        lua_pushstring(L, "Failed to load image");
        return 2;
    }

    // Create Img object
    Img* img = new Img();
    img->sourceImage = image;
    img->texture = LoadTextureFromImage(image);

    // Push Img object onto the Lua stack
    pushPtr(L, img);

    // Return 1 value (the Img object)
    return 1;
}

static int unloadImage(lua_State* L) {
    Img* img = getPtr<Img>(L, 1);
    UnloadImage(img->sourceImage);
    UnloadTexture(img->texture);
    delete img; // Use delete instead of free
    return 0;
}

static int drawTexture(lua_State* L) {
    Img* image = getPtr<Img>(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);
    Color color = lua_getColor(L, 4);
    DrawTexture(image->texture, x, y, color);
    return 0;
}

static luaL_Reg imageFuncs[] = {
	{ "LoadImage", loadImage },
	{ "UnloadImage", unloadImage },
	{ "DrawTexture", drawTexture },
	{NULL, NULL}
};

void init_raylib_img(lua_State*L){
    // Iterate over the functions and add them to the table
	for (int i = 0; imageFuncs[i].name; i++) {
		lua_pushcfunction(L, imageFuncs[i].func);
		lua_setglobal(L, imageFuncs[i].name);
	}
}
