#include "../include/Font.h"

vector <Font*> Font::font_bank;
string Font::font_path = "res/fonts/";

Font::Font()
{
    filename = "";

    fnt = NULL;
    size = 0;
}

Font::Font(string fname, int s)
{
    filename = fname;
    size = s;

    fname = font_path + fname + ".ttf";
    fnt = TTF_OpenFont(fname.c_str(), s);
    if (fnt == NULL)
    {
        clog << "Could not load: " << fname << " : " << s << endl;
    }
    else
    {
        font_bank.push_back(this);
    }
}

Font* Font::getFont(string font_name, int size)
{
    for(int i = 0; i < font_bank.size(); i++)
    {
        if (font_name == font_bank[i]->getName() && size == font_bank[i]->getSize())
        {
            return font_bank[i];
        }
    }

    if (loadFont(font_name, size))
    {
        return font_bank[font_bank.size()-1];
    }

    clog << "Could not get font: " << font_name << endl;
    return NULL;
}

bool Font::loadFont(string filename, int size)
{
    Font *new_font;
    new_font = new Font(filename, size);

    if (new_font->getRaw() == NULL)
    {
        delete new_font;
        return false;
    }
    else
    {
        return true;
    }
}

Font::~Font()
{
    TTF_CloseFont(fnt);
    size = 0;
    filename = "";
}
