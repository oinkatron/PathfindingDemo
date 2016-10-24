#include "../include/WaypointSystem.h"

WaypointSystem::WaypointSystem()
{
    //ctor
}

WaypointSystem::~WaypointSystem()
{
    //dtor
}

void WaypointSystem::Update(Object *ob, long d_t)
{
    PositionModule *p = ob->getModule<PositionModule>();
    VelocityModule *v = ob->getModule<VelocityModule>();
    WaypointModule *w_p = ob->getModule<WaypointModule>();
    SpriteModule *spr  = ob->getModule<SpriteModule>();

    if (p && v && w_p)
    {
        if (w_p->buildPath())
        {
            MapModule *mp_m = ob->getModule<MapModule>();
            if (mp_m)
            {
                calculatePath(w_p->getTail().X(), w_p->getTail().Y(), w_p->getPath(), p, mp_m);
                w_p->buildPath(false);
                v->Travel(true);
            }
        }
        else // move towards next node
        {
            Vector2D node = w_p->getNextNode();
            if (!(node.X() == -1 && node.Y() == -1)) //
            {
                Vector2D diff = p->getPosition() - node;
                if (diff.Length() < 5)
                {
                    w_p->popNode();
                    if (w_p->getPath()->size() == 0)
                    {
                        v->Travel(false);
                    }
                }

                Vector2D turn_vec = v->getVelocity()- diff;
                turn_vec.setFromPolar(turn_vec.Angle(), v->Speed());
                v->applyForce(turn_vec);
            }
        }
    }
}

