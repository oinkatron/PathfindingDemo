#ifndef FONT_H
#define FONT_H

#include <string>
#include <vector>
#include <iostream>
#include <SDL/SDL_ttf.h>

using namespace std;

class Font
{
    public:
        Font();
        Font(string fname, int size);
        virtual ~Font();

        static vector<Font*> font_bank;

        static bool loadFont(string filename, int size);
        static Font* getFont(string font_name, int size);

        static string font_path;

        //Getters and Setters
        string getName() { return filename; }
        int getSize() { return size; }
        TTF_Font *getRaw() { return fnt; }

    protected:
    private:
        string filename;

        TTF_Font *fnt;
        int size;

};

#endif // FONT_H
