#ifndef PLAYERS_H
#define PLAYERS_H

#include <QDialog>
#include <map>
#include "gametime.h"
#include "types.h"
#include "playtimedata.h"

class ifStore;

namespace Ui {
    class players;
}


class players : public QDialog
{
    Q_OBJECT

public:
    explicit players(ifStore *st, std::vector<T_PlayerData> *players_registry, int field[], int substitutes[], T_GameData *game_data, PlayTimeData *time_data, QWidget *parent = 0);
    ~players();
    std::vector<int> get_players_on_court();
    int get_author();
    int get_player_no();
    void show_in_out_players();
    enum{
        none=0,
        select_start_5,
        faul,
        author,
        substitution
    };
    void set_author_mode( int author_mode, bool abort_allowed = false, bool team_allowed = false );
    int get_author_mode(){ return m_author_mode; };
    int get_limit(){ return (registry->size() - N_FIELD); }
    int  get_field_shirt( int index ){
        T_PlayerData tmp;
        if( index >= 0 && index < MAX_PLAYERS ){
            tmp = registry->at(index);
        }else{
            tmp.number = -1;
        }
        return tmp.number;
    };
    QString get_player_name( int index ){
        QString name;
        if( index >= 0 && index == MAX_PLAYERS ){
            name = tr(QT_TR_NOOP("Team"));
        }else{
            T_PlayerData tmp = registry->at(index);
            name = tmp.name;
        }
        return name;
    };
    int get_player_number( int index ){
        int number = 0;
        if( index == MAX_PLAYERS ){
            number = 0;
        }else if( index >= 0 && index < MAX_PLAYERS ){
            T_PlayerData tmp = registry->at(index);
            number = tmp.number;
        }
        return number;
    };
    int get_next_player(int current);
    int get_prev_player(int current);
    GameTime GetUpdatedBanner();
    void set_text(QString text);
    virtual void showEvent ( QShowEvent * event );
    void EndOfPeriod();
    bool IsnewTimeAcceptable(int newtime, int prevtime);
    PlayTimeData *m_time_data;
    void refresh_faul_state();
    void set_button(QPushButton *button, int maglia, int falli);
    void set_enter_time(int in_index, GameTime enter_time);
    void exchange_players(int out, int in);
    void set_field_player(int role, int pl_index);
    void set_subst_player(int role, int pl_index);
    int  lookup_field_pos_by_index(int pl_index);
    int  lookup_subst_pos_by_index(int pl_index);
    void order_by_shirt_number();
    bool can_change_a_player();
    bool can_call_timeout();

private slots:
    void on_bt_change_clicked();

    void on_bt_field1_clicked();

    void on_bt_field2_clicked();

    void on_bt_field3_clicked();

    void on_bt_field4_clicked();

    void on_bt_field5_clicked();

    void on_bt_res_01_clicked();

    void on_bt_res_02_clicked();

    void on_bt_res_03_clicked();

    void on_bt_res_04_clicked();

    void on_bt_res_05_clicked();

    void on_bt_res_06_clicked();

    void on_bt_res_07_clicked();

    void on_bt_res_08_clicked();

    void on_bt_res_09_clicked();

    void on_bt_res_10_clicked();

    void on_bt_close_clicked();

    void on_in_minutes_valueChanged(int arg1);

    void on_in_seconds_valueChanged(int arg1);

    void on_time_slider_sliderMoved(int position);

    void on_bt_my_timeout_clicked();

    void on_bt_oth_tmout_clicked();

private:
    Ui::players *ui;
    ifStore       *m_store;
    std::vector<T_PlayerData> *registry;
    T_GameData *m_game_data;
    bool started;
    bool init_done;
    bool banner_has_changed, is_quarter_init;
    int  *m_field;
    int  *m_subst;
    int  m_out, m_in;
    int  m_intCurrentSlider, m_intPrevSlider, m_iPrevMin, m_iPrevSec;
    void init();

    static QPushButton *in_buttons[N_FIELD];
    static QPushButton *out_buttons[MAX_SUBST];
    static QPushButton *extra_buttons[EXTRA_FOULS];
    void change_sel_for_exit(int from, int to);
    void change_sel_for_enter(int from, int to);
    int    m_author_mode;
};

#endif // PLAYERS_H
