#include "./Game/Game.h"
#include <sol/sol.hpp>
#include <iostream>

void TestLua()
{
    sol::state lua;

    lua.open_libraries(
        sol::lib::base
        );
    lua.script_file("./assets/scripts/myscript.lua");

    int someVarInsideCpp = lua["some_variable"];
    std::cout << "Some lua var " << someVarInsideCpp << std::endl;
}

int main(int argc, char* argv[]) {
    // Game game;
    //
    // game.Initialize();
    // game.Run();
    // game.Destroy();

    TestLua();

    return 0;
}
