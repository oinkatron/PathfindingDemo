#include "../include/Renderer.h"

Renderer::Renderer()
{
    context = NULL;
    draw_font = NULL;

    draw_color = (SDL_Color){0, 0, 0, 255 };
    tmp = (SDL_Rect){0, 0, 0, 0};
}

Renderer::~Renderer()
{
    //dtor
}


void Renderer::drawRect(SDL_Rect &r)
{
    if (context)
    {
        SDL_FillRect(context, &r, SDL_MapRGB(context->format, draw_color.r, draw_color.g, draw_color.b));
    }
}

void Renderer::drawRect(int x, int y, int w, int h)
{
    if (context)
    {
        tmp = (SDL_Rect) {x, y, w, h};
        SDL_FillRect(context, &tmp, SDL_MapRGB(context->format, draw_color.r, draw_color.g, draw_color.b));
    }
}

void Renderer::drawSurface(SDL_Surface *surf, int x, int y, SDL_Rect *clip)
{
    if (context && surf)
    {
        if (clip)
        {
            tmp = (SDL_Rect){x, y, clip->w, clip->h};
            SDL_BlitSurface(surf, clip, context, &tmp);
        }
        else
        {
            tmp = (SDL_Rect){x, y, surf->w, surf->h};
            SDL_BlitSurface(surf, NULL, context, &tmp);
        }
    }
}

void Renderer::drawImage(Image *img, int x, int y, SDL_Rect *clip)
{
    if (context && img && img->getRaw())
    {
        if (clip)
        {
            tmp = (SDL_Rect){x, y, clip->w, clip->h};
            SDL_BlitSurface(img->getRaw(), clip, context, &tmp);
        }
        else
        {
            tmp = (SDL_Rect){x, y, img->getW(), img->getH()};
            SDL_BlitSurface(img->getRaw(), NULL, context, &tmp);
        }

    }
}

void Renderer::drawSprite(Sprite *spr, int x, int y, int frame_num)
{
    if (context && spr && spr->getSheet() && spr->getSheet()->getRaw())
    {
        tmp = (SDL_Rect){x, y, spr->getFrameWidth(), spr->getFrameHeight()};
        if (frame_num != -1)
        {
            SDL_BlitSurface(spr->getSheet()->getRaw(), spr->getFrame(frame_num), context, &tmp);
        }
        else
        {
            SDL_BlitSurface(spr->getSheet()->getRaw(), spr->getNextFrame(), context, &tmp);
        }
    }
}

void Renderer::drawText(string txt, int x, int y)
{
    if (context && draw_font)
    {
        SDL_Surface *msg = TTF_RenderText_Solid(draw_font->getRaw(), txt.c_str(), draw_color);
        if (msg)
        {
            tmp = {x, y, msg->w, msg->h};
            SDL_BlitSurface(msg, NULL, context, &tmp);
        }

    }
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    if (context)
    {
        lineRGBA(context, x1, y1, x2, y2, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
    }
}

void Renderer::drawBox(int x, int y, int w, int h)
{
    if (context)
    {
        lineRGBA(context, x, y, x+w, y, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, x, y, x, y+h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, x+w, y, x+w, y+h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, x, y+h, x+w, y+h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
    }
}

void Renderer::drawBox(SDL_Rect &r)
{
    if (context)
    {
        lineRGBA(context, r.x, r.y, r.x+r.w, r.y, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, r.x, r.y, r.x, r.y+r.h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, r.x+r.w, r.y, r.x+r.w, r.y+r.h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
        lineRGBA(context, r.x, r.y+r.h, r.x+r.w, r.y+r.h, draw_color.r, draw_color.g, draw_color.b, draw_color.unused);
    }
}
