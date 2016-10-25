#include "../include/SpriteSystem.h"

SpriteSystem::SpriteSystem()
{
    //ctor
}

SpriteSystem::~SpriteSystem()
{
    //dtor
}

void SpriteSystem::Update(Object *ob, long d_t)
{
    VelocityModule *v = ob->getModule<VelocityModule>();
    SpriteModule *sp_m = ob->getModule<SpriteModule>();

    if (v && sp_m && sp_m->getSpriteSet())
    {
        int dir = v->Angle();
        SpriteSet *sp_set = sp_m->getSpriteSet();
        Sprite *cur = sp_m->getSprite();

        if (v->Travel())
        {
            if (dir >= 45 && dir < 135 && cur->getName() != sp_set->getWalkingSprite(DOWN)->getName())
            {
                clog << "Setting Sprite to: "  << sp_set->getWalkingSprite(DOWN)->getName() << endl;
                sp_m->setSprite(sp_set->getWalkingSprite(DOWN));
                clog << "Is the error happening where i think????" << endl;
            }
            else if (dir >= 225 && dir < 315 && cur->getName() != sp_set->getWalkingSprite(UP)->getName())
            {
                sp_m->setSprite(sp_set->getWalkingSprite(UP));
            }
            else if (dir >= 135 && dir < 225 && cur->getName() != sp_set->getWalkingSprite(LEFT)->getName())
            {
                sp_m->setSprite(sp_set->getWalkingSprite(LEFT));
            }
            else if (dir >= 315 || dir < 45 && cur->getName() != sp_set->getWalkingSprite(RIGHT)->getName())
            {
                sp_m->setSprite(sp_set->getWalkingSprite(RIGHT));
            }
        }
        else
        {
            if (dir >= 45 && dir < 135 && cur->getName() != sp_set->getStandingSprite(DOWN)->getName())
            {
                sp_m->setSprite(sp_set->getStandingSprite(DOWN));
            }
            else if (dir >= 225 && dir < 315 && cur->getName() != sp_set->getStandingSprite(UP)->getName())
            {
                sp_m->setSprite(sp_set->getStandingSprite(UP));
            }
            else if (dir >= 135 && dir < 225 && cur->getName() != sp_set->getStandingSprite(LEFT)->getName())
            {
                sp_m->setSprite(sp_set->getStandingSprite(LEFT));
            }
            else if (dir >= 315 || dir < 45 && cur->getName() != sp_set->getStandingSprite(RIGHT)->getName())
            {
                sp_m->setSprite(sp_set->getStandingSprite(RIGHT));
            }
        }
    }
}
