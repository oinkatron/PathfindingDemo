#include "../include/MovementSystem.h"

MovementSystem::MovementSystem()
{
    //ctor
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void MovementSystem::Update(Object *ob, long d_t)
{
    PositionModule *p = ob->getModule<PositionModule>();
    VelocityModule *v = ob->getModule<VelocityModule>();
    BoundsModule *b = ob->getModule<BoundsModule>();
    MapModule *mp = ob->getModule<MapModule>();

    if (p && v && v->Travel())
    {
        if (mp && b)
        {
            float dist_x = v->velX() * ((float)d_t/1000.0f);
            float dist_y = v->velY() * ((float)d_t/1000.0f);

            bool tile_found = false;

            //MOVE ALONG X AXIS
            if (dist_x < 0.f)
            {
                for (int i = (int)p->X(); i > (int)(p->X() + dist_x); i--) //i = test_x
                {
                    if (b->Height()*2 > mp->getMap()->tileHeight())
                    {
                        for (int ii = p->Y() - b->Height(); ii < p->Y() + b->Height(); ii += mp->getMap()->tileHeight())
                        {
                            Tile* t = mp->getMap()->getTileFromCoords(i - b->Width(), ii);
                            if (t)
                            {
                                if (t->Type() == TILE_SOLID)
                                {
                                    tile_found = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        Tile *t = mp->getMap()->getTileFromCoords(i - b->Width(), p->Y()+ b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }

                        t = mp->getMap()->getTileFromCoords(i - b->Width(), p->Y() - b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }
                    }

                    if (tile_found)
                    {
                        p->X(i+1);
                        break;
                    }
                }
                if (!tile_found)
                {
                    p->stepX(dist_x);
                }
            }
            else if (dist_x > 0.f)
            {
                for (int i = (int)p->X(); i < (int)(p->X() + dist_x); i++) //i = test_x
                {
                    if (b->Height()*2 > mp->getMap()->tileHeight())
                    {
                        for (int ii = p->Y() - b->Height(); ii < p->Y() + b->Height(); ii += mp->getMap()->tileHeight())
                        {
                            Tile* t = mp->getMap()->getTileFromCoords(i + b->Width(), ii);
                            if (t)
                            {
                                if (t->Type() == TILE_SOLID)
                                {
                                    tile_found = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        Tile *t = mp->getMap()->getTileFromCoords(i + b->Width(), p->Y() + b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }

                        t = mp->getMap()->getTileFromCoords(i + b->Width(), p->Y() - b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }
                    }

                    if (tile_found)
                    {
                        p->X(i-1);
                        break;
                    }
                }

                if (!tile_found)
                {
                    p->stepX(dist_x);
                }
            }

            //MOVE_ALONG_Y_AXIS
            tile_found = false;
            if (dist_y < 0.f)
            {
                for (int i = (int)p->Y(); i >= (int)(p->Y() + dist_y); i--) //i = test_x
                {
                    if (b->Width() > mp->getMap()->tileWidth())
                    {
                        for (int ii = (int)p->X() - b->Width(); ii < p->X() + b->Width(); ii += mp->getMap()->tileWidth())
                        {
                            Tile* t = mp->getMap()->getTileFromCoords(ii, i - b->Height());
                            if (t)
                            {
                                if (t->Type() == TILE_SOLID)
                                {
                                    tile_found = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        Tile *t = mp->getMap()->getTileFromCoords(p->X() - b->Width(), i - b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }

                        t = mp->getMap()->getTileFromCoords(p->X() + b->Width(), i - b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }
                    }

                    if (tile_found)
                    {
                        p->Y(i+1);
                        break;
                    }
                }

                if (!tile_found)
                {
                    p->stepY(dist_y);
                }
            }
            else if (dist_y > 0.f)
            {
                for (int i = (int)p->Y(); i <= (int)(p->Y() + dist_y); i++) //i = test_y
                {
                    if (b->Width() > mp->getMap()->tileHeight())
                    {
                        //int c = 0;
                        for (int ii = p->X() - b->Height(); ii < p->X() + b->Width(); ii += mp->getMap()->tileWidth())
                        {
                            Tile* t = mp->getMap()->getTileFromCoords(ii, i + b->Height());
                            if (t)
                            {
                                if (t->Type() == TILE_SOLID)
                                {
                                    tile_found = true;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        Tile *t = mp->getMap()->getTileFromCoords(p->X() - b->Width(), i + b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }

                        t = mp->getMap()->getTileFromCoords(p->X() + b->Width(), i + b->Height());
                        if (t)
                        {
                            if (t->Type() == TILE_SOLID)
                            {
                                tile_found = true;
                                break;
                            }
                        }
                    }

                    if (tile_found)
                    {
                        p->Y(i-1);
                        break;
                    }
                }

                if (!tile_found)
                {
                    p->stepY(dist_y);
                }
            }

        }
        else
        {
            p->stepX(v->velX() * ((float)d_t/1000.f));
            p->stepY(v->velY() * ((float)d_t/1000.f));
        }

    }
}
