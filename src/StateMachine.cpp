#include "../include/StateMachine.h"

StateMachine::StateMachine()
{
    //ctor
}

StateMachine::~StateMachine()
{
    //dtor
}

void StateMachine::onLoad()
{
    state_list[state_list.size()-1]->onLoad();
}

void StateMachine::onUnload()
{
    state_list[state_list.size()-1]->onUnload();
}

void StateMachine::onUpdate(unsigned int d_t)
{
    state_list[state_list.size()-1]->onUpdate(d_t);
}

void StateMachine::onRender(unsigned int d_t)
{
    state_list[state_list.size()-1]->onRender();
}

void StateMachine::handleKeyPress(SDLKey key)
{
    state_list[state_list.size()-1]->handleKeyPress(key);
}

void StateMachine::handleKeyRelease(SDLKey key)
{
    state_list[state_list.size()-1]->handleKeyRelease(key);
}

void StateMachine::handleMouseDrag(int m_x, int m_y, int m_button)
{
    state_list[state_list.size()-1]->handleMouseDrag(m_x, m_y, m_button);
}

void StateMachine::handleMouseMove(int m_x, int m_y)
{
    state_list[state_list.size()-1]->handleMouseMove(m_x, m_y);
}

void StateMachine::handleMousePress(int m_x, int m_y, int m_button)
{
    state_list[state_list.size()-1]->handleMousePress(m_x, m_y, m_button);
}

void StateMachine::handleMouseRelease(int m_x, int m_y, int m_button)
{
    state_list[state_list.size()-1]->handleMouseRelease(m_x, m_y, m_button);
}

void StateMachine::handleWindowEvent(GUIEvent &ev)
{
    state_list[state_list.size()-1]->handleWindowEvent(ev);
}

void StateMachine::handleCmdObjectLifeExpired(CmdObjectLifeExpired *ev)
{
    state_list[state_list.size()-1]->handleCmdObjectLifeExpired(ev);
}

void StateMachine::handleCmdSkillActivated(CmdSkillActivated *ev)
{
    state_list[state_list.size()-1]->handleCmdSkillActivated(ev);
}

