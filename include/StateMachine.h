#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>

#include "State.h"

using namespace std;

class StateMachine
{
    public:
        StateMachine();
        virtual ~StateMachine();

        void pushState(State *new_state) { state_list.push_back(new_state); onLoad(); }
        void popState() { onUnload(); state_list.erase(state_list.begin() + state_list.size() - 1); }

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
        void onRender(unsigned int d_t=0);

    protected:
    private:
        vector <State*> state_list;
};

#endif // STATEMACHINE_H
