#ifndef STRING_FUNC_H
#define STRING_FUNC_H

#include <string>
#include <sstream>

using namespace std;

template <class C>
inline string toString(C val)
{
    stringstream ss;
    ss << val;
    return ss.str();
}

inline int numberOfOccur(string *str, string occur_str)
{
    int found, old_found;

    found = old_found = str->find(occur_str);
    if (found == string::npos)
        return 0;
    else
    {
        int count = 0;
        do
        {
            count++;
            old_found = found;
            found = str->find(occur_str, old_found+1);
        }while(found != string::npos);

        return count;
    }
}

inline void deleteAllOf(string& str, string del_str)
{
    int found;
    while((found = str.find(del_str)) != string::npos)
    {
        str.erase(found, del_str.size());
    }
}

inline void replaceAll(string& str, string old_str, string new_str)
{
    int found, old_found = 0;
    while((found = str.find(old_str, old_found)) != string::npos)
    {
        str.erase(found, old_str.size());
        str.insert(found, new_str);
        old_found = found;
    }
}

inline int howMany(string& str, string memb)
{
    int found, old_found = 0;
    int count = 0;

    while ((found = str.find(memb, old_found)) != string::npos)
    {
        count++;
        old_found = found+1;
    }

    return count;
}

inline string* split(string& str, string delim)
{
    string *split_str;

    int num_split = howMany(str, delim)+1;
    if (num_split == 0)
    {
        return NULL;
    }

    split_str = new string[num_split];

    int end, beginning = 0;
    int count = 0;
    while ((end = str.find(delim, beginning)) != string::npos)
    {
        split_str[count] = str.substr(beginning, end-beginning);
        beginning = end + delim.size();
        count++;
    }

    split_str[num_split-1] = str.substr(beginning, str.size());

    return split_str;
}
#endif
