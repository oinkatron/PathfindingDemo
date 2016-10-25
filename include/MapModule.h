#ifndef MAPMODULE_H
#define MAPMODULE_H

#include "Module.h"
#include "Map.h";


class MapModule : public Module
{
    public:
        MapModule() { parent_map = NULL; }
        MapModule(Map* val) { parent_map = val; }
        virtual ~MapModule();

        Map* getMap() { return parent_map; }
        void setMap(Map* val) { parent_map = val; }

    protected:
    private:
        Map* parent_map;
};

#endif // MAPMODULE_H
