#include <QMessageBox.h>
#include "playtimedata.h"
#include "setup.h"

PlayTimeData::PlayTimeData()
{
    init();
}

void PlayTimeData::init()
{
    int i;
    for( i=0; i<MAX_PLAYERS; i++ ){
        m_enter_time[i] = GameTime();
        m_played_time[i] = GameTime();
        m_enter_gap[i] = 0;
        m_played_impact[i] = 0;
    }
}

void PlayTimeData::AddPlayedTime(int player, GameTime current, int current_gap)
{
#if defined(DEBUG_VERSION)
  QString msg;
  QMessageBox msgBox;
  msgBox.setStandardButtons(QMessageBox::Ok);
#endif
  GameTime part = GameTime(), total = GameTime();
  part = (m_enter_time[player] - current);
  total = part + m_played_time[player];
  m_played_time[player] = total;
  m_played_impact[player] += (current_gap - m_enter_gap[player]);
#if defined(DEBUG_VERSION)
  msg.sprintf("enter:%d; curr:%d; part:%d, total:%d",m_enter_time[player].m_min,current.m_min,part.m_min,total.m_min);
  msgBox.setText(msg);
  msgBox.exec();
#endif
}

void PlayTimeData::SetEnterTime(int player, GameTime current, int current_gap)
{
    m_enter_time[player] = current;
    m_enter_gap[player] = current_gap;
}

int PlayTimeData::GetPlayedTime(int player)
{
  int min = 0;
  GameTime total = m_played_time[player];
  if( total.m_sec >= 30 ){
    min = total.m_min + 1;
  }else{
    min = total.m_min;
  }
  return min;
}

GameTime PlayTimeData::GetFullPlayedTime(int player)
{
    return m_played_time[player];
}

int PlayTimeData::GetImpact(int player)
{
    int ret = 0;
    if( player >= 0 && player < MAX_PLAYERS ){
        ret = m_played_impact[player];
    }
    return ret;
}

QString PlayTimeData::GetStringFullPlayedTime(GameTime total)
{
    QString x;
    x.sprintf("%02d:%02d",total.m_min,total.m_sec);
    return x;
}
