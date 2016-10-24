#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>
#include <iostream>
#include <vector>

#include "string_func.h"

using namespace std;

class Image
{
    public:
        Image();

        virtual ~Image();

        int getW() { return raw->w; }
        int getH() { return raw->h; }

        static Image* getImage(string name);
        static Image* getImage(int uid);
        static bool loadImage(string filename);

        //Getters & Setters
        SDL_Surface *getRaw() { return raw; }
        void setRaw (SDL_Surface *val) { raw = val; }
        void setRaw(string filename);

        string getName() { return name; }
        void setName(string val) { name = val; }

        int getID() { return uid; }
        void setID(int val) { uid = val;}

        //Public vars
        static int num_images;
        static int next_id;
        static string path;
        static vector<Image*> image_bank;

    protected:
    private:
        SDL_Surface *raw;
        string name;
        int uid;
};

#endif // IMAGE_H
