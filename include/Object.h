#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

#include "string_func.h"
#include "Module.h"

using namespace std;

class Object
{
    public:
        Object();
        virtual ~Object();
        static unsigned long next_id;

        unsigned long getUID() { return u_id; };

        string getName() { return name; }
        void setName(string val) { name = val; }

        vector<Module*> getModuleList() { return module_list; }
        void addMod(Module *new_mod) { module_list.push_back(new_mod); }

        template<class T>
        T* getModule();

        template<class T>
        bool removeModule();

    protected:
    private:
        unsigned long u_id;
        string name;
        vector<Module*> module_list;

};

template <class T>
T* Object::getModule()
{
    for (int i = 0; i < module_list.size(); i++)
    {
        if (dynamic_cast<T*>(module_list[i]) != 0)
        {
            return dynamic_cast<T*>(module_list[i]);
        }
    }

    return 0;
}

template <class T>
bool Object::removeModule()
{
    for (int i = 0; i < module_list.size(); i++)
    {
        if (dynamic_cast<T*>(module_list[i]) != 0)
        {
            delete module_list[i];
            module_list.erase(module_list.begin()+i);

            return true;
        }
    }

    return false;
}

#endif // OBJECT_H
