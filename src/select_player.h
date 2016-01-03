#ifndef SELECT_PLAYER_H
#define SELECT_PLAYER_H

#include <QDialog>
#include "types.h"

namespace Ui {
    class select_player;
}

class select_player : public QDialog
{
    Q_OBJECT

public:
    explicit select_player(QWidget *parent = 0);
    ~select_player();
    void set_numbers(int idx[], int numbers[]);

private slots:
    void on_bt_pl1_clicked();

    void on_bt_pl3_clicked();

    void on_bt_pl2_clicked();

    void on_bt_pl4_clicked();

    void on_bt_pl5_clicked();

private:
    Ui::select_player *ui;
    int indexes[N_FIELD];
    int m_sel;
};

#endif // SELECT_PLAYER_H
