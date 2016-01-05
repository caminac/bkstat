#ifndef SCORER_H
#define SCORER_H

#include <QCoreApplication>
#include <QTextStream>
#include "types.h"
#include "ifStore.h"
#include "playstat.h"
#include "playtimedata.h"

class players;

class scorer : public ifStore
{
    Q_DECLARE_TR_FUNCTIONS(scorer)

public:

    enum{
        _oth_t1,
        _oth_t2,
        _oth_t3,
        _my_fauls,
        _oth_fauls,
        _last_internal_item,
    };
    scorer();
    scorer(T_GameData *m_game_data, PlayTimeData *time_data);
    virtual void init_T_ActionDesc( T_ActionDesc &x);
    virtual ~scorer();
    virtual void SetViewer(ifViewer *v);
    virtual void Reset();
    virtual void ResetQuarterFauls();
    virtual T_ActionDesc Undo();
    virtual T_ActionDesc GetActionForUndo();
    virtual void AddScore(int item, int player_index = 0, int team_index = ifStore::team_A, int p1=0, int p2=0, int q=0);
    virtual int  GetScore(int item);
    virtual int  GetScore(int item, int player_index, int team_index = ifStore::team_A);
    virtual int  GetLastAction();
    virtual QString get_perc( int item1, int item2, int player_index, int team_index = ifStore::team_A);
    virtual QString get_perc( int val1, int tot );
    virtual bool    isInStarting5(int pl_index);
    virtual int  get_current_gap();

    virtual void SetScore(int item, int player_index, int team_index, int action_sign, int param = 0, int param2 = -1);
    virtual void store_match(QFile &data);
    virtual void store_pbp(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry);
    virtual void store_pbp_in_html(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry, QString charset);
    virtual void store_stat(QFile &data, std::vector<T_PlayerData> *players_registry);
    virtual void store_html(QFile &data, players *p, std::vector<T_PlayerData> *players_registry, QString charset);
    virtual void write_stylesheet(QTextStream &out);
    virtual void write_html_page_hdr(QTextStream &out,QString charset="");
    virtual void write_html_page_footer(QTextStream &out, QTextCodec* codec);
    virtual void write_html_table_header(QTextStream &out, QTextCodec* codec);
    virtual void write_html_legenda(QTextStream &out, QTextCodec* codec);
    virtual void write_html_row(QTextStream &out,QTextCodec* codec,QString stile, QString str, int n);
    virtual void load_match(QFile &data, playstat *scoreboard);

    void        set_players(players *p){ m_players = p; };
    ifViewer   *m_viewer;
    int         m_quarter;
    T_GameData *m_game;
    int         m_last_action;
    PlayTimeData *m_time_data;
    players     *m_players;
};

#endif // SCORER_H
