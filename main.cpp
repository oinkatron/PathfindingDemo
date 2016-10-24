#include <iostream>
#include <SDL/SDL.h>

#include "include/GameEngine.h"


#include "include/SetWayPointCommand.h"

using namespace std;
GameEngine *main_engine;

int main ( int argc, char** argv )
{
    //init the event handler
    main_engine = new GameEngine();
    main_engine->onInit(800, 600, 32);
    main_engine->isFullscreen(false);

    main_engine->onStart();


    return 0;
}
