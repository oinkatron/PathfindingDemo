#include "../include/GameEngine.h"

GameEngine::GameEngine()
{
    fullscreen = false;

    lm_pressed = false;
    rm_pressed = false;

    screen_width = 0;
    screen_height = 0;
    screen_bpp = 0;

}

bool GameEngine::onInit(int s_width, int s_height, int s_bpp)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }

    screen_width = s_width;
    screen_height = s_height;
    screen_bpp = s_bpp;

    screen = SDL_SetVideoMode(screen_width, screen_height, screen_bpp, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if (screen == NULL)
    {
        return false;
    }

    if (TTF_Init() == -1)
    {
        clog << "Error Loading TTF library fonts unavailable!" << endl;
    }

    SDL_WM_SetCaption("Pathfinding v1.0", NULL);
    done = false;

    GameState *g_state = new GameState();
    g_state->setGraphicsContext(screen);
    g_state->setWindowManager(&window_manager);
    game_states.pushState(g_state);

    return true;

}

void GameEngine::onStart()
{
    start_time = SDL_GetTicks();
    while (!done)
    {
        last_time = start_time;
        start_time = SDL_GetTicks();
        frame_time = start_time - last_time;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                game_states.handleKeyPress(event.key.keysym.sym);
            }
            else if (event.type == SDL_KEYUP)
            {
                game_states.handleKeyRelease(event.key.keysym.sym);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    Frame* f;
                    f = window_manager.processMouse(event.button.x, event.button.y);
                    if (f != NULL)
                    {
                        GUIEvent new_event;
                        new_event.comp = f;
                        new_event.gui_type = GUIEVENT_PRESSED;
                        game_states.handleWindowEvent(new_event);
                        lm_pressed = true;
                    }
                    else
                    {
                        game_states.handleMousePress(event.button.x, event.button.y, 1);
                        lm_pressed = true;
                    }


                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    game_states.handleMousePress(event.button.x, event.button.y, 10);
                    rm_pressed = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                     Frame* f;
                    f = window_manager.processMouse(event.button.x, event.button.y);
                    if (f != NULL)
                    {
                        GUIEvent new_event;
                        new_event.comp = f;
                        new_event.gui_type = GUIEVENT_RELEASED;
                        game_states.handleWindowEvent(new_event);
                        lm_pressed = false;
                    }
                    else
                    {
                        game_states.handleMousePress(event.button.x, event.button.y, 1);
                        lm_pressed = false;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    game_states.handleMouseRelease(event.button.x, event.button.y, 10);
                    rm_pressed = false;
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (lm_pressed)
                {
                    game_states.handleMouseDrag(event.motion.x, event.button.y, 1);
                }
                else if (rm_pressed)
                {
                    game_states.handleMouseDrag(event.motion.x, event.motion.y, 10);
                }
                else
                {
                    game_states.handleMouseMove(event.motion.x, event.motion.y);
                }
            }
        }

        GameCommand *e;
        while((e = GameCommand::getNextCommand()) != NULL)
        {
            if (dynamic_cast<CmdObjectLifeExpired*>(e))
            {
                game_states.handleCmdObjectLifeExpired((CmdObjectLifeExpired*)e);
            }
            else if (dynamic_cast<CmdSkillActivated*>(e))
            {
                game_states.handleCmdSkillActivated((CmdSkillActivated*)e);
            }
        }

        game_states.onUpdate(frame_time);

        onRender();


    }

    void onCleanUp();
}

void GameEngine::onRender()
{
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
    game_states.onRender();

    SDL_Flip(screen);
}


void GameEngine::onLoop()
{

}

void GameEngine::onCleanUp()
{

}

GameEngine::~GameEngine()
{
    //dtor
}
