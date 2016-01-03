#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include "types.h"
#include "playtimedata.h"

class ifStore;
class players;

namespace Ui {
    class statistics;
}

class statistics : public QDialog
{
    Q_OBJECT

public:
    explicit statistics(ifStore *st, T_GameData *game_data, players *pl, PlayTimeData *time_data, QWidget *parent = 0);
    ~statistics();
    void set_player(int pl);

private slots:
    void on_bt_close_clicked();

    void on_bt_prev_clicked();

    void on_bt_next_clicked();

private:
    Ui::statistics *ui;
    ifStore       *m_store;
    players       *m_players;
    int            m_player;
    T_GameData    *m_game_data;
    PlayTimeData  *m_time_data;
};

#endif // STATISTICS_H
