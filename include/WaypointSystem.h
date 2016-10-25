#ifndef WAYPOINTSYSTEM_H
#define WAYPOINTSYSTEM_H

#include <iostream>
#include <vector>
#include <cmath>

#include "System.h"
#include "WaypointModule.h"
#include "PositionModule.h"
#include "VelocityModule.h"
#include "SpriteModule.h"
#include "MapModule.h"

using namespace std;

struct PathNode
{
    Vector2D map_pos;
    PathNode *parent;
    int g;
    int h;
    int f;
};


class WaypointSystem : public System
{
    public:
        WaypointSystem();
        virtual ~WaypointSystem();

        void Update(Object *ob, long d_t);
        void calculatePath(int end_x, int end_y, vector<Vector2D> *nodes, PositionModule *p, MapModule *mp);
        void calcFManHatten(PathNode *cur, PathNode *tail);
    protected:
    private:
};

#endif // WAYPOINTSYSTEM_H
