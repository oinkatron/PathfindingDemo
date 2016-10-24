#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using namespace std;

class Variable
{
    enum DataType {
        T_INVALID,
        T_INT,
        T_FLOAT,
        T_STRING,
        T_CHAR
    };

    union Data {
        int i;
        float f;
        string *s;
        char c;
    };

    public:
        Variable();
        Variable(int i);
        Variable(char c);
        Variable(string s);
        Variable(float f);
        virtual ~Variable();

        DataType getType() { return type; }

        void setFloat(float f) { if (type == T_STRING) { delete d.s; } d.f = f; type = T_FLOAT; }
        void setInt(int i) { if (type == T_STRING) { delete d.s; } d.i = i; type = T_INT; }
        void setString(string s) { if (type == T_STRING) { delete d.s; } d.s = new string(s); type = T_STRING; }
        void setChar(char c) { if (type == T_STRING) { delete d.s; } d.c = c; type = T_CHAR; }

        template <class T>
        T getData()
        {
            if (type == T_INT)
            {
                return d.i;
            }
            else if (type == T_FLOAT)
            {
                return d.f;
            }
            else if (type == T_STRING)
            {
                return *d.s;
            }
            else if (type == T_CHAR)
            {
                return d.c;
            }
        }

    protected:
    private:
        DataType type;
        Data d;
};

#endif // VARIABLE_H
