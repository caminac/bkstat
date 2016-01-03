#ifndef IFSTORE_H
#define IFSTORE_H

#include "types.h"

#define TECH_FAUL (-1)
#define ANTISP_FAUL (-2)

#define F_RECV    (0)
#define F_DONE    (1)

typedef struct Y_FaulDetails{
  int no_ft, ft_1, ft_2, ft_3;
} T_FaulDetails;

typedef struct Y_ActionDesc{
  int item,
      player_index,
      coord_x,
      coord_y,
      quarter,
      min, sec, param;
} T_ActionDesc;

class ifViewer;
class QString;
class QFile;
class playstat;

namespace Ui {
    class ifStore;
}

class players;

class ifStore
{
public:
    enum{
        t1_ok = 0,
        t1_ko,
        t2_ok,
        t2_ko,
        t3_ok,
        t3_ko,
        rb_def,
        rb_atk,
        fl_recv,
        fl_done,    // 9
        stl_done,
        stl_recv,
        assist,
        blocks_done,
        blocks_recv,
        subst_out,
        subst_in,
        starting_five,
        actual_quarter,
        label_t1,
        label_t2,
        label_t3,
        points,
        val,
        start_substitute,
        last_button,        // last tracked event
        oth_t1,             // 26
        oth_t2,
        oth_t3,
        my_fauls,
        oth_fauls,
        oth_points,
        my_timeout,
        oth_timeout,
    };

    virtual void init_T_ActionDesc( T_ActionDesc &x) = 0;
    virtual void SetViewer(ifViewer *v) = 0;
    virtual void Reset() = 0;
    virtual void ResetQuarterFauls() = 0;
    virtual void AddScore(int item, int player_index = 0, int p1=0, int p2=0, int q=0) = 0;
    virtual int  GetScore(int item) = 0;
    virtual int  GetScore(int item, int player_index) = 0;
    virtual int  GetLastAction() = 0;
    virtual QString get_perc( int item1, int item2, int player_index ) = 0;
    virtual T_ActionDesc GetActionForUndo() = 0;
    virtual T_ActionDesc Undo() = 0;
    virtual void store_match(QFile &data) = 0;
    virtual void store_pbp(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry) = 0;
    virtual void store_pbp_in_html(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry, QString charset) = 0;
    virtual void store_stat(QFile &data, std::vector<T_PlayerData> *players_registry) = 0;
    virtual void store_html(QFile &data, players *p, std::vector<T_PlayerData> *players_registry, QString charset) = 0;
    virtual void load_match(QFile &data, playstat *scoreboard) = 0;
    virtual int  get_current_gap() = 0;
};

#endif // IFSTORE_H
