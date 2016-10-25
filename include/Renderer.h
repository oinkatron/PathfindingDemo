#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <string>

#include "Image.h"
#include "Sprite.h"
#include "Font.h"

using namespace std;

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        virtual void drawRect(int x, int y, int w, int h);
        virtual void drawRect(SDL_Rect &r);
        virtual void drawBox (int x, int y, int w, int h);
        virtual void drawBox (SDL_Rect &r);

        virtual void drawSurface(SDL_Surface *surf, int x, int y, SDL_Rect *clip=NULL);
        virtual void drawImage(Image *img, int x, int y, SDL_Rect *clip=NULL);
        virtual void drawSprite(Sprite *spr, int x, int y, int frame_num=-1);

        virtual void drawLine(int x1, int y1, int x2, int y2);

        virtual void drawText(string txt, int x, int y);

        SDL_Surface *surfaceFromText(string txt) { if (draw_font) return TTF_RenderText_Solid(draw_font->getRaw(), txt.c_str(), draw_color); else return NULL; }

        void setContext(SDL_Surface *val) { context = val; }
        SDL_Surface *getContext() { return context; }

        void setDrawColor(int r, int g, int b) { draw_color = (SDL_Color){r, g, b, 255}; }
        void setDrawColor(SDL_Color &c) { draw_color.r = c.r; draw_color.g = c.g; draw_color.b = c.b; draw_color.unused = 255; }

        void setDrawFont(Font *f) { draw_font = f; }
        void setDrawFont(string f_name, int s) { draw_font = Font::getFont(f_name, s); }
        Font* getDrawFont() { return draw_font; }

    protected:
    private:
        SDL_Rect tmp;
        SDL_Color draw_color;
        SDL_Surface *context;
        Font *draw_font;
};

#endif // RENDERER_H
