#ifndef VELOCITYMODULE_H
#define VELOCITYMODULE_H

#include "Module.h"
#include "OMath.h"


class VelocityModule : public Module
{
    public:
        VelocityModule();
        VelocityModule(float start_xv, float start_yv);
        VelocityModule(int start_ang, float start_spd);

        float Speed() { return speed; }
        void Speed(float val) { speed = val;  vel.setFromPolar(angle, speed); }
        void Accel(float val) { speed += val; vel.setFromPolar(angle, speed); }

        int Angle() { return angle; }
        void Angle(int val) { angle = val; if (angle <= 0) angle += 360; else if (angle > 360) angle -= 360; vel.setFromPolar(angle, speed); }
        void Turn(int val) { angle += val; if (angle <= 0) angle += 360; else if (angle > 360) angle -= 360; vel.setFromPolar(angle, speed); }

        void applyForce(Vector2D &f);
        void applyForce(int x, int y);

        float velX() { return vel.X(); }
        float velY() { return vel.Y(); }

        bool Travel() { return travel; }
        void Travel(bool val) { travel = val; }

        Vector2D& getVelocity() { return vel; }

        virtual ~VelocityModule();
    protected:
    private:
        float speed;
        int angle;
        Vector2D vel;
        bool travel = true;
};

#endif // VELOCITYMODULE_H
