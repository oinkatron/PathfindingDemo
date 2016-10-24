#ifndef STATE_H
#define STATE_H

#include <SDL/SDL.h>

#include "GUIManager.h"
#include "CmdObjectLifeExpired.h"
#include "CmdSkillActivated.h"

class State
{
    public:
        State();
        virtual ~State();

        virtual void onLoad()=0;
        virtual void onUnload()=0;
        virtual void onUpdate(unsigned int d_t)=0;
        virtual void onRender(unsigned int d_t=0)=0;

        virtual void handleMousePress(int m_x, int m_y, int m_button)=0;
        virtual void handleMouseRelease(int m_x, int m_y, int m_button)=0;
        virtual void handleMouseMove(int m_x, int m_y)=0;
        virtual void handleMouseDrag(int m_x, int m_y, int m_button)=0;
        virtual void handleKeyPress(SDLKey key)=0;
        virtual void handleKeyRelease(SDLKey key)=0;
        virtual void handleWindowEvent(GUIEvent& ev)=0;
        virtual void handleCmdObjectLifeExpired(CmdObjectLifeExpired *ev)=0;
        virtual void handleCmdSkillActivated(CmdSkillActivated *ev)=0;

        SDL_Surface* getGraphicsContext() { return graphics_context; }
        void setGraphicsContext(SDL_Surface* val) { graphics_context = val; }

        GUIManager *getWindowManager() { return win_sys; }
        void setWindowManager(GUIManager *val) { win_sys = val; }

    protected:
    private:
        SDL_Surface* graphics_context;
        GUIManager *win_sys;

};

#endif // STATE_H
