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
    m_list.clear();

    m_fauls_definitions.push_back("P");
    m_fauls_definitions.push_back("P1");
    m_fauls_definitions.push_back("P2");
    m_fauls_definitions.push_back("P3");
    m_fauls_definitions.push_back("T1");
    m_fauls_definitions.push_back("U2");
    m_fauls_definitions.push_back("DG");
    m_fauls_definitions.push_back("F");
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

    m_ft_on_faul = 0;
    faul_coach = false;
    faul_team = false;
}

void faul_menu::set_players()
{
    ui->cb_MyTeam->clear();
    ui->cb_OthTeam->clear();
    ui->cb_Faul->clear();
    m_list = m_players->get_players_on_court();
    for( unsigned int i=0; i<m_list.size(); i++ ){
        QString item = QString::number( m_players->get_field_shirt(m_list[i]),10);
        ui->cb_MyTeam->addItem(item);
    }
    ui->cb_MyTeam->insertItem(POS_NOBODY,"--");
    ui->cb_MyTeam->insertItem(POS_COACH,"C");
    ui->cb_MyTeam->insertItem(POS_BENCH,"B");
    ui->cb_MyTeam->setCurrentIndex(POS_NOBODY);

    for( unsigned int i=0; i<m_list.size(); i++ ){
        ui->cb_OthTeam->addItem("?");
        // ui->cb_OthTeam->setEnabled(false);
    }
    ui->cb_OthTeam->insertItem(POS_NOBODY,"--");
    ui->cb_OthTeam->insertItem(POS_COACH,"C");
    ui->cb_OthTeam->insertItem(POS_BENCH,"B");
    ui->cb_OthTeam->setCurrentIndex(POS_NOBODY);

    for (int i=0; i < m_fauls_definitions.size(); ++i){
      ui->cb_Faul->insertItem(i,m_fauls_definitions[i].c_str());
    }

    /*
    UpdateScoreboard(ifStore::t1_ok,m_store->GetScore(ifStore::t1_ok,m_player),m_player);
    UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko,m_player),m_player);
    UpdateScoreboard(ifStore::fl_recv,m_store->GetScore(ifStore::fl_recv,m_player),m_player);
    UpdateScoreboard(ifStore::fl_done,m_store->GetScore(ifStore::fl_done,m_player),m_player);

    QString label = "FT:" + m_store->get_perc(ifStore::t1_ok,ifStore::t1_ko,m_player);
    ui->lb_ft_perc->setText(label);
     */
}

