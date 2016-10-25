#ifndef TILESHEET_H
#define TILESHEET_H

#include <string>
#include <iostream>

#include "Image.h"
#include "Datafile.h"

using namespace std;

class Tilesheet
{
    public:
        Tilesheet();
        virtual ~Tilesheet();

        static string dir;
        static string exten;

        Image *baseImage() { return base; }

        void createTilesheet(Image *img, int sh_w, int sh_h, int t_w, int t_h, int o_x=0, int o_y=0);
        bool loadTilesheet(string f_name);
        void saveTilesheet();
        void saveTilesheet(string f_name);

        int tileWidth() { return tile_width; }
        int tileHeight() { return tile_height; }

        string Name() { return name; }
        void Name(string val) { name = val; }

        SDL_Rect* getTile(int x, int y);
        SDL_Rect* getTile(int id);
    protected:
    private:
        Image *base;
        SDL_Rect clip;

        string name;

        int tile_width;
        int tile_height;

        int off_x;
        int off_y;

        int sheet_width;
        int sheet_height;

};

#endif // TILESHEET_H
