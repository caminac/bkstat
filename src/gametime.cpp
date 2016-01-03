#include "gametime.h"

GameTime::GameTime(int m, int s)
{
  m_min = m;
  m_sec = s;
}

GameTime & GameTime::operator+(const GameTime added)
{
    int sum = 0, final_sec = 0, reminder = 0;
    sum = this->m_sec + added.m_sec;
    final_sec = (sum % 60);
    this->m_sec = final_sec;
    if( sum >= 60 ){ reminder = 1;}
    this->m_min += added.m_min + reminder;
    return *this;
}

GameTime & GameTime::operator-(const GameTime subtractor)
{
    bool can_do = true;
    if( this->m_min > subtractor.m_min ){
    }else{
        if( this->m_min > subtractor.m_min ){
        }else if( this->m_min == subtractor.m_min && this->m_sec > subtractor.m_sec ){
        }else{
          can_do = false;
        }
    }
    if( can_do ){
      if( subtractor.m_sec > this->m_sec ){
        this->m_min -= 1;
        this->m_sec += 60;
      }
      this->m_min -= subtractor.m_min;
      this->m_sec -= subtractor.m_sec;
    }else{
      this->m_min = 0;
      this->m_sec = 0; // ???
    }
    return *this;
}
