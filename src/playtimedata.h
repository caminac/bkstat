#ifndef PLAYTIMEDATA_H
#define PLAYTIMEDATA_H

#include "types.h"

class PlayTimeData
{
public:
    PlayTimeData();
    void init();
    void AddPlayedTime(int player, GameTime current, int current_gap);
    void SetEnterTime(int player, GameTime current, int current_gap);
    int GetPlayedTime(int player);
    GameTime GetFullPlayedTime(int player);
    QString  GetStringFullPlayedTime(GameTime total);
    int      GetImpact(int player);

    GameTime m_enter_time[MAX_PLAYERS];
    GameTime m_played_time[MAX_PLAYERS];
    int      m_enter_gap[MAX_PLAYERS];
    int      m_played_impact[MAX_PLAYERS];
};

#endif // PLAYTIMEDATA_H
