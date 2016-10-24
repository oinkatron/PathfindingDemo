#include "../include/Map.h"

string Map::dir = "./res/maps/";
string Map::ext = ".omp";

Map::Map()
{
    name = "New Map";

    width = 0;
    height = 0;
    t_width = 0;
    t_height = 0;

    tile_data.clear();
}

Map::Map(string m_name, int mw, int mh, int tw, int th)
{
    name = m_name;

    width = mw;
    height = mh;
    t_width = tw;
    t_height = th;

    tile_data.reserve(width*height);
    Tile *tmp;
    for (int i = 0; i < width*height; i++)
    {
        tmp = new Tile(0,11);
        tile_data.push_back(tmp);
    }
}

void Map::initNewMap(string m_name, int mw, int mh, int tw, int th, int t_i)
{
    if (tile_data.size() > 0)
    {
        for (int i = 0; i < tile_data.size(); i++)
        {
            delete tile_data[i];
        }

        tile_data.clear();
    }

    name = m_name;

    width = mw;
    height = mh;
    t_width = tw;
    t_height = th;

    tile_data.reserve(width*height);
    Tile *tmp;
    for (int i = 0; i < width*height; i++)
    {
        tmp = new Tile(0, t_i);
        tile_data.push_back(tmp);
    }
}

bool Map::loadMap(string f_name)
{
    string t_file_n;
    ifstream mp_file;

    mp_file.open((dir + f_name + ext).c_str());

    if (!mp_file.is_open())
    {
        clog << "Cannot open map: " << f_name << ext << endl;
        return false;
    }

    mp_file >> name >> width >> height >> t_width >> t_height >> t_file_n;

    if (t_file_n != "none")
    {
        sheet = new Tilesheet();
        if (!sheet->loadTilesheet(t_file_n))
        {
            delete sheet;
            sheet = NULL;
        }
    }

    Tile *tmp;
    int t_id, t_type;
    for (int i = 0; i < width * height; i++)
    {
        mp_file >> t_id >> t_type;
        tmp = new Tile(t_type, t_id);
        tile_data.push_back(tmp);
    }

    mp_file.close();
    return true;
}

bool Map::saveMap(string f_name)
{
    ofstream mp_file;
    mp_file.open((dir + f_name + ext).c_str());

    if (!mp_file.is_open())
    {
        clog << "Cannot open map: " << f_name << ext << endl;
        return false;
    }

    //map_name map_width map_height t_width t_height
    //tilesheet_name
    mp_file << name << " " << width << " " << height << " " << t_width << " " << t_height << " ";
    if (sheet)
    {
        mp_file << sheet->Name() << " ";
    }
    else
    {
        mp_file << "none ";
    }

    for (int i = 0; i < tile_data.size(); i++)
    {
        mp_file << tile_data[i]->Id() << " " << tile_data[i]->Type() << " ";
    }

    mp_file.close();
    return true;
}

Tile *Map::getTile(int g_x, int g_y)
{
    if (g_x >= 0 && g_x < width && g_y >= 0 && g_y < height)
    {
        return tile_data[(g_y*width)+g_x];
    }

    return NULL;
}

Tile *Map::getTileFromCoords(int xx, int yy)
{
    int g_x = xx / t_width;
    int g_y = yy / t_height;

    if (g_x >= 0 && g_x < width && g_y >= 0 && g_y < height)
    {
        return tile_data[(g_y*width)+g_x];
    }

    return NULL;
}

Map::~Map()
{
    //dtor
}
