#ifndef CAMERA_H
#define CAMERA_H



class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void setOffset(int xx, int yy) { offset_x = xx; offset_y = yy; }
        void setXOffset(int val) { offset_x = val; }
        void setYOffset(int val) { offset_y = val; }

        int getXOffset() { return offset_x; }
        int getYOffset() { return offset_y; }

        void setSize(int w, int h) { view_width = w; view_height = h; }
        void setWidth(int val) { view_width = val; }
        void setHeight(int val) { view_height = val; }

        int getWidth () { return view_width; }
        int getHeight () { return view_height; }

        void setLimit(int x, int y) { limit_x = x; limit_y = y; }
        void setXLimit(int x) { limit_x = x; }
        void setYLimit(int y) { limit_y = y; }

    protected:
    private:
        int offset_x;
        int offset_y;

        int view_width;
        int view_height;

        int limit_x;
        int limit_y;
};

#endif // CAMERA_H
