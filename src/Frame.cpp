#include "../include/Frame.h"

Frame::Frame(unsigned long id)
{
    u_id = id;
    name = "";
    caption = "";
    action = "";

    name_srf = NULL;
    caption_srf = NULL;
    action_srf = NULL;

    border_sheet = NULL;

    dimen = (SDL_Rect) {0, 0, 0, 0};
    fg_color = (SDL_Color) {0, 0, 0, 255};
    bg_color = (SDL_Color) {0, 0, 0, 255};
}

Frame::~Frame()
{
    for (int i = 0; i < component_list.size(); i++)
    {
        delete component_list[i];
    }
    component_list.clear();

    if (caption_srf)
        SDL_FreeSurface(caption_srf);

    if (name_srf)
        SDL_FreeSurface(name_srf);

    if (action_srf)
        SDL_FreeSurface(action_srf);
}

Frame* Frame::isInside(int mx, int my)
{
    if (border_sheet)
    {
        if (mx > border.x&& mx < border.x + border.w&& my > border.y && my < border.y + border.h)
        {
            Frame *tmp;
            for (int i = 0; i < component_list.size(); i++)
            {
                tmp = component_list[i]->isInside(mx, my, dimen.x, dimen.y);
                if (tmp != NULL)
                {
                    return tmp;
                }
            }

            return this;
        }
    }
    else
    {
        if (mx > dimen.x&& mx < dimen.x + dimen.w&& my > dimen.y && my < dimen.y + dimen.h)
        {
            Frame *tmp;
            for (int i = 0; i < component_list.size(); i++)
            {
                tmp = component_list[i]->isInside(mx, my, dimen.x, dimen.y);
                if (tmp != NULL)
                {
                    return tmp;
                }
            }

            return this;
        }
    }

    return NULL;
}

Frame* Frame::isInside(int mx, int my, int off_x, int off_y)
{
    if (border_sheet)
    {
        if (mx > border.x + off_x && mx < border.x + border.w + off_x && my > border.y + off_y && my < border.y + border.h + off_y)
        {
            Frame *tmp;
            for (int i = 0; i < component_list.size(); i++)
            {
                tmp = component_list[i]->isInside(mx, my, dimen.x + off_x, dimen.y + off_y);
                if (tmp != NULL)
                {
                    return tmp;
                }
            }

            return this;
        }
    }
    else
    {
        if (mx > dimen.x + off_x && mx < dimen.x + dimen.w + off_x && my > dimen.y + off_y && my < dimen.y + dimen.h + off_y)
        {
            Frame *tmp;
            for (int i = 0; i < component_list.size(); i++)
            {
                tmp = component_list[i]->isInside(mx, my, dimen.x + off_x, dimen.y + off_y);
                if (tmp != NULL)
                {
                    return tmp;
                }
            }

            return this;
        }
    }


    return NULL;
}

