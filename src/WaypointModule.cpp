#include "../include/WaypointModule.h"

WaypointModule::WaypointModule()
{
   tail.X(0);
   tail.Y(0);
   build_path = false;
}

WaypointModule::~WaypointModule()
{
    //dtor
}
