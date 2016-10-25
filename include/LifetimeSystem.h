#ifndef LIFETIMESYSTEM_H
#define LIFETIMESYSTEM_H

#include "System.h"

#include "LifetimeModule.h"
#include "CmdObjectLifeExpired.h"


class LifetimeSystem : public System
{
    public:
        LifetimeSystem();
        virtual ~LifetimeSystem();

        void Update(Object *ob, long d_t);
    protected:
    private:
};

#endif // LIFETIMESYSTEM_H
