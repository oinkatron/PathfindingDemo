#include "../include/VelocityModule.h"

VelocityModule::VelocityModule()
{
    vel.X(0);
    vel.Y(0);
    speed = 0.f;
    angle = 0;
}

VelocityModule::~VelocityModule()
{
    //dtor
}

VelocityModule::VelocityModule(float start_xv, float start_yv)
{
    vel.setComponents(start_xv, start_yv);
    speed = vel.Length();
    angle = vel.Angle();
}

VelocityModule::VelocityModule(int start_ang, float start_spd)
{
    speed = start_spd;
    angle = start_ang;
    vel.setFromPolar(angle, speed);
}

void VelocityModule::applyForce(Vector2D &f)
{
    Vector2D new_v = f + vel;
    angle = new_v.Angle();
    vel.setFromPolar(angle, speed);
}

void VelocityModule::applyForce(int x, int y)
{
    Vector2D new_v = Vector2D(x, y) + vel;
    angle = new_v.Angle();
    vel.setFromPolar(angle, speed);
}
