#ifndef OTH_POINTS_MENU_H
#define OTH_POINTS_MENU_H

#include <QDialog>
#include "ifStore.h"
#include "players.h"

namespace Ui {
    class oth_points_menu;
}

class playstat;

class oth_points_menu : public QDialog
{
    Q_OBJECT

public:
    explicit oth_points_menu(playstat *stat, ifStore *store, T_GameData *game_data, QWidget *parent = 0);
    ~oth_points_menu();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::oth_points_menu *ui;
    T_GameData *m_game_data;
    ifStore       *m_store;
    playstat      *m_stat;
};

#endif // OTH_POINTS_MENU_H
