#include "../include/Object.h"

unsigned long Object::next_id = 0;

Object::Object()
{
    u_id = next_id++;
    name = "Object " + toString(u_id);
}

Object::~Object()
{
    //dtor
}
