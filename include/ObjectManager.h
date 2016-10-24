#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <map>
#include <iostream>

#include "Object.h"
#include "Module.h"

class ObjectManager
{
    public:
        ObjectManager();
        virtual ~ObjectManager();

        Object* createNewObject();
        bool destroyObject(Object* obj);
        bool destroyObject(unsigned long id);

        void clearObjects();

        void addModule(unsigned long id, Module *new_mod);

        vector<Object*> getObjectList() { return active_objects; }

        Object* getObject(unsigned long u_id);
        Object* getObject(string name);

        void sweep();

    protected:
    private:
        vector<Object*> active_objects;
        vector<Object*> to_delete;
        vector<int> del_list;

};

#endif // OBJECTMANAGER_H
