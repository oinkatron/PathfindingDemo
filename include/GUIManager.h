#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <map>
#include <string>

#include "Frame.h"
#include "Renderer.h"

using namespace std;

enum GUIEvent_Type
{
    GUIEVENT_MOVE = 1,
    GUIEVENT_RESIZE = 2,
    GUIEVENT_PRESSED = 3,
    GUIEVENT_RELEASED = 4,
    GUIEVENT_CLOSE = 5,
    GUIEVENT_OPEN = 6
};

struct GUIEvent
{
    Frame *comp;
    GUIEvent_Type gui_type;
};

class GUIManager
{
    public:
        GUIManager();
        virtual ~GUIManager();

        Frame* createWindow(int x, int y, int w, int h);
        bool addComponent(unsigned long id, Frame* comp);

        void renderGUI(Renderer *r);
        void setDefaultBorder(Tilesheet *b_sheet) { border_sheet = b_sheet; }

        Frame* processMouse(int mx, int my);

    protected:
    private:
        static unsigned long next_id;
        map<unsigned long, Frame*> window_list;
        Tilesheet *border_sheet;
};

#endif // GUIMANAGER_H
