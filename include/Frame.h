#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <string>
#include <SDL/SDL.h>

#include "Tilesheet.h"
#include "Renderer.h"

using namespace std;

class Frame
{
    enum FrameState {
        FRAME_IDLE,
        FRAME_HOVER,
        FRAME_CLICKED
    };

    enum BorderIndex {
    TOP_LEFT_CORNER,
    TOP_EDGE,
    TOP_RIGHT_CORNER,
    LEFT_EDGE,
    CENTER,
    RIGHT_EDGE,
    BOTTOM_LEFT_CORNER,
    BOTTOM_EDGE,
    BOTTOM_RIGHT_CORNER,
    };

    public:
        Frame(unsigned long id);
        virtual ~Frame();

        Frame* isInside(int x, int y);
        Frame* isInside(int x, int y, int off_x, int off_y);

        void addComponent(Frame *f) { component_list.push_back(f); }
        //void removeComponent(Frame *f);
        //void removeComponent(string comp_name);

        void setName(string val) { name = val; }
        string getName() { return name; }

        void setAction(string val) { action = val; }
        string getAction() { return action; }

        void setCaption(string val) { caption = val; }
        string getCaption() { return caption; }

        void setBorder(Tilesheet *bs) { border_sheet = bs; updateBorder(); }
        Tilesheet* getBorder() { return border_sheet; }

        void setDimensions(int x, int y, int w, int h) { dimen = (SDL_Rect) { x, y, w, h}; updateBorder(); }

        void X(int val) { dimen.x = val; updateBorder(); }
        void Y(int val) { dimen.y = val; updateBorder(); }

        void Width(int val) { dimen.w = val; updateBorder(); }
        int Width() { return dimen.w; }

        void Height(int val) { dimen.h = val; updateBorder(); }
        int Height() { return dimen.h; }

        void setBGColor(int r, int g, int b) { bg_color = (SDL_Color) {r, g, b, 255}; }
        void setBGColor(SDL_Color &c) { bg_color.r = c.r; bg_color.g = c.g; bg_color.b = c.b; bg_color.unused = 255; }

        void setFGColor(int r, int g, int b) { fg_color = (SDL_Color) {r, g, b, 255}; }
        void setFGColor(SDL_Color &c) { fg_color.r = c.r; fg_color.g = c.g; fg_color.b = c.b; fg_color.unused = 255; }

        SDL_Color& getBGColor() { return bg_color; }
        SDL_Color& getFGColor() { return fg_color; }

        virtual void render(Renderer *r);
        virtual void render(Renderer *r, int off_x, int off_y);

        unsigned long getUID() { return u_id; }

    protected:
        vector <Frame*> component_list;

        unsigned long u_id;

        string name, old_name;
        string action, old_action;
        string caption, old_caption;

        SDL_Surface* name_srf;
        SDL_Surface* action_srf;
        SDL_Surface* caption_srf;

        SDL_Color fg_color, old_fg_color;
        SDL_Color bg_color, old_bg_color;

        SDL_Rect dimen, border;

        FrameState cur_state;
        Tilesheet *border_sheet;
    private:
        void updateBorder() { if (border_sheet) { border = (SDL_Rect) {dimen.x - border_sheet->tileWidth(), dimen.y - border_sheet->tileHeight(), dimen.w + (border_sheet->tileWidth()*2), dimen.h + (border_sheet->tileHeight()*2)}; } else { border = (SDL_Rect){0, 0, 0, 0}; } }

};

#endif // FRAME_H
