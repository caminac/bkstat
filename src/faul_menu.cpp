#include <QMessageBox>
#include "faul_menu.h"
#include "ui_faul_menu.h"
#include "playstat.h"

faul_menu::faul_menu(playstat *stat, ifStore *store, players *pl, int bonus, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::faul_menu)
{
    ui->setupUi(this);
    m_stat = stat;
    m_store = store;
    fauls_bonus = bonus;
    m_players = pl;
    ft_done = 0;
}

faul_menu::~faul_menu()
{
    delete ui;
}

void faul_menu::FaulDetected()
{
    ui->label->setVisible(true);
    ui->bt_foul_done->setVisible(true);
    ui->bt_foul_recv->setVisible(true);
    ui->lb_ft_perc->setVisible(false);
    ui->bt_ft_ko->setVisible(false);
    ui->bt_ft_ok->setVisible(false);
    ui->bt_oreb->setVisible(false);
    ui->bt_change_on_faul->setVisible(false);

    ui->rb_noft->setVisible(true);
    ui->rb_1FT->setVisible(true);
    ui->rb_2FT->setVisible(true);
    ui->rb_3FT->setVisible(true);
    ui->rb_faul_tech->setVisible(true);
    ui->rb_faul_antisp->setVisible(true);
    ui->rb_Espulsione->setVisible(true);

    ui->bt_tech_coach_done->setVisible(true);
    ui->bt_tech_team_done->setVisible(true);
    ui->bt_tech_recv->setVisible(true);

    ui->rb_noft->setChecked(true);
    ui->rb_1FT->setChecked(false);
    ui->rb_2FT->setChecked(false);
    ui->rb_3FT->setChecked(false);
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
    m_ft_on_faul = 0;
    faul_coach = false;
    faul_team = false;
}

void faul_menu::set_player(int player)
{
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
    m_player = player;
    UpdateScoreboard(ifStore::t1_ok,m_store->GetScore(ifStore::t1_ok,m_player),m_player);
    UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko,m_player),m_player);
    UpdateScoreboard(ifStore::fl_recv,m_store->GetScore(ifStore::fl_recv,m_player),m_player);
    UpdateScoreboard(ifStore::fl_done,m_store->GetScore(ifStore::fl_done,m_player),m_player);

    QString label = "FT:" + m_store->get_perc(ifStore::t1_ok,ifStore::t1_ko,m_player);
    ui->lb_ft_perc->setText(label);
}

void faul_menu::on_bt_ft_ok_clicked()
{
    ft_done++;
    m_store->AddScore(ifStore::t1_ok,m_ft_author); // m_player);
    UpdateScoreboard(ifStore::t1_ok,m_store->GetScore(ifStore::t1_ok,m_ft_author),m_ft_author); // m_player);
    UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko,m_ft_author),m_ft_author); // m_player);
    m_stat->UpdateScoreboard(ifStore::t1_ok,m_store->GetScore(ifStore::t1_ok));
    m_stat->UpdateScoreboard(ifStore::points,m_store->GetScore(ifStore::points));
    m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));

    QString label = "FT:" + m_store->get_perc(ifStore::t1_ok,ifStore::t1_ko,m_ft_author); // m_player);
    ui->lb_ft_perc->setText(label);
    if( ft_done >= m_ft_on_faul ){
        this->hide();
        return;
    }
}

void faul_menu::on_bt_ft_ko_clicked()
{
    ft_done++;
    m_store->AddScore(ifStore::t1_ko,m_ft_author); // m_player);
    UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko,m_ft_author),m_ft_author); // m_player);
    m_stat->UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko));
    m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));

    QString label = "FT:" + m_stat->get_perc(ifStore::t1_ok, ifStore::t1_ko,m_ft_author); // m_player);
    ui->lb_ft_perc->setText(label);
    if( ft_done >= m_ft_on_faul ){
        this->hide();
        return;
    }
}

void faul_menu::go_to_FT()
{
    ui->label->setVisible(false);
    ui->bt_foul_done->setVisible(false);
    ui->bt_foul_recv->setVisible(false);
    ui->lb_ft_perc->setVisible(true);
    ui->bt_ft_ko->setVisible(true);
    ui->bt_ft_ok->setVisible(true);
    ui->bt_oreb->setVisible(true);

    ui->rb_noft->setVisible(false);
    ui->rb_1FT->setVisible(false);
    ui->rb_2FT->setVisible(false);
    ui->rb_3FT->setVisible(false);
    ui->rb_faul_tech->setVisible(false);
    ui->rb_faul_antisp->setVisible(false);
    ui->bt_change_on_faul->setVisible(true);
    ui->bt_tech_coach_done->setVisible(false);
    ui->bt_tech_recv->setVisible(false);
    ui->bt_tech_team_done->setVisible(false);
}

