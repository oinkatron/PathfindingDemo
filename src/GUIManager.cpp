#include "../include/GUIManager.h"

unsigned long GUIManager::next_id = 0;

GUIManager::GUIManager()
{
    border_sheet = NULL;
    window_list.clear();
}

GUIManager::~GUIManager()
{
    //dtor
}

Frame* GUIManager::createWindow(int x, int y, int w, int h)
{
    unsigned long this_id = next_id++;
    Frame *tmp = new Frame(this_id);
    tmp->setDimensions(x, y, w, h);
    tmp->setBorder(border_sheet);
    window_list[this_id] = tmp;

    return tmp;
}

bool GUIManager::addComponent(unsigned long id, Frame *comp)
{
    map<unsigned long, Frame*>::iterator it;
    it = window_list.find(id);

    if (it != window_list.end())
    {
        it->second->addComponent(comp);
        return true;
    }

    return false;
}

void GUIManager::renderGUI(Renderer *r)
{
    map<unsigned long, Frame*>::iterator it;

    for (it = window_list.begin(); it != window_list.end(); it++)
    {
        it->second->render(r);
    }
}

Frame* GUIManager::processMouse(int mx, int my)
{
    map<unsigned long, Frame*>::iterator it;
    Frame *tmp = NULL;

    for (it = window_list.begin(); it != window_list.end(); it++)
    {
        tmp = it->second->isInside(mx, my);
        if (tmp != NULL)
        {
            return tmp;
        }
    }

    return NULL;
}
