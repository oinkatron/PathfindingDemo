#ifndef METAINFOMODULE_H
#define METAINFOMODULE_H

#include <string>

#include "Module.h"

using namespace std;

class MetaInfoModule : public Module
{
    public:
        MetaInfoModule();
        virtual ~MetaInfoModule();
    protected:
    private:
        string name;
        string type_name;
};

#endif // METAINFOMODULE_H
