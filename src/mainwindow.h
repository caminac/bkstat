#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QSettings>
#include "types.h"
#include "teamselection.h"
#include "newgame.h"
#include "playstat.h"
#include "players.h"
#include "scorer.h"
#include "statistics.h"
#include "dlg_options.h"
#include "playtimedata.h"

#define ST_INIT           0
#define ST_GAME_DEFINED   1
#define TEAM_LOADED       2
#define FIELD_OK          3
#define VIEW_ONLY         4

#define HR_PBP            1
#define HR_STAT           2
#define HR_HTML           3
#define HR_NUMERIC        4

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QSettings *settings, QString l = "en", QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);
    void warnForVersion();
    void store_game_data(QFile &data);
    bool load_game_data(QFile &data);

    void showExpanded();
    QRect         m_screen;
    T_GameData    m_game_data;
    teamselection *m_team;
    scorer        *m_sco;
    playstat      *m_play;
    players       *m_players;
    statistics    *m_statistic;
    dlg_options   *m_options;
    PlayTimeData  *m_time_data;
    std::vector<T_PlayerData> players_registry;
    int           m_field[N_FIELD];
    int           m_substitutes[MAX_SUBST];
    int           m_status;
    void          update_status();
    QString       m_current_language, m_loaded_file, m_export_dir;

    QString       GetActualCharset();
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_but_new_clicked();

    void on_but_view_clicked();

    void on_but_play_clicked();

    void on_bt_team_clicked();

    void on_bt_field_clicked();

    void on_bt_help_clicked();

    void on_bt_save_clicked();

    void on_bt_load_clicked();

    void on_but_export_clicked();

    void on_but_exp_stat_clicked();

    void on_but_del_files_clicked();

    void on_but_options_clicked();

    void on_but_del_dirs_clicked();

    void on_bt_exit_clicked();

private:
    Ui::MainWindow *ui;
    bool ask_exit_confirm();
    void export_hr_info( int type );
};

#endif // MAINWINDOW_H
