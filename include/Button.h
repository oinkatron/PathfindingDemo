#ifndef BUTTON_H
#define BUTTON_H

#include "Frame.h"
#include "Image.h"

class Button : public Frame
{
    public:
        Button() : Frame(-1) { }
        Button(string caption, string action, int des_w = -1, int des_h = -1);
        virtual ~Button();

        void render(Renderer *r);
        void render(Renderer *r, int off_x, int off_y);
    protected:
    private:
        Image *back_image,  *back_image_hover, *back_image_click;


};

#endif // BUTTON_H
