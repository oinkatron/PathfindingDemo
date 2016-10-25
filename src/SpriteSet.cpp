#include "../include/SpriteSet.h"

unsigned long SpriteSet::next_id = 0;
map<unsigned long, SpriteSet*> SpriteSet::sprite_set_bank;

string SpriteSet::dir = "res/sprites/";
string SpriteSet::ext = ".set";

SpriteSet::SpriteSet()
{
    u_id = next_id++;
    name = "SpriteSet " + toString(u_id);
    for (int i = 0; i < 4; i++)
    {
        walking[i] = NULL;
        standing[i] = NULL;
    }
}

SpriteSet::SpriteSet(Sprite *w[], Sprite *s[])
{
    u_id = next_id++;
    name = "SpriteSet " + toString(u_id);

    initSpriteSet(w, s);
}

SpriteSet::SpriteSet(string s_name, Sprite *w[], Sprite *s[])
{
    u_id = next_id++;
    name = s_name;
    initSpriteSet(w, s);
}

SpriteSet::SpriteSet(string w[], string s[])
{
    u_id = next_id++;
    name = "SpriteSet " + toString(u_id);

    initSpriteSet(w, s);
}

SpriteSet::SpriteSet(string s_name, string w[], string s[])
{
    u_id = next_id++;
    name = s_name;

    initSpriteSet(w, s);
}

SpriteSet::~SpriteSet()
{
    for (int i = 0; i < 4; i++)
    {
        walking[i] = NULL;
        standing[i] = NULL;
    }
}

bool SpriteSet::initSpriteSet(Sprite *w[], Sprite *s[])
{
    for (int i = 0; i < 4; i++)
    {
        if (w[i] != NULL)
        {
            walking[i] = w[i];
            for (int ii = i-1; ii >= 0; ii--) { walking[ii] = NULL; standing[ii] = NULL; }
            return false;
        }

        if (s[i] != NULL)
        {
            standing[i] = s[i];
            walking[i] = NULL;
            for (int ii = i-1; ii >= 0; ii--) { standing[ii] = NULL; walking[ii] = NULL; }
            return false;
        }

    }

    return true;
}

bool SpriteSet::initSpriteSet(string walk_names[], string s_names[])
{
    for (int i = 0; i < 4; i++)
    {
        clog << "Walking Sprite: " << walk_names[i] << endl;
        walking[i] = Sprite::getSprite(walk_names[i]);
        if (walking[i] == NULL)
        {
            for (int ii = i-1; ii >= 0; ii--)
            {
                walking[ii] = NULL;
                standing[ii] = NULL;
            }

            clog << "Error Fetching Sprite: " << walk_names[i] << ": Cannot initialise SpriteSet" << endl;
            return false;
        }

        clog << "Standing Sprite: " << s_names[i] << endl;
        standing[i] = Sprite::getSprite(s_names[i]);
        if (standing[i] == NULL)
        {
            walking[i] = NULL;
            for (int ii = i-1; ii >= 0; ii--)
            {
                walking[ii] = NULL;
                standing[ii] = NULL;
            }

            delete walking;
            delete standing;

            clog << "Error Fetching Sprite: " << s_names[i] << ": Cannot initialise SpriteSet" << endl;
            return false;
        }
    }

    return true;
}

bool SpriteSet::loadSpriteSet(string f_name)
{
    DataFile m_data;

    SpriteSet* new_set;

    string walk_names[4];
    string s_names[4];
    string set_name;

    if (!m_data.loadFile(dir + f_name + ext))
    {
        clog << "Cannot load File: " << f_name << ext << endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "name", &set_name))
    {
        clog << "Cannot find name: Setting default" << endl;
        //set_name = " ";
    }

    if (!m_data.getMember("SpriteSet", "walk_up", &walk_names[UP]))
    {
        clog << "Cannot find walk_up: Cannot load SpriteSet" <<endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "walk_down", &walk_names[DOWN]))
    {
        clog << "Cannot find walk_down: Cannot load SpriteSet" << endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "walk_left", &walk_names[LEFT]))
    {
        clog << "Cannot find walk_left: Cannot load SpriteSet" <<endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "walk_right", &walk_names[RIGHT]))
    {
        clog << "Cannot find walk_right: Cannot load SpriteSet" << endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "stand_up", &s_names[UP]))
    {
        clog << "Cannot find standing_up: Cannot load SpriteSet" <<endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "stand_down", &s_names[DOWN]))
    {
        clog << "Cannot find standing_down: Cannot load SpriteSet" << endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "stand_left", &s_names[LEFT]))
    {
        clog << "Cannot find standing_left: Cannot load SpriteSet" <<endl;
        return false;
    }

    if (!m_data.getMember("SpriteSet", "stand_right", &s_names[RIGHT]))
    {
        clog << "Cannot find standing_right: Cannot load SpriteSet" << endl;
        return false;
    }

    new_set = new SpriteSet();
    if (set_name != " ")
    {
        new_set->setName(set_name);
    }

    if (!new_set->initSpriteSet(walk_names, s_names))
    {
        delete new_set;
        clog << "Error Initialising SpriteSet: Cannot load" << endl;
        return false;
    }

    sprite_set_bank[new_set->getUID()] = new_set;
    return true;

}

SpriteSet* SpriteSet::getSpriteSet(string set_n)
{
    map<unsigned long, SpriteSet*>::iterator it;

    for (it = sprite_set_bank.begin(); it != sprite_set_bank.end(); it++)
    {
        if (it->second->getName() == set_n)
        {
            return it->second;
        }
    }

    clog << "Cannot find SpriteSet with name: " << set_n << endl;
    return NULL;
}

SpriteSet* SpriteSet::getSpriteSet(unsigned long u_id)
{
    map<unsigned long, SpriteSet*>::iterator it;

    it = sprite_set_bank.find(u_id);
    if (it != sprite_set_bank.end())
    {
        return it->second;
    }

    clog << "Cannot find SpriteSet with ID: " << u_id << endl;
    return NULL;
}
