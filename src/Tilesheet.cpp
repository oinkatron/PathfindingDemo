#include "../include/Tilesheet.h"

string Tilesheet::dir = "res/tilesheets/";
string Tilesheet::exten = ".tsh";

Tilesheet::Tilesheet()
{
    base = NULL;
    clip = {0, 0, 0, 0};

    tile_width = 0;
    tile_height = 0;

    off_x = 0;
    off_y = 0;

    sheet_width = 0;
    sheet_height = 0;
}

void Tilesheet::createTilesheet(Image *img, int sh_w, int sh_h, int t_w, int t_h, int o_x, int o_y)
{
    base = img;
    sheet_width = sh_w;
    sheet_height = sh_h;

    tile_width = t_w;
    tile_height = t_h;

    off_x = o_x;
    off_y = o_y;
}

bool Tilesheet::loadTilesheet(string f_name)
{
    DataFile t_file;
    string img_name;

    cerr << dir << f_name << exten << endl;

    if (!t_file.loadFile(dir+f_name+exten))
    {
        cerr << "Cannot open tilesheet: " << f_name << exten << endl;
        return false;
    }

    name = f_name;
    if (!t_file.getMember("Tilesheet", "image_name", &img_name))
    {
        cerr << "Cannot load tilesheet: Image not defined!" << endl;
        return false;
    }

    base = Image::getImage(img_name);
    if (!base)
    {
        cerr << "Cannot load tilesheet: Cannot load image!" << endl;
        return false;;
    }

    if (!t_file.getMember("Tilesheet", "sheet_width", &sheet_width))
    {
        sheet_width = 1;
    }

    if (!t_file.getMember("Tilesheet", "sheet_height", &sheet_height))
    {
        sheet_height = 1;
    }

    if (!t_file.getMember("Tilesheet", "offset_x", &off_x))
    {
        off_x = 0;
    }

    if (!t_file.getMember("Tilesheet", "offset_y", &off_y))
    {
        off_y = 0;
    }

    if (!t_file.getMember("Tilesheet", "tile_width", &tile_width))
    {
        tile_width = (base->getRaw()->w - (off_x * (sheet_width-1))) / sheet_width;
    }

    if (!t_file.getMember("Tilesheet", "tile_height", &tile_height))
    {
        tile_height = (base->getRaw()->h - (off_y * (sheet_height-1))) / sheet_height;
    }

    clog << "Tilesheet dimens: " << base->getRaw()->w << " : " << base->getRaw()->h << " | " << tile_width << " : " << tile_height << endl;

    return true;
}

void Tilesheet::saveTilesheet()
{

}

SDL_Rect* Tilesheet::getTile(int x, int y)
{
    if (x >= 0 && x < sheet_width*tile_width && y >= 0 && y <= sheet_height*tile_height)
    {
        clip.w = tile_width;
        clip.h = tile_height;

        if (x == 0)
            clip.x = 0;
        else
            clip.x = (tile_width+off_x)*x;

        if (y == 0)
            clip.y = 0;
        else
            clip.y = (tile_height+off_y)*y;

        return &clip;
    }

    return NULL;
}

SDL_Rect* Tilesheet::getTile(int id)
{
    int x = id % sheet_width;
    int y = id / sheet_width;

    if (x >= 0 && x < sheet_width*tile_width && y >= 0 && y <= sheet_height*tile_height)
    {
        clip.w = tile_width;
        clip.h = tile_height;

        if (x == 0)
            clip.x = 0;
        else
            clip.x = (tile_width+off_x)*x;

        if (y == 0)
            clip.y = 0;
        else
            clip.y = (tile_height+off_y)*y;

        return &clip;
    }

    return NULL;
}

Tilesheet::~Tilesheet()
{
    //dtor
}
