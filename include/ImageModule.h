#ifndef IMAGEMODULE_H
#define IMAGEMODULE_H

#include <string>

#include "Module.h"
#include "Image.h"


using namespace std;

class ImageModule : public Module
{
    public:
        ImageModule() { img_data = NULL; }
        ImageModule(Image *val) { img_data = val; }
        ImageModule(string filename) { img_data = Image::getImage(filename); }
        virtual ~ImageModule();

        void setImage(string filename) { img_data = Image::getImage(filename); }
        void setImage(Image* val) { img_data = val; }
        Image* getImage() { return img_data; }
    protected:
    private:
        Image* img_data;
};

#endif // IMAGEMODULE_H
