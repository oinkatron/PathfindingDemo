#ifndef SYSTEM_H
#define SYSTEM_H

#include "Object.h"

class System
{
    public:
        System();
        virtual ~System();

        virtual void Update(Object *ob, long d_t) =0;
    protected:
    private:
};

#endif // SYSTEM_H
