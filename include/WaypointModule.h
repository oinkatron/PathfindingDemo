#ifndef WAYPOINTMODULE_H
#define WAYPOINTMODULE_H

#include <vector>

#include "Module.h"
#include "OMath.h"

using namespace std;

class WaypointModule : public Module
{
    public:
        WaypointModule();
        virtual ~WaypointModule();

        void pathTo(float xx, float yy) { tail.X(xx); tail.Y(yy); build_path = true;}
        Vector2D getTail() { return tail; }

        bool buildPath() { return build_path; }
        void buildPath(bool val) { build_path = val; }

        vector<Vector2D> *getPath() { return &node_list; }
        Vector2D getNextNode() { if (node_list.size() > 0) { return node_list[node_list.size()-1]; } else { return Vector2D(-1, -1); } }
        void popNode() { node_list.erase(node_list.begin() + node_list.size()-1); }

    protected:
    private:
        vector<Vector2D> node_list;
        Vector2D tail;
        bool build_path;
};

#endif // WAYPOINTMODULE_H
