#ifndef PLAYSTAT_H
#define PLAYSTAT_H

#include <QDialog>
#include "ifViewer.h"
//#include "select_player.h"
#include "types.h"
#include "faul_menu.h"
#include "oth_points_menu.h"

class ifStore;
class players;

namespace Ui {
    class playstat;
}

class playstat : public QDialog,ifViewer
{
    Q_OBJECT

public:
    explicit playstat(ifStore *st, T_GameData *game_data, players *players, QWidget *parent = 0);
    ~playstat();

    QString Azione(T_ActionDesc &code);
    static const char *azioni[];
    void UpdateScoreboard(int item, int value, int player_index = -1);
    QString get_perc( int item1, int item2, int player_index = 0);
    int            ask_player(int auth_mode = true, QString msg = "", bool abort_allowed = false, bool team_allowed = false);
    T_GameData *m_game_data;
    void    startGame();
    bool is_game_ended();

private slots:
    void on_bt_change_clicked();

    void on_bt_t2_ok_clicked();

    void on_bt_t2_ko_clicked();

    void on_bt_t3_ok_clicked();

    void on_bt_t3_ko_clicked();

    void on_bt_reb_off_clicked();

    void on_bt_asst_clicked();

    void on_bt_steal_ok_clicked();

    void on_bt_steal_ko_clicked();

    void on_bt_blocks_clicked();

    void on_bt_reb_def_clicked();

    void on_bt_fauls_clicked();

    void on_bt_undo_clicked();

    void on_bt_blk_recv_clicked();

    void on_bt_q_indicator_clicked();

    void on_bt_oth_points_clicked();

private:
    Ui::playstat *ui;
    ifStore       *m_store;
    players       *m_players;
    faul_menu     *m_fauls;
    oth_points_menu *m_oth_pt;
};

#endif // PLAYSTAT_H
