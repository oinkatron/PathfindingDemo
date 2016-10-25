#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include "System.h"

#include "VelocityModule.h"
#include "SpriteModule.h"


class SpriteSystem : public System
{
    public:
        SpriteSystem();
        virtual ~SpriteSystem();

        void Update(Object *ob, long d_t);
    protected:
    private:
};

#endif // SPRITESYSTEM_H
