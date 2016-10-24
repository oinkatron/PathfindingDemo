#ifndef SCENE_H
#define SCENE_H

#include <string>

using namespace std;


class Scene
{
    public:
        Scene();
        virtual ~Scene();
    protected:
    private:
        string name;
        int u_id;

        /* Has to hold all data about the current scene
           whether it is a start screen or game world
           all of them are scenes
        */

};

#endif // SCENE_H
