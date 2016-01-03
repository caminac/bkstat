#include <QDateTime>
#include <QFileInfo>
#include "newgame.h"
#include "ui_newgame.h"

newgame::newgame(T_GameData  *game, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newgame)
{
    ui->setupUi(this);
    m_game = game;
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    ui->lb_current_date->setText(dateString);
    m_game->datestring = dateString;
}

newgame::~newgame()
{
    delete ui;
}

void newgame::on_bt_ok_clicked()
{
    m_game->faul_bonus = 5;
    QString tm = ui->text_team->toPlainText();
    if( tm.length() == 0 ){
        tm = "unknown";
    }else if (tm.length() > MAX_LEN_NAMES ) {
        tm = tm.left(MAX_LEN_NAMES);
    }
    m_game->game_desc = tm;

    tm = ui->text_gameid->toPlainText();
    if( tm.length() == 0 ){
        tm = "";
    }else if (tm.length() > MAX_LEN_NAMES ) {
        tm = tm.left(MAX_LEN_NAMES);
    }
    m_game->game_id = tm;

    tm = ui->text_location->toPlainText();
    if( tm.length() == 0 ){
        tm = "";
    }else if (tm.length() > MAX_LEN_NAMES ) {
        tm = tm.left(MAX_LEN_NAMES);
    }
    m_game->location = tm;

    QString file = mk_filename(m_game->game_desc, m_game->datestring);
    m_game->filename = file;

    QString quarter = ui->cb_duration_q->currentText();
    m_game->m_quarter_duration = atoi(quarter.toLatin1());
    QString overtime = ui->cb_duration_ot->currentText();
    m_game->m_overtime_duration = atoi(overtime.toLatin1());
    m_game->m_banner_time.m_min = m_game->m_quarter_duration;
    m_game->m_banner_time.m_sec = 0;
}

QString newgame::mk_filename(QString team, QString date)
{
   bool done=false;
   QFileInfo fi;
   QString postfix = "";
   int     counter=0;
   QString tmpfile;
   tmpfile = team + "_" + date + ".gme";
   while( !done ){
     fi.setFile(tmpfile);
     if( fi.exists() ){
       ++counter;
       //tmpfile.sprintf("%s%d_%s.gme",team,counter,date);
       postfix.sprintf("%d",counter);
       tmpfile = team + postfix + "_" + date + ".gme";
     }else{
       done = true;
     }
   }
   return tmpfile;
}
