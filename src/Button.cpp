#include "../include/Button.h"

Button::Button(string cap, string ac, int des_w, int des_h) : Frame (-1)
{
    caption = cap;
    action = ac;

    dimen.w = des_w;
    dimen.h = des_h;
}

Button::~Button()
{
    //dtor
}

void Button::render(Renderer *r)
{
    r->setDrawColor(getBGColor());
    r->drawRect(dimen);

    for (int i = 0; i < component_list.size(); i++)
    {
        component_list[i]->render(r, dimen.x, dimen.y);
    }

    if (caption != "")
    {
        r->setDrawColor(getFGColor());

        if (caption != old_caption || caption_srf == NULL)
        {
            caption_srf = r->surfaceFromText(caption);
            old_caption = caption;

            if (dimen.w == -1 || dimen.w < caption_srf->w)
                dimen.w = caption_srf->w;

            if (dimen.h == -1 || dimen.h < caption_srf->h)
                dimen.h = caption_srf->h;

        }

        r->drawSurface(caption_srf, (dimen.x + dimen.w) / 2, (dimen.y + dimen.h) / 2);
    }
}

void Button::render(Renderer *r, int off_x, int off_y)
{
    r->setDrawColor(getBGColor());
    r->drawRect(dimen.x + off_x, dimen.y + off_y, dimen.w, dimen.h);

    for (int i = 0; i < component_list.size(); i++)
    {
        component_list[i]->render(r, off_x + dimen.x, off_y + dimen.y);
    }

    if (caption != "")
    {
        r->setDrawColor(getFGColor());

        if (caption != old_caption || caption_srf == NULL)
        {
            caption_srf = r->surfaceFromText(caption);
            old_caption = caption;

            if (dimen.w == -1 || dimen.w < caption_srf->w)
                dimen.w = caption_srf->w;

            if (dimen.h == -1 || dimen.h < caption_srf->h)
                dimen.h = caption_srf->h;
        }

        r->drawSurface(caption_srf, dimen.x + (dimen.w / 2)+ off_x - (caption_srf->w/2), dimen.y + (dimen.h / 2) + off_y - (caption_srf->h / 2));
    }
}