void faul_menu::on_bt_ft_ok_clicked()
{
    ft_done++;
    m_store->AddScore(ifStore::t1_ok,m_ft_author,ifStore::team_A); // m_player);
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
    m_store->AddScore(ifStore::t1_ko,m_ft_author,ifStore::team_A); // m_player);
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
            m_store->AddScore(ifStore::rb_atk,pl,ifStore::team_A);
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

/*******************************************************************/
/* Falli subiti                                                    */
/*******************************************************************/
void faul_menu::on_bt_foul_recv_clicked()
{
    QMessageBox msgBox;
    QString text, text_player;
    T_FaulDetails det;
    if( !get_faul_details(det,faul_menu::received) ){
        text = tr(QT_TR_NOOP("invalid selection"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    text_player = get_faul_subject(det);
    QString ftype = m_fauls_definitions[det.foul_type].c_str();
    text = tr(QT_TR_NOOP("Confirm faul \"")) + ftype + tr(QT_TR_NOOP("\" received by ")) + text_player + "?";

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){

        m_ft_author = det.my_data;  //m_player;

        faul_received(det);
    }else{
      m_ft_on_faul = 0;
    }
}

void faul_menu::faul_received(T_FaulDetails det)
{
    m_ft_on_faul = get_TL(det.foul_type);
    m_player = det.my_data;
    ft_done = 0;
    m_store->AddScore(ifStore::fl_recv,m_player,det.foul_type,ifStore::team_A);
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
    QMessageBox msgBox;
    QString text, text_player;
    T_FaulDetails det;
    if( !get_faul_details(det,faul_menu::committed) ){
        text = tr(QT_TR_NOOP("invalid selection"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    text_player = get_faul_subject(det);
    QString ftype = m_fauls_definitions[det.foul_type].c_str();
    text = tr(QT_TR_NOOP("Confirm faul \"")) + ftype + tr(QT_TR_NOOP("\" done by ")) + text_player + "?";

    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if( ret == QMessageBox::Ok){
        faul_done(det);
    }
}

void faul_menu::faul_done(T_FaulDetails det)
{
    m_player = det.my_data;
    int faul_count = m_store->GetScore(ifStore::fl_done,m_player);
    if( faul_count < fauls_bonus ){
        int team = ifStore::team_A;
        int other_team_player = -1;
        if( det.oth_data != -1 ){
            team = ifStore::team_B;
            if( det.oth_data == POS_COACH ){
                other_team_player = COACH_INDEX;
            }else if( det.oth_data == POS_BENCH ){
                other_team_player = BENCH_INDEX;
            }
        }else if( det.my_data == POS_COACH ){
            m_player = COACH_INDEX;
        }else if( det.my_data == POS_BENCH ){
            m_player = BENCH_INDEX;
        }
        m_store->AddScore(ifStore::fl_done,m_player,team,det.foul_type,other_team_player);
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

    m_ft_on_faul = get_TL(det.foul_type);
    if( det.oth_data != -1 ){
        if( det.foul_type == ifStore::faul_T ||
            det.foul_type == ifStore::faul_F ||
            det.foul_type == ifStore::faul_DG )
        {
            this->hide();
            m_ft_author = m_stat->ask_player(players::author,tr(QT_TR_NOOP("who will throw FT?")));
            this->show();
            go_to_FT();
        }else{
            this->hide();
        }
    }else{
        this->hide();
    }
}

int faul_menu::get_TL(int f_type)
{
  int rv = 0;

  switch( f_type ){
      case ifStore::faul_P:
          rv = 0;
          break;
      case ifStore::faul_P1:
          rv = 1;
          break;
      case ifStore::faul_P2:
          rv = 2;
          break;
      case ifStore::faul_P3:
          rv = 3;
          break;
      case ifStore::faul_T:
          rv = 1;
          break;
      case ifStore::faul_U:
      case ifStore::faul_DG:
      case ifStore::faul_F:
          rv = 2;
          break;
  };
  return rv;
}

bool faul_menu::get_faul_details(T_FaulDetails& det, int direction)
{
    bool rv = false;
    int faul_type = ui->cb_Faul->currentIndex();
    int my_player = ui->cb_MyTeam->currentIndex();
    int oth_player = ui->cb_OthTeam->currentIndex();
    int last_action = m_store->GetLastAction();
    det.foul_type = -1;
    det.my_data = -1;
    det.oth_data = -1;
    if( direction == faul_menu::received ){
        // only P and U fauls can be received
        if( faul_type == ifStore::faul_P ||
            faul_type == ifStore::faul_P1 ||
            faul_type == ifStore::faul_P2 ||
            faul_type == ifStore::faul_P3 ||
            faul_type == ifStore::faul_U ){
                if( my_player < N_FIELD ){
                    bool ok=true;
                    if( faul_type == ifStore::faul_P1 ){
                        if( last_action != ifStore::t2_ok && last_action != ifStore::t3_ok ){
                            ok = false;
                        }
                    }
                    if( ok ){
                        det.foul_type = faul_type;
                        det.my_data = my_player;
                        rv = true;
                    }
                }
        }
    }else{
        if( faul_type == ifStore::faul_P ||
            faul_type == ifStore::faul_P1 ||
            faul_type == ifStore::faul_P2 ||
            faul_type == ifStore::faul_P3 ||
            faul_type == ifStore::faul_U ){
            if( my_player < N_FIELD ){
                det.foul_type = faul_type;
                det.my_data = my_player;
                rv = true;
            }
        }else if( faul_type == ifStore::faul_T ||
                  faul_type == ifStore::faul_DG ||
                  faul_type == ifStore::faul_F ){
            if( my_player == POS_NOBODY && oth_player != POS_NOBODY ){
                det.foul_type = faul_type;
                det.oth_data = oth_player;
                rv = true;
            }else if( my_player != POS_NOBODY && oth_player == POS_NOBODY ){
                det.foul_type = faul_type;
                det.my_data = my_player;
                rv = true;
            }
        }
    }
    return rv;
}

QString faul_menu::get_faul_subject(T_FaulDetails det)
{
    QString text_player;
    int shirt_number = -1;
    if( det.my_data == POS_COACH && det.foul_type == ifStore::faul_T ){
        text_player = QT_TR_NOOP("our coach (C)");
    }else if( det.my_data == POS_BENCH && det.foul_type == ifStore::faul_T ){
        text_player = QT_TR_NOOP("our bench (B)");
    }else if( det.oth_data == POS_COACH && det.foul_type == ifStore::faul_T ){
        text_player = QT_TR_NOOP("other coach (C)");
    }else if( det.oth_data == POS_BENCH && det.foul_type == ifStore::faul_T ){
        text_player = QT_TR_NOOP("other bench (B)");
    }else if( det.my_data == POS_COACH && det.foul_type == ifStore::faul_DG ){
        text_player = QT_TR_NOOP("our coach (DG)");
    }else if( det.oth_data == POS_COACH && det.foul_type == ifStore::faul_DG ){
        text_player = QT_TR_NOOP("other coach (DG)");
    }else if( det.my_data == POS_COACH && det.foul_type == ifStore::faul_F ){
        text_player = QT_TR_NOOP("our coach (F)");
    }else if( det.oth_data == POS_COACH && det.foul_type == ifStore::faul_F ){
        text_player = QT_TR_NOOP("other coach (F)");
    }else{
        shirt_number = m_players->get_field_shirt(det.my_data);
        text_player = tr(QT_TR_NOOP("player ")) + QString::number(shirt_number,10);
    }
    return text_player;
}

void faul_menu::on_cb_MyTeam_currentIndexChanged(int index)
{

}

void faul_menu::on_cb_OthTeam_currentIndexChanged(int index)
{

}

void faul_menu::on_cb_Faul_currentIndexChanged(const QString &arg1)
{
    int sel = ui->cb_Faul->currentIndex();
    if( sel == ifStore::faul_T ||
        sel == ifStore::faul_DG ||
        sel == ifStore::faul_F )
    {
        ui->cb_MyTeam->setCurrentIndex(POS_NOBODY);
        ui->cb_OthTeam->setCurrentIndex(POS_NOBODY);
    }
}
