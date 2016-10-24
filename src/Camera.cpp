#include "../include/Camera.h"

Camera::Camera()
{
    offset_x = 0;
    offset_y = 0;
    view_width = 0;
    view_height = 0;

    limit_x = 0;
    limit_y = 0;
}

Camera::~Camera()
{
    //dtor
}
