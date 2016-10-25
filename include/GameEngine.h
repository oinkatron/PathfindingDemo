#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "StateMachine.h"
#include "GameCommand.h"
#include "GameState.h"
#include "GUIManager.h"
#include "OMath.h"

class GameEngine
{
    public:
        GameEngine();
        virtual ~GameEngine();

         bool onInit(int s_width, int s_height, int s_bpp);
         void onStart();
         void onLoop();
         void onUpdate();
         void onRender();
         void onCleanUp();

         bool isFullscreen() { return fullscreen; }
         void isFullscreen(bool val) { fullscreen = val; }

    protected:
    private:
        SDL_Surface *screen;
        SDL_Event event;
        StateMachine game_states;
        GUIManager window_manager;

        unsigned int frame_time;
        unsigned int start_time;
        unsigned int last_time;

        bool lm_pressed;
        bool rm_pressed;

        bool done;
        bool fullscreen;

        int screen_width = 480;
        int screen_height = 640;
        int screen_bpp = 32;
};

#endif // GAMEENGINE_H
