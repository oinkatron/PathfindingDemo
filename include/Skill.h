#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <iostream>

#include "Object.h"
#include "Image.h"

using namespace std;

class Skill
{
    public:
        Skill();
        virtual ~Skill();

        void onActivate();
        void onHit();

        void setIcon(Image *val) { icon = val; }
        void setIcon(string val) { icon = Image::getImage(val); }
        Image* getIcon() { return icon; }

        void setParent(Object *val) { parent = val; }
        Object* getParent() { return parent; }

    protected:
        Object* parent;
        Image *icon;
    private:


};

#endif // SKILL_H
