#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>

#include <string>
#include <vector>
#include <iostream>

#include "Image.h"
#include "DataFile.h"

using namespace std;

class Sprite
{
    public:
        Sprite();
        Sprite(const Sprite& source);
        virtual ~Sprite();

        //Operators
        Sprite & operator=(const Sprite &rhs);

        //Functions
        void init(Image *img, int num_frames, int start_x, int start_y, int frame_w, int frame_h);

        static int uid;

        static string dir;
        static string exten;
        static vector<Sprite*> sprite_bank;

        static Sprite* getSprite(string name);
        static bool loadSprite(string filename);

        //Getters and Setters
        void setSheet(Image *img);
        Image *getSheet() { return sheet; }

        void setFrame(int val) { if (val >= 0 && val < num_frames) cur_frame = val; }
        SDL_Rect* getFrame(int frame_num);
        SDL_Rect* getNextFrame();

        void setAnimationSpeed(int val) { anim_speed = val; }
        int getAnimationSpeed() { return anim_speed; }

        int getFrameNum() { return cur_frame; }
        int setFrameNum(int val);

        int getFrameWidth() { if (!frames) { return 0; } else { return frames[0].w; } }
        int getFrameHeight() { if (!frames) { return 0; } else { return frames[0].h; } }

        string getName() { return name; }
        void setName(string val) { name = val; }

    protected:
    private:
        Image *sheet;
        string name;
        int id;
        SDL_Rect *frames;

        int start_frame_x;
        int start_frame_y;

        bool horizontal;

        int num_frames;

        int cur_frame;

        int anim_speed; //Milliseconds a frame
        int start_ticks;
};

#endif // SPRITE_H
