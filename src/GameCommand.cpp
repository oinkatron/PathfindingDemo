#include "../include/GameCommand.h"

vector<GameCommand*> GameCommand::cmd_pmp;
size_t GameCommand::cur_cmd = 0;

GameCommand::GameCommand()
{
    cmd_pmp.push_back(this);
}

GameCommand::~GameCommand()
{

}

GameCommand* GameCommand::getNextCommand()
{
    if (cur_cmd >= cmd_pmp.size())
    {
        flushPump();
        return 0;
    }

    cur_cmd++;
    return cmd_pmp[cur_cmd-1];
}

void GameCommand::flushPump()
{
    cur_cmd = 0;
    for (int i = 0; i < cmd_pmp.size(); i++)
    {
        delete cmd_pmp[i];
    }

    cmd_pmp.clear();
}
