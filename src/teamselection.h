#ifndef TEAMSELECTION_H
#define TEAMSELECTION_H

#include <QDialog>
#include <QFile>
#include <QRegExp>
#include <map>
#include "types.h"

using namespace std;

#define MIN_PLAYER_NUMBER (0)
#define MAX_PLAYER_NUMBER (99)

namespace Ui {
    class teamselection;
}

class teamselection : public QDialog
{
    Q_OBJECT

public:
    explicit teamselection(std::vector<T_PlayerData> *players_registry, T_GameData *game_data, QWidget *parent = 0);
    ~teamselection();
    bool insert_player(int number, QString name);
    bool is_player_present(int number);
    void refresh_players();
    bool can_save();
    void store_team(QFile &data);
    enum{
        test_only,
        load
    };
    int load_team(QFile &data, int &players, QString &firstError, int mode = teamselection::load);
    virtual void showEvent ( QShowEvent * event );
    void warnForVersion();

private slots:
    void on_bt_add_clicked();

    void on_bt_delete_clicked();

    void on_bt_close_clicked();

    void on_bt_load_file_clicked();

    void on_bt_store_file_clicked();

    void on_bt_import_file_clicked();

private:
    bool               m_loaded;
    QRegExp           *m_separator;
    Ui::teamselection *ui;
    std::vector<T_PlayerData> *registry;
    //std::map<int,T_PlayerData> *registry;
    T_GameData *m_game_data;
};

#endif // TEAMSELECTION_H