void WaypointSystem::calculatePath(int end_x, int end_y, vector<Vector2D> *nodes, PositionModule *p, MapModule *mp)
{
   vector<PathNode*> closed_list;
   vector<PathNode*> open_list;

   PathNode *start = new PathNode;
   PathNode *end_n = new PathNode;

   Map *tmp_mp = mp->getMap();
   if (!tmp_mp)
   {
       nodes->clear();
       nodes->push_back(Vector2D(end_x, end_y));
       return;
   }

   end_n->map_pos = Vector2D((int)(end_x/tmp_mp->tileWidth()), (int)(end_y/tmp_mp->tileHeight()));
   end_n->parent = NULL;
   end_n->f = 0;
   end_n->g = 0;
   end_n->h = 0;

   Tile *test = tmp_mp->getTile(end_n->map_pos.X(), end_n->map_pos.Y());
   int off_x = 0, off_y = 0;
   if (!test) //If the end tile doesnt exist or isnt valid find closest tile
   {
        while(true)
        {
            if (abs(end_n->map_pos.X() + off_x - start->map_pos.X()) >= abs(end_n->map_pos.Y() + off_y - start->map_pos.Y()))
            {
                if (end_n->map_pos.X() + off_x - start->map_pos.X() < 0)
                {
                    off_x += 1;
                }
                else
                {
                   off_x -= 1;
                }
            }
            else
            {
                if (end_n->map_pos.Y() + off_y - start->map_pos.Y() < 0)
                {
                    off_y += 1;
                }
                else
                {
                    off_y -= 1;
                }
            }

            test = tmp_mp->getTile(end_n->map_pos.X()+off_x, end_n->map_pos.Y()+off_y);
            if (test && test->Type() != TILE_SOLID)
                break;
        }
   }
   else if (test->Type() == TILE_SOLID)
   {
        while(true)
        {
            if (abs(end_n->map_pos.X()+off_x - start->map_pos.X()) >= abs(end_n->map_pos.Y()+off_y - start->map_pos.Y()))
            {
                if (end_n->map_pos.X()+off_x - start->map_pos.X() < 0)
                {
                    off_x += 1;
                }
                else
                {
                   off_x -= 1;
                }
            }
            else
            {
                if (end_n->map_pos.Y()+off_y - start->map_pos.Y() < 0)
                {
                    off_y += 1;
                }
                else
                {
                    off_y -= 1;
                }
            }

            test = tmp_mp->getTile(end_n->map_pos.X()+off_x, end_n->map_pos.Y()+off_y);
            if (test && test->Type() != TILE_SOLID)
                break;
        }
   }

   if (off_x != 0 || off_y != 0)
   {
      end_n->map_pos.X(end_n->map_pos.X()+off_x);
      end_n->map_pos.Y(end_n->map_pos.Y()+off_y);
      end_x = (end_n->map_pos.X() * tmp_mp->tileWidth()) + (tmp_mp->tileWidth()/2);
      end_y = (end_n->map_pos.Y() * tmp_mp->tileHeight()) + (tmp_mp->tileHeight()/2);
   }

   if (nodes->size() > 0) //determine if we can reuse some of the path
   {
       vector<Vector2D>::iterator it = nodes->begin()+1;
       vector<Vector2D>::iterator tmp_it = nodes->end();
       int lowest_h = abs(((end_n->map_pos.X()*tmp_mp->tileWidth()) - p->X())) + abs(((end_n->map_pos.Y()*tmp_mp->tileHeight()) - p->Y()));
       int past_h = 0;

       Vector2D tmp;
       for (it; it != nodes->end(); it++)
       {
            past_h += tmp_mp->tileWidth();
            tmp = *it;
            int new_h = abs(((end_n->map_pos.X()*tmp_mp->tileWidth()) - tmp.X())) + abs(((end_n->map_pos.Y()*tmp_mp->tileHeight()) - tmp.Y())) + past_h;

            if (lowest_h > new_h)
            {
                lowest_h = new_h;
                tmp_it = it;
            }
       }

       if (tmp_it != nodes->end())
       {
           tmp = *tmp_it;
           start->map_pos = Vector2D((int)tmp.X()/tmp_mp->tileWidth(), (int)tmp.Y()/tmp_mp->tileHeight());

           nodes->erase(nodes->begin(), tmp_it);
       }
       else
       {
           nodes->clear();
           start->map_pos = Vector2D((int)(p->X()/tmp_mp->tileWidth()), (int)(p->Y()/tmp_mp->tileHeight()));
       }
   }
   else
   {
       start->map_pos = Vector2D((int)(p->X()/tmp_mp->tileWidth()), (int)(p->Y()/tmp_mp->tileHeight()));
   }

   start->parent = NULL;
   start->f = 0;
   start->g = 0;
   start->h = 0;

   if (start->map_pos.X() == end_n->map_pos.X() && start->map_pos.Y())
   {
       if (nodes->size() == 0)
          nodes->push_back(Vector2D(end_x, end_y));
       else
           nodes->insert(nodes->begin(), Vector2D(end_x, end_y));

       return;
   }

   closed_list.push_back(start);

   for (int i = -1; i <= 1; i++)
   {
       for (int ii = -1; ii <= 1; ii++)
       {
           if (tmp_mp->getTile(start->map_pos.X()+i, start->map_pos.Y()+ii) && !(i == 0 && ii == 0)) //check if tile is valid or its current tile
           {
               if (tmp_mp->getTile(start->map_pos.X()+i, start->map_pos.Y()+ii)->Type() != TILE_SOLID) //check tile type
               {
                   if (i != 0 && ii != 0)
                   {
                       if (tmp_mp->getTile(start->map_pos.X()+i, start->map_pos.Y())->Type() == TILE_SOLID || tmp_mp->getTile(start->map_pos.X(), start->map_pos.Y()+ii)->Type() == TILE_SOLID)
                       {//If its a corner tile and either of the two adjacent squares arent valid
                            continue;
                       }
                   }
                    PathNode *tmp = new PathNode;

                   tmp->map_pos = Vector2D(start->map_pos.X()+i, start->map_pos.Y()+ii);
                   tmp->parent = start;

                   calcFManHatten(tmp, end_n);
                   open_list.push_back(tmp);
               }
           }
       }
   }

   bool found_end = false;
   int end_m_x = 0;
   int end_m_y = 0;
   if (open_list.size() > 0)
       while (!found_end)
       {
           int smallest = open_list[0]->f;
           int lowest_f = 0;


           for (int i = 1; i < open_list.size(); i++)  //Get smallest f;
           {
                if (smallest > open_list[i]->f)
                {
                    smallest = open_list[i]->f;
                    lowest_f = i;
                }
           }

           //clog << "open_list size: " << open_list.size() << endl << "Lowest F in open list: " << open_list[lowest_f]->f << endl << "Map Coord: " << open_list[lowest_f]->map_pos.X() << " : " << open_list[lowest_f]->map_pos.Y() << endl;
           if (open_list[lowest_f]->map_pos.X() == end_n->map_pos.X() && open_list[lowest_f]->map_pos.Y() == end_n->map_pos.Y())
           {
                found_end = true;
                clog << "Found end node" << endl;
           }

           for (int i = -1; i <= 1; i++)
           {
               for (int ii = -1; ii <= 1; ii++)
               {
                   if (tmp_mp->getTile(open_list[lowest_f]->map_pos.X()+i, open_list[lowest_f]->map_pos.Y()+ii) && !(i == 0 && ii == 0)) //check if tile is valid or its current tile
                   {
                       bool found_closed = false;
                       bool found_open = false;
                       for (int j = 0; j < closed_list.size(); j++) //Check for closed tiles
                       {
                           if (open_list[lowest_f]->map_pos.X()+i == closed_list[j]->map_pos.X() && open_list[lowest_f]->map_pos.Y()+ii == closed_list[j]->map_pos.Y())
                            found_closed = true;
                       }

                       if (found_closed)
                            continue;

                       for (int j = 0; j < open_list.size(); j++) //Check for open tiles
                       {
                           if (open_list[lowest_f]->map_pos.X()+i == open_list[j]->map_pos.X() && open_list[lowest_f]->map_pos.Y()+ii == open_list[j]->map_pos.Y())
                           {
                               int old_f = open_list[j]->f;
                               int old_h = open_list[j]->h;
                               int old_g = open_list[j]->g;
                               PathNode *old_p = open_list[j]->parent;

                               open_list[j]->parent = open_list[lowest_f];
                               calcFManHatten(open_list[j], end_n);

                               if (old_g < open_list[j]->g)
                               {
                                   open_list[j]->parent = old_p;
                                   open_list[j]->f = old_f;
                                   open_list[j]->g = old_g;
                                   open_list[j]->h = old_h;
                               }

                               found_open = true;
                           }
                       }

                       if (found_open)
                           continue;

                       if (tmp_mp->getTile(open_list[lowest_f]->map_pos.X()+i, open_list[lowest_f]->map_pos.Y()+ii)->Type() != TILE_SOLID) //check tile type
                       {
                           if (i != 0 && ii != 0)
                           {
                               if (tmp_mp->getTile(open_list[lowest_f]->map_pos.X()+i, open_list[lowest_f]->map_pos.Y())->Type() == TILE_SOLID || tmp_mp->getTile(open_list[lowest_f]->map_pos.X(), open_list[lowest_f]->map_pos.Y()+ii)->Type() == TILE_SOLID)
                               {//If its a corner tile and either of the two adjacent squares arent valid
                                    continue;
                               }
                           }
                           PathNode *tmp = new PathNode;

                           tmp->map_pos = Vector2D(open_list[lowest_f]->map_pos.X()+i, open_list[lowest_f]->map_pos.Y()+ii);
                           tmp->parent = open_list[lowest_f];

                           calcFManHatten(tmp, end_n);
                           open_list.push_back(tmp);
                       }
                   }
               }
           }

           closed_list.push_back(open_list[lowest_f]);
           open_list.erase(open_list.begin()+lowest_f);

           if (open_list.size() == 0)
           {
               clog << "Open List empty break from it" << endl;
               break;
           }
       }

    if (found_end)
    {
        if (nodes->size() == 0)
        {
            nodes->push_back(Vector2D(end_x, end_y));
            PathNode *nxt = closed_list[closed_list.size()-1]->parent;
            while (nxt->parent != NULL)
            {
                nodes->push_back(Vector2D(nxt->map_pos.X()*tmp_mp->tileWidth() + (tmp_mp->tileWidth()/2), nxt->map_pos.Y()*tmp_mp->tileHeight() + (tmp_mp->tileHeight()/2)));
                nxt = nxt->parent;
            }

        }
        else
        {
            int n_size = nodes->size();
            vector<Vector2D>::iterator i_pos = nodes->end() - n_size;
            nodes->insert(i_pos, Vector2D(end_x, end_y));
            PathNode *nxt = closed_list[closed_list.size()-1]->parent;
            while (nxt->parent != NULL)
            {
                i_pos = nodes->end()-n_size;
                nodes->insert(i_pos, Vector2D(nxt->map_pos.X()*tmp_mp->tileWidth() + (tmp_mp->tileWidth()/2), nxt->map_pos.Y()*tmp_mp->tileHeight() + (tmp_mp->tileHeight()/2)));
                nxt = nxt->parent;
            }

        }
    }

    for (int i = 0; i < closed_list.size(); i++)
    {
        delete closed_list[i];
    }

    for (int i = 0; i < open_list.size(); i++)
    {
        delete open_list[i];
    }
}

void WaypointSystem::calcFManHatten(PathNode *cur, PathNode *tail)
{
    cur->h = fabs(((tail->map_pos.X() - cur->map_pos.X()) + (tail->map_pos.Y() - cur->map_pos.Y()))) * 10;

    if (abs(cur->parent->map_pos.X() - cur->map_pos.X()) == abs(cur->parent->map_pos.Y() - cur->map_pos.Y()))
    {
        cur->g = cur->parent->g + 14;
    }
    else
    {
        cur->g = cur->parent->g + 10;
    }
    cur->f = cur->g + cur->h;
}