bool faul_menu::can_close_dialog()
{
    bool rv = true;
    if( ft_done < m_ft_on_faul ){
        QString text;
        text = tr(QT_TR_NOOP("Again ")) + QString::number(m_ft_on_faul-ft_done,10) + tr(QT_TR_NOOP(" FT"));
        QMessageBox msgBox;
        msgBox.setText(text);
        msgBox.exec();
        rv = false;
    }
    return rv;
}

void faul_menu::on_bt_close_clicked()
{
    if( can_close_dialog() ){
        ft_done = 0;
        this->hide();
    }
}

void faul_menu::UpdateScoreboard(int item, int value, int player_index)
{
    QString label;
    QString text = QString::number(value);

    switch(item){
        case ifStore::t1_ok:
            ui->bt_ft_ok->setText(text);
            break;
        case ifStore::t1_ko:
            ui->bt_ft_ko->setText(text);
            break;
        case ifStore::fl_recv:
            ui->bt_foul_recv->setText(text);
            break;
        case ifStore::fl_done:
            ui->bt_foul_done->setText(text);
            break;
    }
}

void faul_menu::on_bt_oreb_clicked()
{
    //this->hide();
    //int pl = m_stat->ask_player(true,"who made OREB ?");
    //m_store->AddScore(ifStore::rb_atk ,pl);
    //m_stat->UpdateScoreboard(ifStore::rb_atk,m_store->GetScore(ifStore::rb_atk,pl),pl);
    //m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));

    if( can_close_dialog() ){
        int last_action = m_store->GetLastAction();
        if( last_action == ifStore::t1_ko )
        {
            this->hide();
            int pl = m_stat->ask_player(players::author,tr(QT_TR_NOOP("who made OREB ?")),false,true);
            m_store->AddScore(ifStore::rb_atk,pl);
            m_stat->UpdateScoreboard(ifStore::rb_atk,m_store->GetScore(ifStore::rb_atk));
            m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
        }else{
            QString text;
            text = tr(QT_TR_NOOP("Previous action is not an error"));
            QMessageBox msgBox;
            msgBox.setText(text);
            msgBox.exec();
        }
    }
}

/**
per poter fare un cambio durante i TL
*/
void faul_menu::on_bt_change_on_faul_clicked()
{
    int orig_am = m_players->get_author_mode();
    m_players->set_author_mode(players::substitution);
    m_players->update();
    this->hide();
    m_players->set_text(tr(QT_TR_NOOP("Select in and out\nplayers then <->")));
    m_players->showNormal();
    if ( m_players->exec() == QDialog::Accepted ) {
    }
    m_players->set_author_mode(orig_am);
    this->showNormal();
}

void faul_menu::on_rb_noft_clicked()
{

}

void faul_menu::on_rb_1FT_clicked()
{

}

void faul_menu::on_rb_2FT_clicked()
{

}

void faul_menu::on_rb_3FT_clicked()
{

}

/*******************************************************************/
/* Falli subiti                                                    */
/*******************************************************************/
void faul_menu::on_bt_foul_recv_clicked()
{
    ft_done = 0;
    m_ft_on_faul = get_TL();
    QMessageBox msgBox;
    QString text, text_player;

    text_player = get_faul_subject();
    if( m_ft_on_faul == TECH_FAUL ){
        text = tr(QT_TR_NOOP("Tech faul can't be received"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        return;
    }else if( m_ft_on_faul == ANTISP_FAUL ){
        text = tr(QT_TR_NOOP("Confirm unsport faul recv by ")) + text_player + "?";
    }else if(m_ft_on_faul > 0){
        text = tr(QT_TR_NOOP("Confirm faul (P")) + QString::number(m_ft_on_faul,10) + tr(QT_TR_NOOP(") recv by ")) + text_player + "?";
    }else{
        text = tr(QT_TR_NOOP("Confirm faul recv by ")) + text_player + "?";
    }
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        if(  m_ft_on_faul == TECH_FAUL ){
            this->hide();
            m_ft_author = m_stat->ask_player(players::author,tr(QT_TR_NOOP("who will throw FT?")));
            this->show();
        }else{
            m_ft_author = m_player;
        }
        faul_received(m_ft_on_faul);
    }else{
      m_ft_on_faul = 0;
    }
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
}

void faul_menu::faul_received(int type)
{
    if( type == TECH_FAUL || type == ANTISP_FAUL ){
        m_ft_on_faul = 2;
    }else{
        m_ft_on_faul = type;
    }
    ft_done = 0;
    m_store->AddScore(ifStore::fl_recv,m_player,type);
    UpdateScoreboard(ifStore::fl_recv,m_store->GetScore(ifStore::fl_recv,m_player),m_player);
    m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
    m_stat->UpdateScoreboard(ifStore::oth_fauls,m_store->GetScore(ifStore::oth_fauls));
    if( m_ft_on_faul > 0 ){
        go_to_FT();
    }else{
        this->hide();
    }
}

/*******************************************************************/
/* Falli commessi                                                  */
/*******************************************************************/
void faul_menu::on_bt_foul_done_clicked()
{
    m_ft_on_faul = get_TL();
    QMessageBox msgBox;
    QString text, text_player;
    text_player = get_faul_subject();
    if( m_ft_on_faul == TECH_FAUL ){
        text = tr(QT_TR_NOOP("Confirm tech faul done by ")) + text_player + "?";
    }else if( m_ft_on_faul == ANTISP_FAUL ){
        text = tr(QT_TR_NOOP("Confirm unsport faul done by ")) + text_player + "?";
    }else if(m_ft_on_faul > 0){
        text = tr("Confirm faul (P") + QString::number(m_ft_on_faul,10) + tr(QT_TR_NOOP(") done by ")) + text_player + "?";
    }else{
        text = tr(QT_TR_NOOP("Confirm faul done by ")) + text_player + "?";
    }
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        faul_done(m_ft_on_faul);
    }
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
}

