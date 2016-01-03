#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include "types.h"

namespace Ui {
    class newgame;
}

class newgame : public QDialog
{
    Q_OBJECT

public:
    explicit newgame(T_GameData *m_game, QWidget *parent = 0);
    ~newgame();

private slots:
    void on_bt_ok_clicked();

private:
    Ui::newgame *ui;
    T_GameData  *m_game;
    QString     mk_filename(QString team, QString date);
};

#endif // NEWGAME_H
