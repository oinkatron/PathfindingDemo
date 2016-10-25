#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL/SDL.h>
#include <iostream>

#include "Renderer.h"

#include "System.h"
#include "Camera.h"

#include "PositionModule.h"
#include "BoundsModule.h"
#include "ImageModule.h"
#include "SpriteModule.h"
#include "WaypointModule.h"

class RenderSystem : public System
{
    public:
        RenderSystem();
        virtual ~RenderSystem();

        void setRenderer(Renderer *v) { renderer = v; }
        Renderer* getRenderer() { return renderer; }

        void setCamera(Camera *c) { game_cam = c; }
        Camera* getCamera() { return game_cam; }

        void Update(Object *ob, long d_t);
    protected:
    private:
        Renderer *renderer;
        Camera *game_cam;
};

#endif // RENDERSYSTEM_H
