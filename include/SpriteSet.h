#ifndef SPRITESET_H
#define SPRITESET_H

#include <map>
#include <iostream>

#include "Sprite.h"
#include "DataFile.h"
#include "string_func.h"

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

class SpriteSet
{
    public:
        SpriteSet();
        SpriteSet(Sprite *w[], Sprite *s[]);
        SpriteSet(string s_name, Sprite *w[], Sprite* s[]);
        SpriteSet(string w[], string s[]);
        SpriteSet(string s_name, string w[], string s[]);
        virtual ~SpriteSet();

        static bool loadSpriteSet(string f_name);
        static void addSpriteSet(SpriteSet *s) { sprite_set_bank[s->getUID()] = s; }

        static SpriteSet *getSpriteSet(string set_n);
        static SpriteSet *getSpriteSet(unsigned long u_id);

        bool initSpriteSet(Sprite *w[], Sprite *s[]);
        bool initSpriteSet(string w[], string s[]);

        void setName(string val) { name = val; }
        string getName() { return name; }

        unsigned long getUID() { return u_id; }

        static void setDirectory(string val) { dir = val; }
        static string getDirectory() { return dir; }

        static void setExtension(string val) { ext = val; }
        static string getExtension() { return ext; }

        Sprite* getWalkingSprite(int direc) { if (direc >= 0 && direc < 4) return walking[direc]; else return NULL;}
        Sprite* getStandingSprite(int direc) { if (direc >= 0 && direc < 4)  return standing[direc]; else return NULL;}

    protected:
    private:
        static unsigned long next_id;
        static map<unsigned long, SpriteSet*> sprite_set_bank;

        static string dir;
        static string ext;

        int u_id;
        string name;

        Sprite *walking[4];
        Sprite *standing[4];

};

#endif // SPRITESET_H
