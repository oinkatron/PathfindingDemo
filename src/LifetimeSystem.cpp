#include "../include/LifetimeSystem.h"

LifetimeSystem::LifetimeSystem()
{
    //ctor
}

LifetimeSystem::~LifetimeSystem()
{
    //dtor
}

void LifetimeSystem::Update(Object *ob, long d_t)
{
    LifetimeModule *lt_m = ob->getModule<LifetimeModule>();

    if (lt_m && lt_m->getLifeSpan() >= 0)
    {
        if (SDL_GetTicks() - lt_m->getStartTime() > lt_m->getLifeSpan())
        {
            CmdObjectLifeExpired* new_ev = new CmdObjectLifeExpired(ob);
        }
    }
}
