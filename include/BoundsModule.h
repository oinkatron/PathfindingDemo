#ifndef BOUNDSMODULE_H
#define BOUNDSMODULE_H

#include "Module.h"

class BoundsModule : public Module
{
    public:
        BoundsModule();
        BoundsModule(int s_w, int s_h, int o_x, int o_y) : width(s_w), height(s_h), offset_x(o_x), offset_y(o_y) { }
        virtual ~BoundsModule();

        int Width() { return width; }
        int Height() { return height; }

        int OffsetX() { return offset_x; }
        int OffsetY() { return offset_y; }

        void Width(int val) { width = val; }
        void Height(int val) { height = val; }

        void OffsetX(int val) { offset_x = val; }
        void OffsetY(int val) { offset_y = val; }


    protected:
    private:
        int width;
        int height;

        int offset_x;
        int offset_y;
};

#endif // BOUNDSMODULE_H
