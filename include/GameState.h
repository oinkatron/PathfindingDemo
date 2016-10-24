#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <vector>

#include "Renderer.h"

#include "Image.h"
#include "Font.h"
#include "Sprite.h"
#include "SpriteSet.h"
#include "Map.h"
#include "MapGenerator.h"
#include "Tilesheet.h"

#include "State.h"
#include "ObjectManager.h"

#include "Frame.h"
#include "Button.h"
#include "Tilesheet.h"

#include "MovementSystem.h"
#include "RenderSystem.h"
#include "WaypointSystem.h"
#include "SpriteSystem.h"
#include "LifetimeSystem.h"

#include "PositionModule.h"
#include "VelocityModule.h"
#include "MapModule.h"
#include "WaypointModule.h"
#include "LifetimeModule.h"
#include "SkillSetModule.h"

//#include "SetWayPointCommand.h"

using namespace std;

class GameState : public State
{
    public:
        GameState();
        virtual ~GameState();

        void onLoad();
        void onUnload();

        void handleMousePress(int m_x, int m_y, int m_button);
        void handleMouseRelease(int m_x, int m_y, int m_button);
        void handleMouseMove(int m_x, int m_y);
        void handleMouseDrag(int m_x, int m_y, int m_button);
        void handleKeyPress(SDLKey key);
        void handleKeyRelease(SDLKey key);
        void handleWindowEvent(GUIEvent &ev);
        void handleCmdObjectLifeExpired(CmdObjectLifeExpired *ev);
        void handleCmdSkillActivated(CmdSkillActivated *ev);

        void onUpdate(unsigned int d_t);
        void onRender(unsigned int d_t);

    protected:
    private:
        vector<State*> state_stack;
        ObjectManager game_objects;
        Camera cam;
        Object *player_obj;
        Image *test;
        Map *test_map;
        Tilesheet *t_sheet;
        Renderer *s_renderer;

        MovementSystem move_system;
        RenderSystem renderer;
        WaypointSystem way_p_system;
        SpriteSystem spr_system;
        LifetimeSystem life_system;

};

#endif // GAMESTATE_H
