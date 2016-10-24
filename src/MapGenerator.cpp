#include "../include/MapGenerator.h"

MapGenerator::MapGenerator()
{
    //ctor
}

MapGenerator::~MapGenerator()
{
    //dtor
}

Map *MapGenerator::generateMap(unsigned int seed)
{
    srand(seed); //seed the num gen should make the same maps based on seed

    //load tilesheet
    Tilesheet *t_sheet = new Tilesheet();
    t_sheet->loadTilesheet("test");
    if (!t_sheet)
    {
        clog << "Cannot load tilesheet can't generate map..." << endl;
        return NULL;
    }

    t_width = t_sheet->tileWidth();
    t_height = t_sheet->tileHeight();

    //Pick map size 1 - 3
    map_size_gen = randInt(1, 4);

    clog << "Map Gen: " << map_size_gen << endl;

    m_width = (map_size_gen) * 63;
    m_height = (map_size_gen) * 63;

    c_wide = 7;
    c_tall = 7;

    total_tiles = m_width * m_height;

    clog << "Map Width: " << m_width << " ; Map Height: " << m_height << endl;

    c_width = m_width / c_wide;
    c_height = m_height / c_tall;

    clog << "Cell Width: " << c_width << " : Cell Height: " << c_height << endl;

    Map *gen = new Map();
    gen->initNewMap("Gen_Map_", m_width, m_height, t_width, t_height);
    gen->tSheet(t_sheet);

    //Generate start_room
    c_start_x = room_cell_x = randInt(0, c_wide);
    c_start_y = room_cell_y = randInt(0, c_tall);

    clog << "Starting Cell: " << c_start_x << " : " << c_start_y << endl;

    room_width = randInt(2, c_width);
    if (room_width < c_width * 0.5)
    {
        if (randInt(0, 100) > 50)
        {
           room_height = randInt((c_width *0.5)+1, c_width);
        }
        else
        {
            room_height = randInt(2, c_height);
        }
    }
    else
    {
        room_height = randInt(2, c_height);
    }

    room_st_x = randInt(0, c_width - room_width);
    room_st_y = randInt(0, c_height - room_height);

    gen->setStartX((c_start_x * c_width) + room_st_x + (room_width*0.5));
    gen->setStartY((c_start_y * c_height) + room_st_y + (room_height*0.5));

    RoomInfo *new_r = new RoomInfo;
    new_r->cell_x = room_cell_x;
    new_r->cell_y = room_cell_y;
    new_r->x = room_st_x;
    new_r->y = room_st_y;
    new_r->width = room_width;
    new_r->height = room_height;

    room_list.push_back(new_r);
    used_tiles = room_width*room_height;

    while (used_tiles < total_tiles * 0.5 && generateRoom())
    {

    }

    generatePaths();

    clog << "Carving rooms..." << endl;
    carveRooms(gen);
    carvePaths(gen);

    return gen;
}

bool MapGenerator::generateRoom()
{
    if (!getNextCell())
    {
        return false;
    }

    //Generate Room dimensions
    room_width = randInt(2, c_width);
    if (room_width < c_width * 0.5)
    {
        if (randInt(0, 100) > 50)
        {
           room_height = randInt((c_width *0.5)+1, c_width);
        }
        else
        {
            room_height = randInt(2, c_height);
        }
    }
    else
    {
        room_height = randInt(2, c_height);
    }

    room_st_x = randInt(0, c_width - room_width);
    room_st_y = randInt(0, c_height - room_height);

    //Store the room
    RoomInfo *new_r;
    new_r = new RoomInfo;
    new_r->cell_x = room_cell_x;
    new_r->cell_y = room_cell_y;

    new_r->x = room_st_x;
    new_r->y = room_st_y;

    new_r->width = room_width;
    new_r->height = room_height;

    room_list.push_back(new_r);

    used_tiles += room_width * room_height;

    return true;
}

