#ifndef DATAFILE_H
#define DATAFILE_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>

//#include "Log.h"
#include "string_func.h"

using namespace std;

struct Member
{
    string name;
    string value;
    //bool is_string;
};

struct Section
{
    string name;
    vector <Member*> members;
};

class DataFile
{
    public:
        DataFile();
        DataFile(string filename);

        virtual ~DataFile();

        bool Ok() { return ok; }
        bool loadFile(string filename);

        bool findMember(string member_name);

        int numSections() { return sections.size(); }
        string getSectionName(int val) { if (sections.size() > 0 && val >= 0 && val < sections.size()) return sections[val]->name; else return ""; }

        template<class T>
        bool getMember(string section, string name, T *var);
        template<class T>
        bool getMember(int section_num, string name, T *var);
    protected:
    private:
        vector<Section*> sections;
        string name;
        bool ok;
};


template <class T>
bool DataFile::getMember(string section, string name, T *var)
{
    stringstream ss;

    for (int i = 0; i < sections.size(); i++)
    {
        if (section == sections[i]->name)
        {
            for (int ii = 0; ii < sections[i]->members.size(); ii++)
            {
                if (name == sections[i]->members[ii]->name)
                {
                    ss << sections[i]->members[ii]->value;
                    if((ss >> *var))
                        return true;
                    else
                        return false;
                }
            }
        }
    }

    return false;
}

template <class T>
bool DataFile::getMember(int section_num, string name, T* var)
{
    if (section_num < 0 || section_num >= sections.size())
    {
        return false;
    }

    stringstream ss;

    for (int i = 0; i < sections[section_num]->members.size(); i++)
    {
        if (name == sections[section_num]->members[i]->name)
        {
            ss << sections[section_num]->members[i]->value;
            if ((ss >> *var))
                return true;
            else
                return false;
        }
    }

    return false;
}

#endif // DATAFILE_H
