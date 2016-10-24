#include "../include/SkillSetModule.h"

SkillSetModule::SkillSetModule()
{
    for (int i = 0; i < 5; i++)
    {
        mapped_keys[i] = (SDLKey) -1;
        mapped_skills[i] = NULL;
    }
}

SkillSetModule::~SkillSetModule()
{
    //dtor
}

void SkillSetModule::mapSkill(int i, SDLKey m_k, Skill *sk)
{
    if (i >= 0 && i < 5)
    {
        mapped_keys[i] = m_k;
        mapped_skills[i] = sk;
    }
}

int SkillSetModule::isMapped(SDLKey k)
{
    for (int i = 0; i < 5; i++)
    {
        if (mapped_keys[i] == k)
        {
            return i;
        }
    }

    return -1;
}
