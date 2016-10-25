#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <iostream>

#include "System.h"
#include "PositionModule.h"
#include "VelocityModule.h"
#include "MapModule.h"
#include "BoundsModule.h"


class MovementSystem : public System
{
    public:
        MovementSystem();
        virtual ~MovementSystem();

        void Update(Object *ob, long d_t);
    protected:
    private:
};

#endif // MOVEMENTSYSTEM_H
