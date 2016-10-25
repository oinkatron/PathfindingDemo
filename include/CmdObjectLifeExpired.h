#ifndef CMDOBJECTLIFEEXPIRED_H
#define CMDOBJECTLIFEEXPIRED_H

#include "GameCommand.h"
#include "Object.h"

class CmdObjectLifeExpired : public GameCommand
{
    public:
        CmdObjectLifeExpired();
        CmdObjectLifeExpired(Object *o);
        virtual ~CmdObjectLifeExpired();

        void setObject(Object *val) { ob = val; }
        Object* getObject() { return ob; }

    protected:
    private:
        Object *ob;
};

#endif // CMDOBJECTLIFEEXPIRED_H
