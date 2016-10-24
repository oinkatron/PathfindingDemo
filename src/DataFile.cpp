#include "../include/DataFile.h"

DataFile::DataFile()
{
    name = "";
}

DataFile::DataFile(string filename)
{
    loadFile(filename);
}

bool DataFile::loadFile(string filename)
{
    string tmp_data;
    string::size_type i, found, found2;

    Section *tmp_section=NULL;
    Member *tmp_member=NULL;

    //Clear old members
    sections.clear();

    ifstream file(filename.c_str());

    if (!file.is_open())
    {
        return false;
    }

    name = filename;
    string *tmp1, *tmp2;

    while (!file.eof())
    {
        getline(file, tmp_data);

        if (!tmp_data.empty())
        {
            int i = tmp_data.find_first_not_of(" \t\n\v");
            if (i == string::npos || tmp_data[i] == '#')
                continue;

            if ((found = tmp_data.find("[")) != string::npos) //Finding new section
            {
                tmp_section = new Section;
                if ((found2 = tmp_data.find("]")) != string::npos)
                {
                    tmp_section->name = tmp_data.substr(found+1, found2-found-1);
                    sections.push_back(tmp_section);
                }
                else
                {
                    //Log::game_log->pushError("Malformed section declaration");

                    if (!tmp_section)
                        delete tmp_section;

                    tmp_section = sections[sections.size()-1];
                }


            }
            else if ((found = tmp_data.find("=")) != string::npos) //found a new member
            {
                tmp_member = new Member;

                tmp1 = split(tmp_data, "=");
                deleteAllOf(tmp1[0], " ");

                tmp_member->name = tmp1[0];

                if ((found = tmp1[1].find_first_not_of(" \n\v\t")) != string::npos)
                {
                    if (tmp1[1][found] == '"')
                    {
                        found2 = tmp1[1].find("\"", found+1);
                        if (found2 != string::npos)
                        {
                            tmp_member->value = tmp1[1].substr(found+1, found2-found-1);
                            tmp_section->members.push_back(tmp_member);

                            delete [] tmp1;
                        }
                        else
                        {
                            //Log::game_log->pushError("Malformed String!");

                            delete [] tmp1;
                            delete tmp_member;
                        }
                    }
                    else
                    {
                        tmp_member->value = tmp1[1].substr(found, tmp1[1].size()-found);
                        tmp_section->members.push_back(tmp_member);

                        delete [] tmp1;
                    }
                }
                else
                {
                    //Log::game_log->pushError("Malformed expression");

                    delete [] tmp1;
                    delete tmp_member;
                }
            }
            else
            {
                //Log::game_log->pushError("Unknown input: " + tmp_data);
            }
        }
    }
    file.close();

    return true;
}

DataFile::~DataFile()
{
   for (int i = 0; i < sections.size(); i++)
        sections[i]->members.clear();
   sections.clear();
}
