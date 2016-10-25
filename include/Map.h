#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <fstream>

#include "Tilesheet.h"

#define TILE_SOLID 1
#define TILE_BLANK 0

using namespace std;

class Tile {
   public:
      Tile(int t, int i) { type = t; id = i; }
      Tile() {type = 0; id = 0; }

      int Type() { return type; }
      void Type(int val) { type = val; }

      int Id() { return id; }
      void Id(int val) { id = val; }
   private:
      int type; //what happens on collide
      int id; // the tile to be drawn
};

class Map
{
    public:
        static string dir;
        static string ext;

        Map();
        Map(string m_name, int mw, int mh, int tw, int th);
        virtual ~Map();

        Tilesheet* tSheet() { return sheet; }
        void tSheet(Tilesheet* val) { sheet = val; }

        int tilesWide() { return width;}
        int mapWidth() { return width*t_width; }
        int tileWidth() { return t_width; }

        int tilesTall() { return height; }
        int mapHeight() { return height*t_height; }
        int tileHeight() { return t_height; }

        Tile* getTile(int g_x, int g_y);
        Tile* getTileFromCoords(int xx, int yy);

        void setStartX(int val) { st_x = val; }
        int getStartX() { return st_x; }

        void setStartY(int val) { st_y = val; }
        int getStartY() { return st_y; }

        void initNewMap(string m_name, int mw, int mh, int tw, int th, int t_i=5);
        bool loadMap(string f_name);
        bool saveMap(string f_name);

    protected:
    private:
        string name;

        int width;
        int height;

        int t_width;
        int t_height;

        int st_x;
        int st_y;

        Tilesheet *sheet;

        vector<Tile*> tile_data;
};

#endif // MAP_H
