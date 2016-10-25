#ifndef SPRITEMODULE_H
#define SPRITEMODULE_H

#include "Module.h"
#include "Sprite.h"
#include "SpriteSet.h"

class SpriteModule : public Module
{
    public:
        SpriteModule() { cur_sprite = NULL; spr_set = NULL; }
        SpriteModule(Sprite *val) { cur_sprite = val; spr_set = NULL; }
        SpriteModule(string val) { cur_sprite = Sprite::getSprite(val); spr_set = NULL; }
        SpriteModule(SpriteSet *val) { spr_set = val; cur_sprite = NULL; }
        SpriteModule(Sprite *val, SpriteSet *val2) { cur_sprite = val; spr_set = val2; }
        SpriteModule(string val, string val2) { cur_sprite = Sprite::getSprite(val); spr_set = SpriteSet::getSpriteSet(val2); }
        virtual ~SpriteModule();

        Sprite* getSprite() { return cur_sprite; }
        void setSprite(Sprite *val) { if (cur_sprite) { if (cur_sprite->getName() == val->getName()) { return; } else { delete cur_sprite; } } cur_sprite = new Sprite(*val); }
        void setSprite(string val) { if (cur_sprite) { if (cur_sprite->getName() == val) { return; } else { delete cur_sprite; } } cur_sprite = Sprite::getSprite(val); }

        SpriteSet *getSpriteSet() { return spr_set; }
        void setSpriteSet(SpriteSet * val) { spr_set = val; }
        void setSpriteSet(string val) { spr_set = SpriteSet::getSpriteSet(val); }
        void setSpriteSet(unsigned long u_id) { spr_set = SpriteSet::getSpriteSet(u_id); }

    protected:
    private:
        Sprite *cur_sprite;
        SpriteSet *spr_set;
};

#endif // SPRITEMODULE_H
