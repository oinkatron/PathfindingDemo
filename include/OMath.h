#ifndef OMATH_H
#define OMATH_H

#include <cmath>
#include <iostream>

using namespace std;

class Vector2D
{
    public:
        Vector2D() { x = 0; y = 0; }
        Vector2D(float xx, float yy) { x = xx; y = yy; }
        virtual ~Vector2D() { }

        Vector2D& operator+=(const Vector2D& rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        }

        Vector2D& operator-=(const Vector2D& rhs)
        {
           x -= rhs.x;
           y -= rhs.y;

           return *this;
        }

        Vector2D& operator+(const Vector2D& rhs)
        {
            Vector2D new_v;
            new_v += *this;
            new_v += rhs;

            return new_v;
        }

        Vector2D& operator-(const Vector2D& rhs)
        {
            Vector2D new_v;
            new_v += *this;
            new_v -= rhs;

            return new_v;
        }

        float Length() { return sqrtf((x * x) + (y * y)); }
        float LengthSqr() { return (x * x) + (y * y); }
        float Angle()
        {
            float ang = atan2f(y,x) * 180.f / 3.14159265f;

            if (ang > 0.f && ang <= 180.f)
            {
                //ang = 360.f - ang;
            }
            else if (ang >= -180.f && ang <= 0.f)
            {
                ang = 360 - (ang * -1.f);
            }

            return ang;
        }

        void setFromPolar(int ang, float speed)
        {
            if (ang >= 360)
                ang -= 360;
            x = cosf((float)ang * 3.14159265f / 180.f)*speed;
            y = sinf((float)ang * 3.14159265f / 180.f)*speed;
        }

        void setComponents(float xx, float yy)
        {
            x = xx;
            y = yy;
        }



        float dot(Vector2D &other) { return (x * other.x) + (y * other.y); }
        Vector2D project(Vector2D &other) { Vector2D res; float scale = this->dot(other)/this->LengthSqr(); res.x = scale*other.x; res.y = scale*other.y; return res;}

        float X() { return x; }
        float Y() { return y; }
        void X(float val) { x = val; }
        void Y(float val) { y = val; }

    private:
        float x;
        float y;
};

#endif // OMATH_H
