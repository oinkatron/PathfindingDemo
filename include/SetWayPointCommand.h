#ifndef SETWAYPOINTCOMMAND_H
#define SETWAYPOINTCOMMAND_H

#include "OMath.h"
#include "GameCommand.h"


class SetWayPointCommand : public GameCommand
{
    public:
        SetWayPointCommand();
        virtual ~SetWayPointCommand();

        void onAction();

        void setCoord(int xx, int yy) { tar_x = xx; tar_y = yy; }
        void waypointPointer(Vector2D *val) { wayp = val; }
        Vector2D* waypointPointer() { return wayp; }
    protected:
    private:
        int tar_x, tar_y;
        Vector2D *wayp;

};

#endif // SETWAYPOINTCOMMAND_H
