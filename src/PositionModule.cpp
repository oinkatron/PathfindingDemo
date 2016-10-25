#include "../include/PositionModule.h"

PositionModule::PositionModule()
{
    position.X(0.f);
    position.Y(0.f);
}

PositionModule::~PositionModule()
{
    //dtor
}

PositionModule::PositionModule(float s_x, float s_y)
{
    position.X(s_x);
    position.Y(s_y);
}

float PositionModule::distanceToPoint(int x, int y)
{
    float dist_x = (float)x - position.X();
    float dist_y = (float)y - position.Y();

    return sqrtf((dist_x*dist_x) + (dist_y * dist_y));
}