void faul_menu::faul_done(int type)
{
    if( type == TECH_FAUL || type == ANTISP_FAUL ){
        m_ft_on_faul = 2;
    }else{
        m_ft_on_faul = type;
    }
    int faul_count = m_store->GetScore(ifStore::fl_done,m_player);
    if( faul_count < fauls_bonus ){
        m_store->AddScore(ifStore::fl_done,m_player,type);
        faul_count = m_store->GetScore(ifStore::fl_done,m_player);
        UpdateScoreboard(ifStore::fl_done,faul_count,m_player);
        m_stat->UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
        m_stat->UpdateScoreboard(ifStore::my_fauls,m_store->GetScore(ifStore::my_fauls));
        if( faul_count == fauls_bonus ){
            QString text;
            text = tr(QT_TR_NOOP("Player ")) + tr(QT_TR_NOOP(" must be replaced"));
            QMessageBox msgBox;
            msgBox.setText(text);
            msgBox.exec();
        }
    }else{
    }
    this->hide();
}

int faul_menu::get_TL()
{
  int rv = 0;
  if( ui->rb_noft->isChecked() ){
  }else if( ui->rb_1FT->isChecked() ){
    rv = 1;
  }else if( ui->rb_2FT->isChecked() ){
    rv = 2;
  }else if( ui->rb_3FT->isChecked() ){
    rv = 3;
  }else if( ui->rb_faul_tech->isChecked() ){
    rv = TECH_FAUL;
  }else if( ui->rb_faul_antisp->isChecked() ){
    rv = ANTISP_FAUL;
  }else if( ui->rb_Espulsione->isChecked() ){
    rv = 2;
  }
  return rv;
}

QString faul_menu::get_faul_subject()
{
    int shirt_number = m_players->get_field_shirt(m_player);
    QString text_player;
    if( faul_team ){
      text_player = tr(QT_TR_NOOP("team"));
    }else if( faul_coach ){
      text_player = tr(QT_TR_NOOP("coach"));
    }else{
      text_player = tr(QT_TR_NOOP("player ")) + QString::number(shirt_number,10);
    }
    return text_player;
}

void faul_menu::on_bt_tech_recv_clicked()
{
    ft_done = 0;
    m_ft_on_faul = 2;
    m_player = MAX_PLAYERS;
    QMessageBox msgBox;
    QString text;

    text = tr(QT_TR_NOOP("Confirm tech faul recv?"));
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        this->hide();
        m_ft_author = m_stat->ask_player(players::author,tr(QT_TR_NOOP("who will throw FT?")));
        this->show();
        faul_received(TECH_FAUL);
    }
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
}

void faul_menu::on_bt_tech_team_done_clicked()
{
    m_ft_on_faul = 2;
    m_player = MAX_PLAYERS;
    QMessageBox msgBox;
    QString text, text_player;
    text_player = tr(QT_TR_NOOP("Team"));
    text = tr(QT_TR_NOOP("Confirm tech faul done by ")) + text_player + "?";

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        faul_done(TECH_FAUL);
    }
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
}

void faul_menu::on_bt_tech_coach_done_clicked()
{
    m_ft_on_faul = 2;
    m_player = MAX_PLAYERS;
    QMessageBox msgBox;
    QString text, text_player;
    text_player = tr(QT_TR_NOOP("Coach"));
    text = tr(QT_TR_NOOP("Confirm tech faul done by ")) + text_player + "?";

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        faul_done(TECH_FAUL);
    }
    ui->rb_faul_tech->setChecked(false);
    ui->rb_faul_antisp->setChecked(false);
}
