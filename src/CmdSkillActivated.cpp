#include "../include/CmdSkillActivated.h"

CmdSkillActivated::CmdSkillActivated()
{
    sk_ac = NULL;
}

CmdSkillActivated::CmdSkillActivated(Skill *val)
{
    sk_ac = val;
}

CmdSkillActivated::~CmdSkillActivated()
{

}