void MapGenerator::generatePaths()
{
    int left_side = -1, top_side = -1, a_side_choice = -1, b_side_choice = -1;
    int a_rm_st_x, a_rm_st_y, b_rm_st_x, b_rm_st_y;
    int a_cen_x, a_cen_y, b_cen_x, b_cen_y;

    PathInfo *new_p;
    RoomInfo *a, *b;

    for (list<RoomInfo*>::iterator it=room_list.begin(); it != room_list.end(); it++) //loop through all rooms
    {
        a =*it;
        it++;
        if (it == room_list.end())
        {
            it--;
            continue;
        }
        it--;
        b = *(++it);
        it--;

        a_rm_st_x = (a->cell_x * c_width) + a->x;
        a_rm_st_y = (a->cell_y * c_height) + a->y;
        b_rm_st_x = (b->cell_x * c_width) + b->x;
        b_rm_st_y = (b->cell_y * c_height) + b->y;

        a_cen_x = (a_rm_st_x + (a->width*0.5));
        a_cen_y = (a_rm_st_y + (a->height*0.5));
        b_cen_x = (b_rm_st_x + (b->width*0.5));
        b_cen_y = (b_rm_st_y + (b->height*0.5));

        //determine possible sides
        if (a_cen_x < b_cen_x)
        {
            left_side = 0;
        }
        else if (a_cen_x > b_cen_x)
        {
            left_side = 1;
        }
        else
        {
            left_side = 2;
        }

        if (a_cen_y < b_cen_y)
        {
            top_side = 0;
        }
        else if (a_cen_y > b_cen_y)
        {
            top_side = 1;
        }
        else
        {
            top_side = 2;
        }

        b_side_choice = randInt(1, 3); //pick at random b's side (it doesnt have any sides blocked yet)

        if (((top_side == 0 && !a->wall_info[WALL_BOTTOM]) || (top_side == 1 && !a->wall_info[WALL_TOP])) && left_side != 2)
        {
            if ((left_side == 0 && !a->wall_info[WALL_RIGHT]) || (left_side == 1 && !a->wall_info[WALL_LEFT]))
            {
                a_side_choice = randInt(1, 3);
            }
            else
            {
                a_side_choice = 2;
            }
        }
        else if ((left_side == 0 && !a->wall_info[WALL_RIGHT]) || (left_side == 1 && !a->wall_info[WALL_LEFT]) && top_side != 2)
        {
            a_side_choice = 1;
        }
        else
        {
            if (left_side == 2)
            {
                a_side_choice = 1;
                b_side_choice = 1;
            }
            else
            {
                a_side_choice = 2;
                b_side_choice = 2;
            }
        }

        new_p = new PathInfo;

        if (left_side != 2 && top_side != 2) // if they aren't aligned
        {
            if (a_side_choice == b_side_choice) // if choices are on the same side
            {
                if (a_side_choice == 1) //horizontal sides used
                {
                    new_p->a_hor = true;
                    new_p->b_hor = true;
                    if (left_side == 1)
                    {
                        a->wall_info[WALL_LEFT] = true;
                        new_p->a_x = a_rm_st_x;
                        new_p->b_x = b_rm_st_x + b->width;
                    }
                    else
                    {
                        a->wall_info[WALL_RIGHT] = true;
                        new_p->a_x = a_rm_st_x + a->width;
                        new_p->b_x = b_rm_st_x;
                    }

                    new_p->a_y = randInt(a_rm_st_y+1, a_rm_st_y + a->height);
                    new_p->b_y = randInt(b_rm_st_y+1, b_rm_st_y + b->height);

                    if (new_p->a_y == new_p->b_y)
                    {
                        new_p->path_t = P_STRAIGHT;
                    }
                    else
                    {
                        new_p->path_t = P_SNAKE;
                        new_p->c_x = randInt(new_p->a_x+1, new_p->b_x);
                        new_p->c_y = -1;
                    }
                }
                else //verticle sides
                {
                    new_p->a_hor = false;
                    new_p->b_hor = false;
                    if (top_side == 1)
                    {
                        a->wall_info[WALL_TOP] = true;
                        new_p->a_y = a_rm_st_y;
                        new_p->b_y = b_rm_st_y + b->height;
                    }
                    else
                    {
                        a->wall_info[WALL_BOTTOM] = true;
                        new_p->a_y = a_rm_st_y + a->height;
                        new_p->b_y = b_rm_st_y;
                    }

                    new_p->a_x = randInt(a_rm_st_x+1, a_rm_st_x+a->width);
                    new_p->b_x = randInt(b_rm_st_x+1, b_rm_st_x+b->width);

                    if (new_p->b_y == new_p->a_y)
                    {
                        new_p->path_t = P_STRAIGHT;
                    }
                    else
                    {
                        new_p->path_t = P_SNAKE;
                        new_p->c_y = randInt(new_p->a_y, new_p->b_y);
                        new_p->c_x = -1;
                    }
                }
            }
            else //choices are on opposite sides
            {
                new_p->path_t = P_ELBOW;
                if (a_side_choice == 1) //horizontal
                {
                    new_p->a_hor = true;
                    new_p->b_hor = false;
                    if (left_side == 1)
                    {
                        a->wall_info[WALL_LEFT] = true;
                        new_p->a_x = a_rm_st_x;
                    }
                    else
                    {
                        a->wall_info[WALL_RIGHT] = true;
                        new_p->a_x = a_rm_st_x + a->width;
                    }

                    if (top_side == 1)
                    {
                        new_p->b_y = b_rm_st_y + b->height;
                    }
                    else
                    {
                        new_p->b_y = b_rm_st_y;
                    }

                    new_p->a_y = randInt(a_rm_st_y+1, a_rm_st_y+a->height);
                    new_p->b_x = randInt(b_rm_st_x+1, b_rm_st_x+b->width);

                }
                else //vertivle
                {
                    new_p->a_hor = false;
                    new_p->a_hor = true;
                    if (top_side == 1)
                    {
                        a->wall_info[WALL_TOP] = true;
                        new_p->a_y = a_rm_st_y + b->height;
                    }
                    else
                    {
                        a->wall_info[WALL_BOTTOM] = true;
                        new_p->a_y = a_rm_st_y;
                    }

                    if (left_side == 1)
                    {
                        new_p->b_x = b_rm_st_x;
                    }
                    else
                    {
                        new_p->b_x = b_rm_st_x + b->width;
                    }

                    new_p->a_x = randInt(a_rm_st_x+1, a_rm_st_x+a->width);
                    new_p->b_y = randInt(b_rm_st_y+1, b_rm_st_y+b->height);
                }
            }
        }
        else
        {
            if (left_side == 2)
            {
                new_p->a_hor = false;
                new_p->b_hor = false;

                new_p = new PathInfo;
                new_p->path_t = P_STRAIGHT;

                new_p->a_x = a_cen_x;
                new_p->b_x = b_cen_x;

                if (top_side == 0)
                {
                    new_p->a_y = a_rm_st_y + a->height;
                    new_p->b_y = b_rm_st_y;
                }
                else if (top_side == 1)
                {
                    new_p->a_y = a_rm_st_y;
                    new_p->b_y = b_rm_st_y + b->height;
                }

            }
            else
            {
                new_p->a_hor = true;
                new_p->b_hor = true;
                new_p = new PathInfo;
                new_p->path_t = P_STRAIGHT;
                new_p->a_y = a_cen_y;
                new_p->b_y = b_cen_y;

                if (left_side == 0)
                {
                    new_p->a_x = a_rm_st_x + a->width;
                    new_p->b_x = b_rm_st_x;
                }
                else if (left_side == 1)
                {
                    new_p->a_x = a_rm_st_x;
                    new_p->b_x = b_rm_st_x + b->width;
                }
            }
        }
        path_list.push_back(new_p);
    }
}

