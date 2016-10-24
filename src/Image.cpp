#include "../include/Image.h"

int Image::next_id;
int Image::num_images;
string Image::path = "res/images/";
vector<Image*> Image::image_bank;

Image::Image()
{
    num_images++;
    next_id++;
    image_bank.push_back(this);

    uid = next_id;

    raw = NULL;
    name = "Image " + toString(uid);
}

bool Image::loadImage(string filename)
{
    Image *tmp_img = new Image;
    SDL_Surface *tmp, *opt;

    tmp_img->setName(filename);

    filename = path + filename;
    tmp = IMG_Load(filename.c_str());
    if (!tmp)
    {
        clog << "Image: " << filename << " not found" << endl;
        return false;
    }

    opt = SDL_DisplayFormat(tmp);
    if (!opt)
    {
        clog << "Could not optimize Image!" << endl;
        SDL_FreeSurface(tmp);

        return false;
    }

    SDL_SetColorKey(opt, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(opt->format, 255, 0, 255));
    tmp_img->setRaw(opt);

    SDL_FreeSurface(tmp);
    return true;
}

Image* Image::getImage(string name)
{
    for (int i = 0; i < image_bank.size(); i++)
    {
        if (name == image_bank[i]->getName())
        {
            return image_bank[i];
        }
    }

    if (loadImage(name))
    {
        return image_bank[image_bank.size()-1];
    }


    clog << "Could not find image: " << name;
    return NULL;
}

Image* Image::getImage(int uid)
{
    for (int i = 0; i < image_bank.size(); i++)
    {
        if (uid == image_bank[i]->getID())
        {
            return image_bank[i];
        }
    }

    return NULL;
}

Image::~Image()
{
    num_images--;

    if (raw)
        SDL_FreeSurface(raw);
    name = "";
}
