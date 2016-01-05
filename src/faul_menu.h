#ifndef FAUL_MENU_H
#define FAUL_MENU_H

#include <QDialog>
#include "ifStore.h"
#include "players.h"

#define POS_NOBODY (N_FIELD)
#define POS_COACH (N_FIELD+1)
#define POS_BENCH (N_FIELD+2)

typedef struct Y_FaulDetails{
  int my_data, foul_type, oth_data;
} T_FaulDetails;

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
    void set_players();
    void UpdateScoreboard(int item, int value, int player_index);
    void FaulDetected();
    int  get_TL(int f_type);
    void go_to_FT();
    int  m_ft_on_faul;
    bool faul_coach, faul_team;
    void faul_done(T_FaulDetails det);
    void faul_received(T_FaulDetails det);
    bool    get_faul_details(T_FaulDetails& det, int direction);
    QString get_faul_subject(T_FaulDetails det);
    bool    can_close_dialog();
    std::vector<int> m_list;
    // std::map<int,std::string> m_fauls_definitions;
    std::vector<std::string> m_fauls_definitions;
    enum{
        committed=11,
        received
    };

private slots:
    void on_bt_ft_ok_clicked();

    void on_bt_ft_ko_clicked();

    void on_bt_foul_recv_clicked();

    void on_bt_foul_done_clicked();

    void on_bt_close_clicked();

    void on_bt_oreb_clicked();

    void on_bt_change_on_faul_clicked();

    void on_cb_MyTeam_currentIndexChanged(int index);

    void on_cb_OthTeam_currentIndexChanged(int index);

    void on_cb_Faul_currentIndexChanged(const QString &arg1);

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
