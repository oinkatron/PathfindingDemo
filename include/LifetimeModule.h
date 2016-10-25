#ifndef LIFETIMEMODULE_H
#define LIFETIMEMODULE_H

#include "Module.h"
#include <SDL/SDL.h>


class LifetimeModule : public Module
{
    public:
        LifetimeModule() { start_time = SDL_GetTicks(); life_span = -1; }
        LifetimeModule(int val) { start_time = SDL_GetTicks(); life_span = val; }
        virtual ~LifetimeModule();

        void setLifeSpan(int val);
        int getLifeSpan() { return life_span; }

        void resetLife() { start_time = SDL_GetTicks(); }
        int getStartTime() { return start_time; }

    protected:
    private:
        int life_span;
        int start_time;

};

#endif // LIFETIMEMODULE_H
