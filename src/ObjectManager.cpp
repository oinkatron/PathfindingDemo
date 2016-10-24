#include "../include/ObjectManager.h"

ObjectManager::ObjectManager()
{
    //ctor
}

ObjectManager::~ObjectManager()
{
    //dtor
}

Object* ObjectManager::createNewObject()
{
    active_objects.push_back(new Object());
    return active_objects[active_objects.size()-1];
}

Object* ObjectManager::getObject(unsigned long u_id)
{
    for (int i = 0; i < active_objects.size(); i++)
    {
        if (u_id == active_objects[i]->getUID())
        {
            return active_objects[i];
        }
    }

    return NULL;
}

Object* ObjectManager::getObject(string name)
{
    for (int i = 0; i < active_objects.size(); i++)
    {
        if (name == active_objects[i]->getName())
        {
            return active_objects[i];
        }
    }

    return NULL;
}

bool ObjectManager::destroyObject(Object *obj)
{
    for (int i = 0; i < active_objects.size(); i++)
    {
        if (obj == active_objects[i])
        {
            to_delete.push_back(obj);
            del_list.push_back(i);
            return true;
        }
    }

    return false;
}

bool ObjectManager::destroyObject(unsigned long id)
{
    for (int i = 0; i < active_objects.size(); i++)
    {
        if (id == active_objects[i]->getUID())
        {
            to_delete.push_back(active_objects[i]);
            del_list.push_back(i);

            return true;
        }
    }

    return false;
}

void ObjectManager::addModule(unsigned long id, Module *new_mod)
{
    for (int i = 0; i < active_objects.size(); i++)
    {
        if (id == active_objects[i]->getUID())
        {
            active_objects[i]->addMod(new_mod);
            return;
        }
    }
}

void ObjectManager::clearObjects()
{
    for (int i = active_objects.size()-1; i >= 0; i--)
    {
        vector<Module*> mod_list = active_objects[i]->getModuleList();
        for (int ii = mod_list.size()-1; ii >= 0; ii--)
        {
            delete mod_list[ii];
        }

        delete active_objects[i];
    }

    active_objects.clear();
    to_delete.clear();
    del_list.clear();


}

void ObjectManager::sweep()
{
    for (int i = 0; i < to_delete.size(); i++)
    {
        clog << "Object: \"" << to_delete[i]->getName() << "\" flagged for deletion" << endl;
        vector<Module*> mod_list = to_delete[i]->getModuleList();
        for (int ii = mod_list.size()-1; ii >= 0; ii--)
        {
            delete mod_list[ii];
        }

        delete to_delete[i];
    }

    for (int i = 0; i < del_list.size(); i++)
    {
        active_objects.erase(active_objects.begin()+del_list[i]);
    }

    to_delete.clear();
    del_list.clear();
}
