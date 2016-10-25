#ifndef POSITIONMODULE_H
#define POSITIONMODULE_H

#include "Module.h"
#include "OMath.h"

class PositionModule : public Module
{
    public:
        PositionModule();
        PositionModule(float s_x, float s_y);
        virtual ~PositionModule();

        float X() { return position.X(); }
        float Y() { return position.Y(); }

        void stepX(float val) { position.X(position.X() + val); }
        void stepY(float val) { position.Y(position.Y() + val); }

        void X(float val) { position.X(val); }
        void Y(float val) { position.Y(val); }

        Vector2D &getPosition() { return position; }


        float distanceToPoint(int x, int y);
    protected:
    private:
        Vector2D position;
};

#endif // POSITIONMODULE_H
