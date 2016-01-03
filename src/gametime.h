#ifndef GAMETIME_H
#define GAMETIME_H

class GameTime
{
public:
    GameTime(const GameTime &c){m_min = c.m_min; m_sec = c.m_sec; };
    GameTime(int m=0, int s=0);
    int m_min;
    int m_sec;
    GameTime& operator+(const GameTime added);
    GameTime& operator-(const GameTime subtractor);
};

#endif // GAMETIME_H
