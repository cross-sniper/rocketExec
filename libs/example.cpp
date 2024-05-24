#include "../ffi.hpp"
int ls(lua_State *L) {
    system("ls");
    return 0;
}

int i(lua_State *L) {
    // as long as the lua table has "l" and "r", this works, not mattering the order
    int l = getArgByName(L, "l",1);
    int r = getArgByName(L, "r",1);
    std::cout << l << " + " << r << " = " << l + r << std::endl;
    return 0;
}

lua_funcs fns[] = {
    {"ls", ls},
    {"i", i},
    {NULL, NULL}
};

extern "C" {
    lua_func rocket_init(lua_State *L) {
        newModule("example", fns, L);
        return 0; // Ensure the function returns an integer
    }
}
