#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include "gametime.h"

#define N_FIELD         5
#define MAX_SUBST       10
#define MAX_PLAYERS     (N_FIELD + MAX_SUBST)
#define MAX_QTR         5
#define MAX_LEN_NAMES  20
#define EXTRA_FOULS     3

typedef struct Y_GameData{
  bool    simplified;
  QString datestring, game_id, location;
  QString game_desc;
  int     other_team_points;
  QString filename;
  QString this_team;
  int     m_quarter_duration,
          m_overtime_duration,
          m_actual_quarter,
          faul_bonus;
  bool    game_started, game_end;
  GameTime m_banner_time;
  int      m_start5[N_FIELD];
} T_GameData;

typedef struct Y_PlayerData{
  QString name,
          birthdate,
          team_id,
          fed_id;
  int     number;
  GameTime m_enter_time;
  GameTime m_played_time;
} T_PlayerData;

typedef struct Y_PlaytimeData{
  GameTime m_enter_time;
  GameTime m_played_time;
} T_PlaytimeData;

typedef struct Y_player_info{
  int index, shirt, fauls;
} T_player_info;

#endif // TYPES_H
