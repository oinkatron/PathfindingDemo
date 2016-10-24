#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "Map.h"

using namespace std;

class MapGenerator
{
    enum WallDir {
        WALL_TOP,
        WALL_BOTTOM,
        WALL_LEFT,
        WALL_RIGHT
    };
    struct RoomInfo {
        bool wall_info[4];
        int cell_x, cell_y;
        int x, y;
        int width, height;
    };

    enum PType {
        P_SNAKE,
        P_STRAIGHT,
        P_ELBOW
    };

    struct PathInfo {
        PType path_t;
        bool a_hor, b_hor;
        int a_x, a_y;
        int b_x, b_y;
        int c_x, c_y;
    };

    public:
        MapGenerator();
        virtual ~MapGenerator();

        Map* generateMap(unsigned int seed);
    protected:
    private:
        int randInt(int m, int mx);
        bool generateRoom();
        void generatePaths();
        bool getNextCell();

        void carveRooms(Map *m);
        void carvePaths(Map *m);
        bool carvePathSegment(Map *m, int st_x, int st_y, int end_x, int end_y);

        int r_cont;

        //map gen variables
        int used_tiles;
        int total_tiles;
        int map_size_gen;
        int cell_size_gen;

        int m_width, m_height;
        int t_width, t_height;

        int c_width, c_height;
        int c_wide, c_tall;
        int c_start_x, c_start_y;

        int room_cell_x, room_cell_y;
        int room_st_x, room_st_y;
        int room_width, room_height;

        list<RoomInfo*> room_list;
        list<PathInfo*> path_list;

};

#endif // MAPGENERATOR_H
