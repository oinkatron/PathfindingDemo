#include "../include/CmdObjectLifeExpired.h"

CmdObjectLifeExpired::CmdObjectLifeExpired()
{
    ob = NULL;
}

CmdObjectLifeExpired::CmdObjectLifeExpired(Object *o)
{
    ob = o;
}

CmdObjectLifeExpired::~CmdObjectLifeExpired()
{
    //dtor
}
