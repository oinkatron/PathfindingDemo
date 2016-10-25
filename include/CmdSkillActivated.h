#ifndef CMDSKILLACTIVATED_H
#define CMDSKILLACTIVATED_H

#include "GameCommand.h"
#include "Skill.h"


class CmdSkillActivated : public GameCommand
{
    public:
        CmdSkillActivated();
        CmdSkillActivated(Skill *val);
        virtual ~CmdSkillActivated();

        void setSkill(Skill *val) { sk_ac = val; }
        Skill *getSkill() { return sk_ac; }
    protected:
    private:
        Skill *sk_ac;
};

#endif // CMDSKILLACTIVATED_H