bool MapGenerator::getNextCell()
{
    RoomInfo *new_r;

    bool loop_complete = false;
    bool uni;
    RoomInfo *tmp;

    for (int i = 0; i < 1000; i++)
    {
        room_cell_x = randInt(0, c_wide);
        room_cell_y = randInt(1, c_tall);

        uni = true;

        for (list<RoomInfo*>::iterator it = room_list.begin(); it != room_list.end(); it++)
        {
            tmp = *it;
            if (room_cell_x == tmp->cell_x && room_cell_y == tmp->cell_y)
            {
                uni = false;
                break;
            }

        }

        if (uni)
        {
            break;
        }
        if (i == 999)
        {
            loop_complete = true;
        }

    }

    if (loop_complete)
        return false;
    else
        return true;
}

void MapGenerator::carveRooms(Map *m)
{
    RoomInfo *tmp;
    int rm_st_t_x;
    int rm_st_t_y;
    int rm_end_t_x;
    int rm_end_t_y;


    for (list<RoomInfo*>::iterator it = room_list.begin(); it != room_list.end(); it++)
    {
        //clog << "Beginning Carving process" << endl;
        tmp = *it;

        rm_st_t_x = (c_width*tmp->cell_x) + tmp->x;
        rm_end_t_x = (c_width*tmp->cell_x) + tmp->x + tmp->width;
        rm_st_t_y = (c_height*tmp->cell_y) + tmp->y;
        rm_end_t_y = (c_height*tmp->cell_y) + tmp->y + tmp->height;

        /*clog << "Room Cell: " << tmp->cell_x << " : " << tmp->cell_y << endl;
        clog << "Cell Beginning: " << tmp->cell_x * c_width << " : "  << tmp->cell_y * c_height << endl;
        clog << "Cell End: " << tmp->cell_x * c_width + c_width << " : " << tmp->cell_y * c_height + c_height << endl;
        clog << "Room Start: " << rm_st_t_x << " : " << rm_st_t_y << endl;
        clog << "Room End:   " << rm_end_t_x << " : " << rm_end_t_y << endl;*/

        for (int i = rm_st_t_x; i < rm_end_t_x; i++)
        {
            if (m->getTile(i, rm_st_t_y))
            {
                m->getTile(i, rm_st_t_y)->Type(1);
            }
            if (m->getTile(i, rm_end_t_y-1))
            {
                m->getTile(i, rm_end_t_y-1)->Type(1);
            }
            for (int ii = rm_st_t_y; ii < rm_end_t_y; ii++)
            {
                if (m->getTile(i, ii))
                {
                    if (i == rm_st_t_x || i == rm_end_t_x -1)
                    {
                        m->getTile(i, ii)->Type(1);
                    }
                    else
                    {
                        m->getTile(i, ii)->Id(22);
                    }

                }
            }
        }
    }
}

