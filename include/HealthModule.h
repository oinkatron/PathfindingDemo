#ifndef HEALTHMODULE_H
#define HEALTHMODULE_H

#include "Module.h"


class HealthModule : public Module
{
    public:
        HealthModule();
        virtual ~HealthModule();

        void setMaxHP(int val) { max_hp = val; }
        void setCurHP(int val) { hp = val; }

        int getMaxHP() { return max_hp; }
        int getCurHP() { return hp; }

    protected:
    private:
        int hp;
        int max_hp;
};

#endif // HEALTHMODULE_H