void Frame::render(Renderer *r)
{
    //Draw background
    r->setDrawColor(bg_color);
    r->drawRect(dimen);

    //Draw Border
    int rem;
    if (border_sheet)
    {
        if ((rem = border.w % border_sheet->tileWidth()) != 0)
        {
            for (int i = 1; i < ((border.w/border_sheet->tileWidth())-1); i++)
            {
                r->drawImage(border_sheet->baseImage(), border.x + (i*border_sheet->tileWidth()), border.y, border_sheet->getTile(TOP_EDGE));
                r->drawImage(border_sheet->baseImage(), border.x + (i*border_sheet->tileWidth()), border.y + border.h- border_sheet->tileHeight(), border_sheet->getTile(BOTTOM_EDGE));
            }

            SDL_Rect *old_r = border_sheet->getTile(TOP_EDGE);
            SDL_Rect new_r = (SDL_Rect){old_r->x, old_r->y, rem, old_r->h};
            r->drawImage(border_sheet->baseImage(), border.x + (border_sheet->tileWidth() * ((border.w/border_sheet->tileWidth())-1)), border.y, &new_r);

            old_r = border_sheet->getTile(BOTTOM_EDGE);
            new_r = (SDL_Rect){old_r->x, old_r->y, rem, old_r->h};
            r->drawImage(border_sheet->baseImage(), border.x + (border_sheet->tileWidth() * ((border.w/border_sheet->tileWidth())-1)), border.y + border.h - border_sheet->tileHeight(), &new_r);
        }
        else
        {
            for (int i = 1; i < (border.w/border_sheet->tileWidth())-1; i++)
            {
                r->drawImage(border_sheet->baseImage(), border.x + (i*border_sheet->tileWidth()), border.y, border_sheet->getTile(TOP_EDGE));
                r->drawImage(border_sheet->baseImage(), border.x + (i*border_sheet->tileWidth()), border.y + border.h- border_sheet->tileHeight(), border_sheet->getTile(BOTTOM_EDGE));
            }
        }

        if ((rem = border.h % border_sheet->tileHeight()) != 0)
        {
            for (int i = 1; i < (border.h/border_sheet->tileHeight())-1; i++)
            {
                r->drawImage(border_sheet->baseImage(), border.x, (i*border_sheet->tileHeight()) + border.y, border_sheet->getTile(LEFT_EDGE));
                r->drawImage(border_sheet->baseImage(), border.x + border.w - border_sheet->tileWidth(), (i*border_sheet->tileHeight()) + border.y, border_sheet->getTile(RIGHT_EDGE));
            }

            SDL_Rect *old_r = border_sheet->getTile(LEFT_EDGE);
            SDL_Rect new_r = (SDL_Rect){old_r->x, old_r->y, old_r->w, rem};
            r->drawImage(border_sheet->baseImage(), border.x, border.y + (border_sheet->tileHeight()*((border.h/border_sheet->tileHeight())-1)), &new_r);

            old_r = border_sheet->getTile(RIGHT_EDGE);
            new_r = (SDL_Rect){old_r->x, old_r->y, old_r->w, rem};
            r->drawImage(border_sheet->baseImage(), border.x + border.w - border_sheet->tileWidth(), border.y + (border_sheet->tileHeight() * ((border.h/border_sheet->tileHeight())-1)), &new_r);
        }
        else
        {
            for (int i = 1; i < (border.h/border_sheet->tileHeight())-1; i++)
            {
                r->drawImage(border_sheet->baseImage(), border.x, (i*border_sheet->tileHeight()) + border.y, border_sheet->getTile(LEFT_EDGE));
                r->drawImage(border_sheet->baseImage(), border.x + border.w - border_sheet->tileWidth(), (i*border_sheet->tileHeight()) + border.y, border_sheet->getTile(RIGHT_EDGE));
            }
        }



        r->drawImage(border_sheet->baseImage(), border.x, border.y, border_sheet->getTile(TOP_LEFT_CORNER));
        r->drawImage(border_sheet->baseImage(), border.x+border.w-border_sheet->tileWidth(), border.y, border_sheet->getTile(TOP_RIGHT_CORNER));
        r->drawImage(border_sheet->baseImage(), border.x, border.y+border.h-border_sheet->tileHeight(), border_sheet->getTile(BOTTOM_LEFT_CORNER));
        r->drawImage(border_sheet->baseImage(), border.x+border.w-border_sheet->tileWidth(), border.y+border.h-border_sheet->tileHeight(), border_sheet->getTile(BOTTOM_RIGHT_CORNER));
    }

    if (caption != "")
    {
        r->setDrawColor(fg_color);
        if (caption != old_caption || caption_srf == NULL)
        {
            caption_srf = r->surfaceFromText(caption);
            old_caption = caption;
        }

        r->drawSurface(caption_srf, dimen.x+1, dimen.y+1);
    }

    for (int i = 0; i < component_list.size(); i++)
    {
        component_list[i]->render(r, dimen.x, dimen.y);
    }
}

void Frame::render(Renderer *r, int off_x, int off_y)
{
    //Draw background
    r->setDrawColor(bg_color);
    r->drawRect(off_x + dimen.x, off_y + dimen.y, dimen.w, dimen.h);

    clog << "Made it into border_sheet_loop" << endl;
    if (border_sheet)
    {

        for (int i = 1; i < (dimen.x/border_sheet->tileWidth())-1; i++)
        {
            r->drawImage(border_sheet->baseImage(), i*border_sheet->tileWidth() + off_x, off_y, border_sheet->getTile(TOP_EDGE));
            r->drawImage(border_sheet->baseImage(), i*border_sheet->tileWidth() + off_x, off_y + dimen.h - border_sheet->tileHeight(), border_sheet->getTile(BOTTOM_EDGE));
        }
    }

    if (caption != "")
    {
        r->setDrawColor(fg_color);

        if (caption != old_caption || caption_srf == NULL || old_fg_color.r != fg_color.r || old_fg_color.g != fg_color.g || old_fg_color.b != fg_color.b)
        {
            r->setDrawColor(fg_color);
            caption_srf = r->surfaceFromText(caption);
            old_caption = caption;
            old_fg_color = fg_color;
        }

        r->drawSurface(caption_srf, off_x + dimen.x+1, off_y + dimen.y+1);
    }

    for (int i = 0; i < component_list.size(); i++)
    {
        component_list[i]->render(r, off_x + dimen.x, off_y + dimen.y);
    }
}
