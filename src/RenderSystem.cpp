#include "../include/RenderSystem.h"

RenderSystem::RenderSystem()
{
    game_cam = 0;
    renderer = NULL;
}

RenderSystem::~RenderSystem()
{
    //dtor
}

void RenderSystem::Update(Object *ob, long d_t)
{
    PositionModule *p = ob->getModule<PositionModule>();
    BoundsModule *b = ob->getModule<BoundsModule>();
    WaypointModule *wp_m = ob->getModule<WaypointModule>();
    ImageModule *i_m = ob->getModule<ImageModule>();
    SpriteModule *spr = ob->getModule<SpriteModule>();

    if (p && renderer)
    {
        if (b)
        {
           if (p->X() - b->OffsetX() + b->Width() > game_cam->getXOffset() && p->X() - b->OffsetX() < game_cam->getXOffset()+game_cam->getWidth() && p->Y() - b->OffsetY() + b->Height() > game_cam->getYOffset() && p->Y() - b->OffsetY() < game_cam->getYOffset() + game_cam->getHeight())
           {

               if (spr)
               {
                   if (game_cam)
                   {
                       renderer->drawSprite(spr->getSprite(), (int)p->X() - b->OffsetX() - game_cam->getXOffset(), (int)p->Y() - b->OffsetY() - game_cam->getYOffset());
                   }
                   else
                   {
                        renderer->drawSprite(spr->getSprite(), (int)p->X() - b->OffsetX(), (int)p->Y() - b->OffsetY());
                   }
               }
               else if (i_m)
               {
                   clog << "Has Image module" << endl;
                   if (game_cam)
                   {
                       renderer->drawImage(i_m->getImage(), (int)p->X()- b->OffsetX() - game_cam->getXOffset(), (int)p->Y() - b->OffsetY() - game_cam->getYOffset());
                   }
                   else
                   {
                       renderer->drawImage(i_m->getImage(), (int)p->X() - b->OffsetX(), (int)p->Y() - b->OffsetY());
                   }
               }
               else
               {
                   renderer->setDrawColor(128, 0, 128);
                   if (game_cam)
                   {
                      renderer->drawRect((int)p->X() - b->OffsetX() - game_cam->getXOffset(), (int)p->Y() - b->OffsetY() - game_cam->getYOffset(), b->Width(), b->Height());
                   }
                   else
                   {
                      renderer->drawRect((int)p->X() - b->OffsetX(), (int)p->Y() - b->OffsetY(), b->Width(), b->Height());
                   }

               }

               renderer->setDrawColor(255, 0, 0);
               renderer->drawRect((int)p->X() - game_cam->getXOffset() - b->Width(), (int)p->Y() - game_cam->getYOffset() - b->Height(), b->Width()*2, b->Height()*2);

            }

        }
        else
        {
           if (p->X() > game_cam->getXOffset() && p->X() < game_cam->getXOffset() + game_cam->getWidth() && p->Y() > game_cam->getYOffset() && p->Y() < game_cam->getYOffset() + game_cam->getHeight() && (i_m || spr))
           {

               if (spr)
               {
                   if (game_cam)
                   {
                       renderer->drawSprite(spr->getSprite(), (int)p->X() - game_cam->getXOffset(), (int)p->Y() - game_cam->getYOffset());
                   }
                   else
                   {
                        renderer->drawSprite(spr->getSprite(), (int)p->X(), (int)p->Y());
                   }
               }
               else if (i_m)
               {
                   clog << "Has Image module" << endl;
                   if (game_cam)
                   {
                       renderer->drawImage(i_m->getImage(), (int)p->X() - game_cam->getXOffset(), (int)p->Y() - game_cam->getYOffset());
                   }
                   else
                   {
                       renderer->drawImage(i_m->getImage(), (int)p->X(), (int)p->Y());
                   }
               }

               renderer->setDrawColor(255, 0, 0);
               renderer->drawRect((int)p->X() - game_cam->getXOffset(), (int)p->Y() - game_cam->getYOffset(), 2, 2);

            }
        }

       if (wp_m && wp_m->getPath()->size() > 1)
       {
           renderer->setDrawColor(255, 255, 255);
           renderer->drawLine(p->X() - game_cam->getXOffset(), p->Y() - game_cam->getYOffset(), wp_m->getNextNode().X() - game_cam->getXOffset(), wp_m->getNextNode().Y() - game_cam->getYOffset());
           renderer->setDrawColor(255, 0, 0);
           renderer->drawBox(wp_m->getNextNode().X()-2 - game_cam->getXOffset(), wp_m->getNextNode().Y()-2-game_cam->getYOffset(), 4, 4);

           vector<Vector2D> *l = wp_m->getPath();
           vector<Vector2D>::iterator it = l->begin();

           for (it; it != l->end()-1; it++)
           {
               Vector2D &f = *it, &s = *(it+1);

               renderer->setDrawColor(255, 255, 255);
               renderer->drawLine(f.X() - game_cam->getXOffset(), f.Y() - game_cam->getYOffset(), s.X() - game_cam->getXOffset(), s.Y() - game_cam->getYOffset());
               renderer->setDrawColor(255, 0, 0);
               renderer->drawBox(f.X()-2 - game_cam->getXOffset(), f.Y()-2 - game_cam->getYOffset(), 4, 4);
           }
       }
    }
}
