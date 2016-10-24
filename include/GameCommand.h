#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include <vector>

using namespace std;

class GameCommand
{
    public:
        GameCommand();
        virtual ~GameCommand();

        static GameCommand* getNextCommand();

    protected:
    private:
        static void flushPump();

        static vector<GameCommand*> cmd_pmp;
        static size_t cur_cmd;

};

#endif // GAMECOMMAND_H
