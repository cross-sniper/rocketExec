#include <lua.hpp>

#include <raylib.h>
// Helper function to add Raylib key constants to the luar table
static int addRaylibKeyConstant(lua_State *L, const char *keyName,
                                int keyValue) {
  lua_pushinteger(L, keyValue);
  lua_setglobal(L, keyName);
  return 1;
}
void init_raylib_gamepad(lua_State* ctx);

static int init_raylib_keys(lua_State *L)
{
    // Alphanumeric keys
    addRaylibKeyConstant(L, "KEY_APOSTROPHE", KEY_APOSTROPHE);
    addRaylibKeyConstant(L, "KEY_COMMA", KEY_COMMA);
    addRaylibKeyConstant(L, "KEY_MINUS", KEY_MINUS);
    addRaylibKeyConstant(L, "KEY_PERIOD", KEY_PERIOD);
    addRaylibKeyConstant(L, "KEY_SLASH", KEY_SLASH);
    addRaylibKeyConstant(L, "KEY_ZERO", KEY_ZERO);
    addRaylibKeyConstant(L, "KEY_ONE", KEY_ONE);
    addRaylibKeyConstant(L, "KEY_TWO", KEY_TWO);
    addRaylibKeyConstant(L, "KEY_THREE", KEY_THREE);
    addRaylibKeyConstant(L, "KEY_FOUR", KEY_FOUR);
    addRaylibKeyConstant(L, "KEY_FIVE", KEY_FIVE);
    addRaylibKeyConstant(L, "KEY_SIX", KEY_SIX);
    addRaylibKeyConstant(L, "KEY_SEVEN", KEY_SEVEN);
    addRaylibKeyConstant(L, "KEY_EIGHT", KEY_EIGHT);
    addRaylibKeyConstant(L, "KEY_NINE", KEY_NINE);
    addRaylibKeyConstant(L, "KEY_SEMICOLON", KEY_SEMICOLON);
    addRaylibKeyConstant(L, "KEY_EQUAL", KEY_EQUAL);
    addRaylibKeyConstant(L, "KEY_A", KEY_A);
    addRaylibKeyConstant(L, "KEY_B", KEY_B);
    addRaylibKeyConstant(L, "KEY_C", KEY_C);
    addRaylibKeyConstant(L, "KEY_D", KEY_D);
    addRaylibKeyConstant(L, "KEY_E", KEY_E);
    addRaylibKeyConstant(L, "KEY_F", KEY_F);
    addRaylibKeyConstant(L, "KEY_G", KEY_G);
    addRaylibKeyConstant(L, "KEY_H", KEY_H);
    addRaylibKeyConstant(L, "KEY_I", KEY_I);
    addRaylibKeyConstant(L, "KEY_J", KEY_J);
    addRaylibKeyConstant(L, "KEY_K", KEY_K);
    addRaylibKeyConstant(L, "KEY_L", KEY_L);
    addRaylibKeyConstant(L, "KEY_M", KEY_M);
    addRaylibKeyConstant(L, "KEY_N", KEY_N);
    addRaylibKeyConstant(L, "KEY_O", KEY_O);
    addRaylibKeyConstant(L, "KEY_P", KEY_P);
    addRaylibKeyConstant(L, "KEY_Q", KEY_Q);
    addRaylibKeyConstant(L, "KEY_R", KEY_R);
    addRaylibKeyConstant(L, "KEY_S", KEY_S);
    addRaylibKeyConstant(L, "KEY_T", KEY_T);
    addRaylibKeyConstant(L, "KEY_U", KEY_U);
    addRaylibKeyConstant(L, "KEY_V", KEY_V);
    addRaylibKeyConstant(L, "KEY_W", KEY_W);
    addRaylibKeyConstant(L, "KEY_X", KEY_X);
    addRaylibKeyConstant(L, "KEY_Y", KEY_Y);
    addRaylibKeyConstant(L, "KEY_Z", KEY_Z);
    addRaylibKeyConstant(L, "KEY_LEFT_BRACKET", KEY_LEFT_BRACKET);
    addRaylibKeyConstant(L, "KEY_BACKSLASH", KEY_BACKSLASH);
    addRaylibKeyConstant(L, "KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET);
    addRaylibKeyConstant(L, "KEY_GRAVE", KEY_GRAVE);

    // Function keys
    addRaylibKeyConstant(L, "KEY_SPACE", KEY_SPACE);
    addRaylibKeyConstant(L, "KEY_ESCAPE", KEY_ESCAPE);
    addRaylibKeyConstant(L, "KEY_ENTER", KEY_ENTER);
    addRaylibKeyConstant(L, "KEY_TAB", KEY_TAB);
    addRaylibKeyConstant(L, "KEY_BACKSPACE", KEY_BACKSPACE);
    addRaylibKeyConstant(L, "KEY_INSERT", KEY_INSERT);
    addRaylibKeyConstant(L, "KEY_DELETE", KEY_DELETE);
    addRaylibKeyConstant(L, "KEY_RIGHT", KEY_RIGHT);
    addRaylibKeyConstant(L, "KEY_LEFT", KEY_LEFT);
    addRaylibKeyConstant(L, "KEY_DOWN", KEY_DOWN);
    addRaylibKeyConstant(L, "KEY_UP", KEY_UP);
    addRaylibKeyConstant(L, "KEY_PAGE_UP", KEY_PAGE_UP);
    addRaylibKeyConstant(L, "KEY_PAGE_DOWN", KEY_PAGE_DOWN);
    addRaylibKeyConstant(L, "KEY_HOME", KEY_HOME);
    addRaylibKeyConstant(L, "KEY_END", KEY_END);
    addRaylibKeyConstant(L, "KEY_CAPS_LOCK", KEY_CAPS_LOCK);
    addRaylibKeyConstant(L, "KEY_SCROLL_LOCK", KEY_SCROLL_LOCK);
    addRaylibKeyConstant(L, "KEY_NUM_LOCK", KEY_NUM_LOCK);
    addRaylibKeyConstant(L, "KEY_PRINT_SCREEN", KEY_PRINT_SCREEN);
    addRaylibKeyConstant(L, "KEY_PAUSE", KEY_PAUSE);
    addRaylibKeyConstant(L, "KEY_F1", KEY_F1);
    addRaylibKeyConstant(L, "KEY_F2", KEY_F2);
    addRaylibKeyConstant(L, "KEY_F3", KEY_F3);
    addRaylibKeyConstant(L, "KEY_F4", KEY_F4);
    addRaylibKeyConstant(L, "KEY_F5", KEY_F5);
    addRaylibKeyConstant(L, "KEY_F6", KEY_F6);
    addRaylibKeyConstant(L, "KEY_F7", KEY_F7);
    addRaylibKeyConstant(L, "KEY_F8", KEY_F8);
    addRaylibKeyConstant(L, "KEY_F9", KEY_F9);
    addRaylibKeyConstant(L, "KEY_F10", KEY_F10);
    addRaylibKeyConstant(L, "KEY_F11", KEY_F11);
    addRaylibKeyConstant(L, "KEY_F12", KEY_F12);
    addRaylibKeyConstant(L, "KEY_LEFT_SHIFT", KEY_LEFT_SHIFT);
    addRaylibKeyConstant(L, "KEY_LEFT_CONTROL", KEY_LEFT_CONTROL);
    addRaylibKeyConstant(L, "KEY_LEFT_ALT", KEY_LEFT_ALT);
    addRaylibKeyConstant(L, "KEY_LEFT_SUPER", KEY_LEFT_SUPER);
    addRaylibKeyConstant(L, "KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT);
    addRaylibKeyConstant(L, "KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL);
    addRaylibKeyConstant(L, "KEY_RIGHT_ALT", KEY_RIGHT_ALT);
    addRaylibKeyConstant(L, "KEY_RIGHT_SUPER", KEY_RIGHT_SUPER);
    addRaylibKeyConstant(L, "KEY_KB_MENU", KEY_KB_MENU);

    // Keypad keys
    addRaylibKeyConstant(L, "KEY_KP_0", KEY_KP_0);
    addRaylibKeyConstant(L, "KEY_KP_1", KEY_KP_1);
    addRaylibKeyConstant(L, "KEY_KP_2", KEY_KP_2);
    addRaylibKeyConstant(L, "KEY_KP_3", KEY_KP_3);
    addRaylibKeyConstant(L, "KEY_KP_4", KEY_KP_4);
    addRaylibKeyConstant(L, "KEY_KP_5", KEY_KP_5);
    addRaylibKeyConstant(L, "KEY_KP_6", KEY_KP_6);
    addRaylibKeyConstant(L, "KEY_KP_7", KEY_KP_7);
    addRaylibKeyConstant(L, "KEY_KP_8", KEY_KP_8);
    addRaylibKeyConstant(L, "KEY_KP_9", KEY_KP_9);
    addRaylibKeyConstant(L, "KEY_KP_DECIMAL", KEY_KP_DECIMAL);
    addRaylibKeyConstant(L, "KEY_KP_DIVIDE", KEY_KP_DIVIDE);
    addRaylibKeyConstant(L, "KEY_KP_MULTIPLY", KEY_KP_MULTIPLY);
    addRaylibKeyConstant(L, "KEY_KP_SUBTRACT", KEY_KP_SUBTRACT);
    addRaylibKeyConstant(L, "KEY_KP_ADD", KEY_KP_ADD);
    addRaylibKeyConstant(L, "KEY_KP_ENTER", KEY_KP_ENTER);
    addRaylibKeyConstant(L, "KEY_KP_EQUAL", KEY_KP_EQUAL);

    // Android key buttons
    addRaylibKeyConstant(L, "KEY_BACK", KEY_BACK);
    addRaylibKeyConstant(L, "KEY_MENU", KEY_MENU);
    addRaylibKeyConstant(L, "KEY_VOLUME_UP", KEY_VOLUME_UP);
    addRaylibKeyConstant(L, "KEY_VOLUME_DOWN", KEY_VOLUME_DOWN);

    // mouse buttons
    addRaylibKeyConstant(L, "MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_RIGHT", MOUSE_BUTTON_RIGHT);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_MIDDLE", MOUSE_BUTTON_MIDDLE);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_SIDE", MOUSE_BUTTON_SIDE);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_EXTRA", MOUSE_BUTTON_EXTRA);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_FORWARD", MOUSE_BUTTON_FORWARD);
    addRaylibKeyConstant(L, "MOUSE_BUTTON_BACK", MOUSE_BUTTON_BACK);
    init_raylib_gamepad(L);
    return 1;
}

void init_raylib_gamepad(lua_State* ctx){
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB);
    addRaylibKeyConstant(ctx, "GAMEPAD_BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB);

    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X);
    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y);
    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X);
    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y);

    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER);
    addRaylibKeyConstant(ctx, "GAMEPAD_AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER);


}
