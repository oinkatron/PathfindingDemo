#include "../include/SetWayPointCommand.h"

SetWayPointCommand::SetWayPointCommand()
{
    tar_x = 0;
    tar_y = 0;
    wayp = 0;
}

SetWayPointCommand::~SetWayPointCommand()
{
    //dtor
}

void SetWayPointCommand::onAction()
{
    if (wayp)
    {
        wayp->X(tar_x);
        wayp->Y(tar_y);
    }
}
