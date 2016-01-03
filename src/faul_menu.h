#ifndef FAUL_MENU_H
#define FAUL_MENU_H

#include <QDialog>
#include "ifStore.h"
#include "players.h"

class playstat;

namespace Ui {
    class faul_menu;
}

class faul_menu : public QDialog
{
    Q_OBJECT

public:
    explicit faul_menu(playstat *stat, ifStore *store, players *pl, int bonus = 5, QWidget *parent = 0);
    ~faul_menu();
    void set_player(int player);
    void UpdateScoreboard(int item, int value, int player_index);
    void FaulDetected();
    int  get_TL();
    void go_to_FT();
    int  m_ft_on_faul;
    bool faul_coach, faul_team;
    void faul_done(int type);
    void faul_received(int type);
    QString get_faul_subject();
    bool    can_close_dialog();

private slots:
    void on_bt_ft_ok_clicked();

    void on_bt_ft_ko_clicked();

    void on_bt_foul_recv_clicked();

    void on_bt_foul_done_clicked();

    void on_bt_close_clicked();

    void on_bt_oreb_clicked();

    void on_bt_change_on_faul_clicked();

    void on_rb_noft_clicked();

    void on_rb_1FT_clicked();

    void on_rb_2FT_clicked();

    void on_rb_3FT_clicked();

    void on_bt_tech_recv_clicked();

    void on_bt_tech_team_done_clicked();

    void on_bt_tech_coach_done_clicked();

private:
    Ui::faul_menu *ui;
    int      m_player, m_ft_author;
    playstat *m_stat;
    ifStore  *m_store;
    players  *m_players;
    int      ft_done;
    int      fauls_bonus;
};

#endif // FAUL_MENU_H
