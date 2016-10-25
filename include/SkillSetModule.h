#ifndef SKILLSETMODULE_H
#define SKILLSETMODULE_H

#include "Module.h"
#include "Skill.h"
#include <SDL/SDL.h>

class SkillSetModule : public Module
{
    public:
        SkillSetModule();
        virtual ~SkillSetModule();

        void mapSkill(int i, SDLKey mk, Skill *sk);

        int isMapped(SDLKey k);

        Skill* getSkill(int i) { if (i >= 0 && i < 5) return mapped_skills[i]; else return NULL; }
        SDLKey getKey(int i) { if (i >= 0 && i < 5) return mapped_keys[i]; else return (SDLKey)-1; }

    protected:
    private:
        SDLKey mapped_keys[5];
        Skill *mapped_skills[5];

};

#endif // SKILLSETMODULE_H
