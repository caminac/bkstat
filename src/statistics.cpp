#include "players.h"
#include "ifStore.h"
#include "statistics.h"
#include "ui_statistics.h"

statistics::statistics(ifStore *st, T_GameData *game_data, players *pl, PlayTimeData *time_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);
    m_player = 0;
    m_store = st;
    m_players = pl;
    m_game_data = game_data;
    m_time_data = time_data;
}

statistics::~statistics()
{
    delete ui;
}

void statistics::on_bt_close_clicked()
{
    this->hide();
}

void statistics::on_bt_prev_clicked()
{
    int next_pl = m_players->get_prev_player(m_player);
    set_player(next_pl);
}

void statistics::on_bt_next_clicked()
{
    int next_pl = m_players->get_next_player(m_player);
    set_player(next_pl);
}

void statistics::set_player(int pl)
{
    QString text, v1, v2, perc, name;
    m_player = pl;
    T_PlayerData tmp;
    int n, t1, t2, t3, shirt;

    shirt = m_players->get_field_shirt(pl);
    name = m_players->get_player_name(pl);
    if( shirt > -1 ){
        v1 = QString::number(shirt,10);
        text = tr(QT_TR_NOOP("Player #")) + v1 + " " + name;
    }else{
        text = name;
    }
    ui->lb_player->setText(text);

    if( shirt > -1 ){
        t1 = m_store->GetScore(ifStore::t1_ok,m_player);
        v1 = QString::number(t1,10);
        v2 = QString::number(m_store->GetScore(ifStore::t1_ko,m_player),10);
        perc = m_store->get_perc( ifStore::t1_ok, ifStore::t1_ko, m_player);
        text = tr(QT_TR_NOOP("FT:")) + v1 + "/" + v2 + " " + perc;
    }else{
        text = "-";
    }
    ui->lb_t1->setText(text);

    if( shirt > -1 ){
        t2 = m_store->GetScore(ifStore::t2_ok,m_player);
        v1 = QString::number(t2,10);
        v2 = QString::number(m_store->GetScore(ifStore::t2_ko,m_player),10);
        perc = m_store->get_perc( ifStore::t2_ok, ifStore::t2_ko, m_player);
        text = tr(QT_TR_NOOP("FG2 : ")) + v1 + "/" + v2 + " " + perc;
    }else{
        text = "-";
    }
    ui->lb_t2->setText(text);

    if( shirt > -1 ){
    t3 = m_store->GetScore(ifStore::t3_ok,m_player);
    v1 = QString::number(t3,10);
    v2 = QString::number(m_store->GetScore(ifStore::t3_ko,m_player),10);
    perc = m_store->get_perc( ifStore::t3_ok, ifStore::t3_ko, m_player);
    text = tr(QT_TR_NOOP("FG3 : ")) + v1 + "/" + v2 + " " + perc;
    }else{
        text = "-";
    }
    ui->lb_t3->setText(text);

    if( shirt > -1 ){
        n = t1 + 2*t2 + 3*t3;
        v1 = tr(QT_TR_NOOP("Pts: ")) + QString::number(n,10);
    }else{
        v1 = "-";
    }
    ui->lb_points->setText(v1);

    n = m_store->GetScore(ifStore::val,m_player);
    v1 = tr(QT_TR_NOOP("VAL: ")) + QString::number(n,10);
    ui->lb_val->setText(v1);

    // tempo giocato

    if( shirt > -1 ){
        GameTime t = m_time_data->GetFullPlayedTime(m_player);
        QString x = m_time_data->GetStringFullPlayedTime(t);
        v1 = tr(QT_TR_NOOP("Min: ")) + x;
        n = m_time_data->GetImpact(m_player);
        v2 = "+/-:  " + QString::number(n,10);
    }else{
        v1 = "-";
        v2 = "-";
    }
    ui->lb_min->setText(v1);
    ui->lb_plusminus->setText(v2);

    // Rebounds
    v1 = QString::number(m_store->GetScore(ifStore::rb_atk,m_player),10);
    v2 = QString::number(m_store->GetScore(ifStore::rb_def,m_player),10);
    text = tr(QT_TR_NOOP("Reb  Off: ")) + v1 + tr(QT_TR_NOOP(" / Def : ")) + v2;
    ui->lb_rimb->setText(text);

    // Steal / turnovers
    v1 = QString::number(m_store->GetScore(ifStore::stl_done,m_player),10);
    v2 = QString::number(m_store->GetScore(ifStore::stl_recv,m_player),10);
    text = tr(QT_TR_NOOP("Steals : ")) + v1 + tr(QT_TR_NOOP(" / Turnovers : ")) + v2;
    ui->lb_steal_to->setText(text);

    // fauls
    v1 = QString::number(m_store->GetScore(ifStore::fl_recv,m_player),10);
    v2 = QString::number(m_store->GetScore(ifStore::fl_done,m_player),10);
    text = tr(QT_TR_NOOP("Fouls + ")) + v1 + tr(QT_TR_NOOP(" / Done : ")) + v2;
    ui->lb_fouls->setText(text);

    // blocks
    if( shirt > -1 ){
        v1 = QString::number(m_store->GetScore(ifStore::blocks_done,m_player),10);
        v2 = QString::number(m_store->GetScore(ifStore::blocks_recv,m_player),10);
        text = tr(QT_TR_NOOP("Blocks + ")) + v1 + tr(QT_TR_NOOP(" / Received : ")) + v2;
    }else{
        text = "-";
    }
    ui->lb_stopp->setText(text);
    // Assist
    if( shirt > -1 ){
        v1 = QString::number(m_store->GetScore(ifStore::assist,m_player),10);
        text = tr(QT_TR_NOOP("Assist ")) + v1;
    }else{
        text = "-";
    }
    ui->lb_asst->setText(text);
}
