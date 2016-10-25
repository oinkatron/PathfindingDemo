#include "../include/Sprite.h"

int Sprite::uid = 0;
vector<Sprite*> Sprite::sprite_bank;
string Sprite::dir = "res/sprites/";
string Sprite::exten = ".spr";


Sprite::Sprite()
{
    id = uid;
    uid++;

    start_ticks = SDL_GetTicks();
    anim_speed = 100;

    sprite_bank.push_back(this);

    num_frames = 0;
    cur_frame = 0;

    frames = NULL;

    sheet = NULL;
    name = " ";

    horizontal = true;
    start_frame_x = 0;
    start_frame_y = 0;
}

Sprite::Sprite(const Sprite& source)
{
    id = uid;
    uid++;
    name = source.name;

    start_ticks = SDL_GetTicks();
    anim_speed = source.anim_speed;

    num_frames = source.num_frames;
    cur_frame = source.cur_frame;

    sheet = source.sheet;

    horizontal = source.horizontal;
    start_frame_x = source.start_frame_x;
    start_frame_y = source.start_frame_y;

    frames = new SDL_Rect[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = source.frames[i];
    }
}

Sprite &Sprite::operator=(const Sprite &rhs)
{
    if (this == &rhs)
        return *this;

    if (frames)
        delete [] frames;

    start_ticks = SDL_GetTicks();
    anim_speed = rhs.anim_speed;

    num_frames = rhs.num_frames;
    cur_frame = rhs.cur_frame;

    sheet = rhs.sheet;

    horizontal = rhs.horizontal;
    start_frame_x = rhs.start_frame_x;
    start_frame_y = rhs.start_frame_y;

    frames = new SDL_Rect[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = rhs.frames[i];
    }

    return *this;
}

Sprite* Sprite::getSprite(string name)
{
    for (int i = 0; Sprite::sprite_bank.size(); i++)
    {
        if (Sprite::sprite_bank[i]->getName() == name)
        {
            Sprite *tmp;
            tmp = new Sprite(*Sprite::sprite_bank[i]);

            return tmp;
        }
    }

    return NULL;
}

bool Sprite::loadSprite(string filename)
{
    DataFile spr_data;

    //tmp sprite data
    string spr_name;
    string image_name;
    int num_fr;
    int s_x;
    int s_y;
    int s_w;
    int s_h;
    int anim_sp;

    if (!spr_data.loadFile(dir+filename+exten))
    {
        //Log::game_log->pushError("Unable to load Sprite: " + filename);
        return false;
    }

    for (int i = 0; i < spr_data.numSections(); i++)
    {
        if (spr_data.getSectionName(i) == "Sprite")
        {
            if (!spr_data.getMember(i, "image_name", &image_name))
            {
                //Log::game_log->pushError("No image specified...cannot load sprite");
                continue;
            }
            if (!spr_data.getMember(i, "name", &spr_name))
            {
                spr_name == "Sprite " + toString(uid);
            }

            if (!spr_data.getMember(i, "num_frames", &num_fr))
            {
                num_fr = 1;
            }

            if (!spr_data.getMember(i, "start_x", &s_x))
            {
                s_x = 0;
            }

            if (!spr_data.getMember(i, "start_y", &s_y))
            {
                s_y = 0;
            }

            if (!spr_data.getMember(i, "frame_width", &s_w))
            {
                s_w = 32;
            }

            if (!spr_data.getMember(i, "frame_height", &s_h))
            {
                s_h = 32;
            }

            if (!spr_data.getMember(i, "animation_speed", &anim_sp))
            {
                anim_sp = 100;
            }

            Sprite *new_spr = new Sprite();
            new_spr->init(Image::getImage(image_name), num_fr, s_x, s_y, s_w, s_h);

            new_spr->setName(spr_name);
            new_spr->setAnimationSpeed(anim_sp);

            sprite_bank.push_back(new_spr);
        }
    }
}

void Sprite::init(Image *img, int num_f, int start_x, int start_y, int frame_w, int frame_h)
{
    sheet = img;

    num_frames = num_f;
    frames = new SDL_Rect[num_f];

    start_frame_x = start_x;
    start_frame_y = start_y;

    for (int i = 0; i < num_f; i++)
    {
        frames[i].x = (start_x+i)*frame_w;
        frames[i].y = start_y*frame_h;
        frames[i].w = frame_w;
        frames[i].h = frame_h;
    }
}

SDL_Rect* Sprite::getFrame(int frame_num)
{
    if (frame_num >= 0 && frame_num < num_frames)
    {
        return &frames[frame_num];
    }
    else
    {
        return NULL;
    }
}

SDL_Rect* Sprite::getNextFrame()
{
    if (SDL_GetTicks() - start_ticks > anim_speed)
    {
        start_ticks = SDL_GetTicks();

        cur_frame++;
        if (cur_frame >= num_frames)
        {
            cur_frame = 0;
        }
    }

    return &frames[cur_frame];
}

Sprite::~Sprite()
{
    delete [] frames;
}
