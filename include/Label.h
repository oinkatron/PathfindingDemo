#ifndef LABEL_H
#define LABEL_H

#include "Frame.h"


class Label : public Frame
{
    public:
        Label();
        virtual ~Label();

        void render(Renderer *r);
        void render(Renderer *r, int off_x, int off_y);
    protected:
    private:
};

#endif // LABEL_H
