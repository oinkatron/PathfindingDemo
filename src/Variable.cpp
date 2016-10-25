#include "../include/Variable.h"

Variable::Variable()
{
    type = T_INVALID;
}

Variable::Variable(int i)
{
    d.i = i;
    type = T_INT;
}

Variable::Variable(char c)
{
    d.c = c;
    type = T_CHAR;
}

Variable::Variable(string s)
{
    d.s = new string(s);
    type = T_STRING;
}

Variable::Variable(float f)
{
    d.f = f;
    type = T_FLOAT;
}

Variable::~Variable()
{
    if (type == T_STRING)
    {
        delete d.s;
    }
}