void MapGenerator::carvePaths(Map *m)
{
    PathInfo *tmp;
    Tile *t_tmp;

    for (list<PathInfo*>::iterator it = path_list.begin(); it != path_list.end(); it++)
    {
        clog << "Path : " << (*it)->a_x << " : " << (*it)->a_y << " to " << (*it)->b_x << " : " << (*it)->b_y << " and " << (*it)->c_x << " : " << (*it)->c_y << endl;
        if ((*it)->a_hor)
            clog << "Horizontal" << endl;
        tmp = *it;
        switch(tmp->path_t)
        {
            case P_STRAIGHT:
            {
                clog << "Straight Path" << endl;
                if (!carvePathSegment(m, tmp->a_x, tmp->a_y, tmp->b_x, tmp->b_y))
                {
                    carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->a_x, tmp->a_y);
                }
                else
                {
                    if (m->getTile(tmp->b_x, tmp->b_y))
                    {
                        m->getTile(tmp->b_x, tmp->b_y)->Type(0);
                        m->getTile(tmp->b_x, tmp->b_y)->Id(23);
                    }
                }
            }
            case P_ELBOW:
            {
                clog << "Elbow Path" << endl;
                if (tmp->a_hor)
                {
                    clog << "comparing: " << tmp->a_x << " : " << tmp->b_x << endl;
                    if (!carvePathSegment(m, tmp->a_x, tmp->a_y, tmp->b_x, tmp->a_y))
                    {
                        if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->b_x, tmp->a_y))
                        {
                            carvePathSegment(m, tmp->b_x, tmp->a_y, tmp->a_x, tmp->a_y);
                        }
                    }
                    else
                    {
                        if (!carvePathSegment(m, tmp->b_x, tmp->a_y, tmp->b_x, tmp->b_y))
                        {
                            carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->b_x, tmp->a_y);
                        }
                        else
                        {
                            if (m->getTile(tmp->b_x, tmp->b_y))
                            {
                                m->getTile(tmp->b_x, tmp->b_y)->Type(0);
                                m->getTile(tmp->b_x, tmp->b_y)->Id(23);
                            }
                        }
                    }
                }
                else
                {
                    if (!carvePathSegment(m, tmp->a_x, tmp->a_y, tmp->a_x, tmp->b_y))
                    {
                        if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->a_x, tmp->b_y))
                        {
                            carvePathSegment(m, tmp->a_x, tmp->b_y, tmp->a_x, tmp->a_y);
                        }
                    }
                    else
                    {
                        if (!carvePathSegment(m, tmp->a_x, tmp->b_y, tmp->b_x, tmp->b_y))
                        {
                            carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->a_x, tmp->b_y);
                        }
                        else
                        {
                            if (m->getTile(tmp->b_x, tmp->b_y))
                            {
                                m->getTile(tmp->b_x, tmp->b_y)->Type(0);
                                m->getTile(tmp->b_x, tmp->b_y)->Id(23);
                            }
                        }
                    }
                }

                break;
            }
            case P_SNAKE:
            {
                clog << "Snake Path" << endl;
                if (tmp->a_hor)
                {
                    if (!carvePathSegment(m, tmp->a_x, tmp->a_y, tmp->c_x, tmp->a_y))
                    {
                        if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->c_x, tmp->b_y))
                        {
                            if (carvePathSegment(m, tmp->c_x, tmp->b_y, tmp->c_x, tmp->a_y))
                            {
                                carvePathSegment(m, tmp->c_x, tmp->a_y, tmp->a_x, tmp->a_y);
                            }
                        }
                    }
                    else
                    {
                        if (tmp->a_y < tmp->b_y)
                        {
                            for (int i = tmp->c_x - 1; i <= tmp->c_x + 1; i++)
                            {
                                t_tmp = m->getTile(i, tmp->a_y-1);
                                if (t_tmp)
                                {
                                    t_tmp->Type(1);
                                }
                            }
                        }
                        else
                        {

                        }

                        if (tmp->a_x < tmp->c_x)
                        {
                            t_tmp = m->getTile(tmp->c_x+1, tmp->a_y);
                            if (t_tmp)
                            {
                                t_tmp->Type(1);
                            }
                        }
                        else
                        {
                            t_tmp = m->getTile(tmp->c_x-1, tmp->a_y);
                            if (t_tmp)
                            {
                                t_tmp->Type(1);
                            }
                        }


                        if (!carvePathSegment(m, tmp->c_x, tmp->a_y, tmp->c_x, tmp->b_y))
                        {
                            if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->c_x, tmp->b_y))
                            {
                                carvePathSegment(m, tmp->c_x, tmp->b_y, tmp->c_x, tmp->a_y);
                            }
                        }
                        else
                        {
                            if (!carvePathSegment(m, tmp->c_x, tmp->b_y, tmp->b_x, tmp->b_y))
                            {
                                carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->c_x, tmp->b_y);
                            }
                            else
                            {
                                if (m->getTile(tmp->b_x, tmp->b_y))
                                {
                                    m->getTile(tmp->b_x, tmp->b_y)->Type(0);
                                    m->getTile(tmp->b_x, tmp->b_y)->Id(23);
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (!carvePathSegment(m, tmp->a_x, tmp->a_y, tmp->a_x, tmp->c_y))
                    {
                        if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->b_x, tmp->c_y))
                        {
                            if (carvePathSegment(m, tmp->b_x, tmp->c_y, tmp->a_x, tmp->c_y))
                            {
                                carvePathSegment(m, tmp->a_x, tmp->c_y, tmp->a_x, tmp->a_y);
                            }
                        }
                    }
                    else
                    {
                        if (!carvePathSegment(m, tmp->a_x, tmp->c_y, tmp->b_x, tmp->c_y))
                        {
                            if (carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->b_x, tmp->c_y))
                            {
                                carvePathSegment(m, tmp->b_x, tmp->c_y, tmp->b_x, tmp->a_y);
                            }
                        }
                        else
                        {
                            if (!carvePathSegment(m, tmp->b_x, tmp->c_y, tmp->b_x, tmp->b_y))
                            {
                                carvePathSegment(m, tmp->b_x, tmp->b_y, tmp->b_x, tmp->c_y);
                            }
                            else
                            {
                                if (m->getTile(tmp->b_x, tmp->b_y))
                                {
                                    m->getTile(tmp->b_x, tmp->b_y)->Type(0);
                                    m->getTile(tmp->b_x, tmp->b_y)->Id(23);
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}


bool MapGenerator::carvePathSegment(Map *m, int st_x, int st_y, int end_x, int end_y)
{
    Tile *t_tmp;
    t_tmp = m->getTile(st_x, st_y);
    if (t_tmp)
    {
        t_tmp->Type(0);
    }
    if (st_x > end_x)
    {
        for (int i = st_x-1; i > end_x; i--)
        {
            t_tmp = m->getTile(i, st_y);
            if (t_tmp)
            {
                t_tmp->Id(23);
                if (t_tmp->Type() == 1)
                {
                    t_tmp->Type(0);
                    return false;
                }
                else
                {
                    if (m->getTile(i, st_y - 1))
                    {
                        m->getTile(i, st_y - 1)->Type(1);
                    }
                    if (m->getTile(i, st_y + 1))
                    {
                        m->getTile(i, st_y+1)->Type(1);
                    }
                }
            }
        }
    }
    else if (st_x < end_x)
    {
        for (int i = st_x+1; i < end_x; i++)
        {
            t_tmp = m->getTile(i, st_y);
            if (t_tmp)
            {
                t_tmp->Id(23);
                if (t_tmp->Type() == 1)
                {
                    t_tmp->Type(0);
                    return false;
                }
                else
                {
                    if (m->getTile(i, st_y - 1))
                    {
                        m->getTile(i, st_y - 1)->Type(1);
                    }
                    if (m->getTile(i, st_y + 1))
                    {
                        m->getTile(i, st_y+1)->Type(1);
                    }
                }
            }
        }
    }
    else
    {
        if (st_y > end_y)
        {
            for (int i = st_y-1; i > end_y; i--)
            {
                t_tmp = m->getTile(st_x, i);
                if (t_tmp)
                {
                    t_tmp->Id(23);
                    if (t_tmp->Type() == 1)
                    {
                        t_tmp->Type(0);
                        return false;
                    }
                    else
                    {
                        if (m->getTile(st_x - 1, i))
                        {
                            m->getTile(st_x - 1, i)->Type(1);
                        }
                        if (m->getTile(st_x + 1, i))
                        {
                            m->getTile(st_x + 1, i)->Type(1);
                        }
                    }
                }
            }
        }
        else if (st_y < end_y)
        {
            for (int i = st_y+1; i < end_y; i++)
            {
                t_tmp = m->getTile(st_x, i);
                if (t_tmp)
                {
                    t_tmp->Id(23);
                    if (t_tmp->Type() == 1)
                    {
                        t_tmp->Type(0);
                        return false;
                    }
                    else
                    {
                        if (m->getTile(st_x - 1, i))
                        {
                            m->getTile(st_x - 1, i)->Type(1);
                        }
                        if (m->getTile(st_x + 1, i))
                        {
                            m->getTile(st_x+1, i)->Type(1);
                        }
                    }
                }
            }
        }
    }

    return true;
}

int MapGenerator::randInt(int m, int mx)
{
    if (mx < m)
    {
        int tmp = mx;
        mx = m;
        m = tmp;
    }

    return (rand() % (mx - m)) + m;
}
