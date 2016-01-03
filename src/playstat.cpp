
#include <QMessageBox>
#include "playstat.h"
#include "ui_playstat.h"
#include "ifStore.h"
#include "players.h"
#include "setup.h"

const char * playstat::azioni[] ={
    QT_TR_NOOP("Free Throw"),
    QT_TR_NOOP("Free Throw ERROR"),
    QT_TR_NOOP("FG 2"),
    QT_TR_NOOP("FG 2 ERROR"),
    QT_TR_NOOP("FG 3"),
    QT_TR_NOOP("FG 3 ERROR"),
    QT_TR_NOOP("Defensive Rebound"),
    QT_TR_NOOP("Offensive Rebound"),
    QT_TR_NOOP("Faul received"),
    QT_TR_NOOP("Faul done"),
    QT_TR_NOOP("Steal"),
    QT_TR_NOOP("Lost ball"),
    QT_TR_NOOP("Assist"),
    QT_TR_NOOP("Block Done"),
    QT_TR_NOOP("Block received"),
    QT_TR_NOOP("Out"),
    QT_TR_NOOP("In"),
    QT_TR_NOOP("Start 5"),
    QT_TR_NOOP("End of period"),
    "","","","","",
    QT_TR_NOOP("Initial Substitute"),
    "",
    QT_TR_NOOP("FT received"),
    QT_TR_NOOP("FG 2 received"),
    QT_TR_NOOP("FG 3 received"),
    "",
    "",
    "",
    QT_TR_NOOP("Timeout"),
    QT_TR_NOOP("Timeout"),
};
playstat::playstat(ifStore *st, T_GameData *game_data, players *pl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playstat)
{
    m_store = st;
    m_players = pl;
    m_game_data = game_data;
    m_fauls = new faul_menu(this, st, pl);
    m_oth_pt = new oth_points_menu(this, st, game_data);
    ui->setupUi(this);
    //player_selector = new select_player();
    m_players->set_author_mode(players::none);

#if defined(DEMO_VERSION)
    ui->bt_asst->setEnabled(false);
    ui->bt_blocks->setEnabled(false);
    ui->bt_blk_recv->setEnabled(false);
#endif
}

playstat::~playstat()
{
    delete ui;
}

void playstat::startGame()
{
    if( m_game_data->simplified ){
        ui->bt_t3_ok->setEnabled(false);
        ui->bt_t3_ok->setStyleSheet("background-color: rgb(186, 186, 186);");
        ui->bt_t3_ko->setEnabled(false);
        ui->bt_t3_ko->setStyleSheet("background-color: rgb(186, 186, 186);");
        ui->lab_t3->setEnabled(false);
        ui->bt_blk_recv->setEnabled(false);
        ui->bt_blk_recv->setStyleSheet("background-color: rgb(186, 186, 186);");
        ui->bt_blocks->setEnabled(false);
        ui->bt_blocks->setStyleSheet("background-color: rgb(186, 186, 186);");
    }
}

/**
*/
void playstat::UpdateScoreboard(int item, int value, int player_index)
{
    QString label;
    QString text = QString::number(value);

    switch(item){
        case ifStore::t1_ok:
        case ifStore::t1_ko:
            //ui->bt_t1_ok->setText(text);
            label = tr("FT:") + get_perc( ifStore::t1_ok, ifStore::t1_ko );
            ui->lb_ft->setText(label);
            break;
        case ifStore::t2_ok:
            ui->bt_t2_ok->setText(text);
            label = tr("FG2:") + get_perc( ifStore::t2_ok, ifStore::t2_ko );
            ui->lab_t2->setText(label);
            break;
        case ifStore::t2_ko:
            ui->bt_t2_ko->setText(text);
            label = tr("FG2:") + get_perc( ifStore::t2_ok, ifStore::t2_ko );
            ui->lab_t2->setText(label);
            break;
        case ifStore::t3_ok:
            ui->bt_t3_ok->setText(text);
            label = tr("FG3:") + get_perc( ifStore::t3_ok, ifStore::t3_ko );
            ui->lab_t3->setText(label);
            break;
        case ifStore::t3_ko:
            ui->bt_t3_ko->setText(text);
            label = tr("FG3:") + get_perc( ifStore::t3_ok, ifStore::t3_ko );
            ui->lab_t3->setText(label);
            break;
        case ifStore::rb_def:
            ui->bt_reb_def->setText(text);
            break;
        case ifStore::rb_atk:
            ui->bt_reb_off->setText(text);
            break;
        case ifStore::fl_recv:
            //ui->bt_fauls_recv->setText(text);
            break;
        case ifStore::fl_done:
            //ui->bt_fauls_done->setText(text);
            break;
        case ifStore::stl_done:
            ui->bt_steal_ok->setText(text);
            break;
        case ifStore::stl_recv:
            ui->bt_steal_ko->setText(text);
            break;
        case ifStore::assist:
            ui->bt_asst->setText(text);
            break;
        case ifStore::blocks_done:
            ui->bt_blocks->setText(text);
            break;
        case ifStore::blocks_recv:
            ui->bt_blk_recv->setText(text);
            break;
        case ifStore::points:
            ui->label_pts->setText(text);
            break;
        case ifStore::val:
            // ui->label_val->setText(text);
            break;
        case ifStore::oth_points:
            ui->bt_oth_points->setText(text);
            break;
        case ifStore::my_fauls:
            ui->label_my_fauls->setText(text);
            if( value >= 5 ){
              ui->label_my_fauls->setStyleSheet("color: rgb(255, 255, 255);\nbackground-color: rgb(255, 0, 0);\nfont: 75 8pt \"MS Shell Dlg 2\";");
            }else{
              ui->label_my_fauls->setStyleSheet("color: rgb(0, 0, 0);\nbackground-color: rgb(193, 193, 193);");
            }
            break;
        case ifStore::oth_fauls:
            ui->label_oth_fauls->setText(text);
            if( value >= 5 ){
              ui->label_oth_fauls->setStyleSheet("color: rgb(255, 255, 255);\nbackground-color: rgb(255, 0, 0);\nfont: 75 8pt \"MS Shell Dlg 2\";");
            }else{
              ui->label_oth_fauls->setStyleSheet("color: rgb(0, 0, 0);\nbackground-color: rgb(193, 193, 193);");
            }
            break;
        case ifStore::actual_quarter:
            if( value <= 4 ){
              label.sprintf("Q%d",value);
            }else{
              label.sprintf("OT%d",(value-4));
            }
            if( is_game_ended() ){
                label = tr("End");
            }
            ui->bt_q_indicator->setText(label);
            break;
    }
}

QString playstat::get_perc( int item1, int item2, int player_index )
{
    QString str;
    int v1, v2;
    float perc, sum;
    v1 = m_store->GetScore(item1);
    v2 = m_store->GetScore(item2);
    sum = v2; //1 + v2;
    if( sum > 0 ){
        perc = (float)(v1 / sum);
        perc *= 100;
        str.sprintf("%.1f %%",perc);
    }else{
        str = "-.- %";
    }
    return str;
}

void playstat::on_bt_change_clicked()
{
    if( is_game_ended() ){ return; }
    m_players->set_author_mode(players::substitution);
    m_players->update();
    this->hide();
    m_players->set_text(tr(QT_TR_NOOP("Select in and out\nplayers then <->")));
    m_players->showNormal();
    if ( m_players->exec() == QDialog::Accepted ) {
    }
    this->showNormal();
}

void playstat::on_bt_t2_ok_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who scored 2 pt?")));
    m_store->AddScore(ifStore::t2_ok,pl);
    UpdateScoreboard(ifStore::t2_ok,m_store->GetScore(ifStore::t2_ok));
    UpdateScoreboard(ifStore::t2_ko,m_store->GetScore(ifStore::t2_ko));
    UpdateScoreboard(ifStore::points,m_store->GetScore(ifStore::points));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_t2_ko_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who missed FG2?")));
    m_store->AddScore(ifStore::t2_ko,pl);
    UpdateScoreboard(ifStore::t2_ko,m_store->GetScore(ifStore::t2_ko));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_t3_ok_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who scored 3 pt?")));
    m_store->AddScore(ifStore::t3_ok,pl);
    UpdateScoreboard(ifStore::t3_ok,m_store->GetScore(ifStore::t3_ok));
    UpdateScoreboard(ifStore::t3_ko,m_store->GetScore(ifStore::t3_ko));
    UpdateScoreboard(ifStore::points,m_store->GetScore(ifStore::points));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_t3_ko_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who missed FG3 ?")));
    m_store->AddScore(ifStore::t3_ko,pl);
    UpdateScoreboard(ifStore::t3_ko,m_store->GetScore(ifStore::t3_ko));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_reb_off_clicked()
{
    if( is_game_ended() ){ return; }
    int last_action = m_store->GetLastAction();
    if( last_action == ifStore::t1_ko ||
        last_action == ifStore::t2_ko ||
        last_action == ifStore::t3_ko )
    {
        int pl = ask_player(players::author,tr(QT_TR_NOOP("who did OREB?")),false,true);
        m_store->AddScore(ifStore::rb_atk,pl);
        UpdateScoreboard(ifStore::rb_atk,m_store->GetScore(ifStore::rb_atk));
        UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
    }else{
        QString text;
        text = tr(QT_TR_NOOP("Previous action is not an error"));
        QMessageBox msgBox;
        msgBox.setText(text);
        msgBox.exec();
    }
}

void playstat::on_bt_asst_clicked()
{
    if( is_game_ended() ){ return; }
    int last_action = m_store->GetLastAction();
    if( last_action == ifStore::t2_ok ||
        last_action == ifStore::t3_ok )
    {
        int pl = ask_player(players::author,tr(QT_TR_NOOP("who made the Assist?")));
        m_store->AddScore(ifStore::assist,pl);
        UpdateScoreboard(ifStore::assist,m_store->GetScore(ifStore::assist));
        UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
    }else{
        QString text;
        text = tr(QT_TR_NOOP("Previous action is not an FG"));
        QMessageBox msgBox;
        msgBox.setText(text);
        msgBox.exec();
    }
}

void playstat::on_bt_steal_ok_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who made the steal?")),false,true);
    m_store->AddScore(ifStore::stl_done,pl);
    UpdateScoreboard(ifStore::stl_done,m_store->GetScore(ifStore::stl_done));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_steal_ko_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who lost the ball?")),false,true);
    m_store->AddScore(ifStore::stl_recv,pl);
    UpdateScoreboard(ifStore::stl_recv,m_store->GetScore(ifStore::stl_recv));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_blocks_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who made the block?")));
    m_store->AddScore(ifStore::blocks_done,pl);
    UpdateScoreboard(ifStore::blocks_done,m_store->GetScore(ifStore::blocks_done));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_reb_def_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who made DREB?")),false,true);
    m_store->AddScore(ifStore::rb_def,pl);
    UpdateScoreboard(ifStore::rb_def,m_store->GetScore(ifStore::rb_def));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_fauls_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::faul,tr(QT_TR_NOOP("who received\nor made the faul ?")),true); // con true si avrebbe l'uscita
    if( pl > -1 && pl < MAX_PLAYERS ){
        m_fauls->set_player(pl);
        m_fauls->FaulDetected();
        m_fauls->showNormal();
    }
}

void playstat::on_bt_undo_clicked()
{
    if( is_game_ended() ){ return; }
    QMessageBox msgBox;
    QString text;
    T_ActionDesc tmp;
    m_store->init_T_ActionDesc(tmp);
     // tmp = m_store->Undo();
     tmp = m_store->GetActionForUndo();
     if( tmp.item >= 0 ){
         if( tmp.item == ifStore::actual_quarter ){
            text = tr("Undo: End of period ?");
         }else{
            QString maglia = QString::number(m_players->get_field_shirt(tmp.player_index));
            if( maglia == "-1" ){
              text = tr("Undo: ") + Azione(tmp) + "?";
            }else{
              text = tr("Undo: ") + Azione(tmp) + tr(" player ") + maglia + "?";
            }
         }
         msgBox.setText(text);
         msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Ok);
         int ret = msgBox.exec();
         if( ret == QMessageBox::Ok){
             m_store->Undo();
             //if( tmp.item == ifStore::subst_in ){
             //    m_store->Undo(); // se annullo sostituzione ....
             //}
             UpdateScoreboard(tmp.item,m_store->GetScore(tmp.item));
             if( tmp.item == ifStore::t1_ok ){
               UpdateScoreboard(ifStore::t1_ko,m_store->GetScore(ifStore::t1_ko));
             }else if( tmp.item == ifStore::t2_ok ){
               UpdateScoreboard(ifStore::t2_ko,m_store->GetScore(ifStore::t2_ko));
             }else if( tmp.item == ifStore::t3_ok ){
               UpdateScoreboard(ifStore::t3_ko,m_store->GetScore(ifStore::t3_ko));
             }else if( tmp.item == ifStore::actual_quarter ){
               UpdateScoreboard(ifStore::actual_quarter,tmp.quarter);
               m_game_data->m_actual_quarter -= 1;
             }
             UpdateScoreboard(ifStore::points,m_store->GetScore(ifStore::points));
             UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
             UpdateScoreboard(ifStore::actual_quarter,m_game_data->m_actual_quarter);
         }
     }else{
        text = tr(QT_TR_NOOP("Nothing to undo"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
     }
}

int playstat::ask_player(int auth_mode, QString msg, bool abort_allowed, bool team_allowed)
{
    m_players->set_author_mode(auth_mode,abort_allowed,team_allowed);
    m_players->update();
    this->hide();
    if( msg != "" ){
        m_players->set_text(msg);
    }else{
        if( auth_mode ){
            m_players->set_text(tr(QT_TR_NOOP("Select player")));
        }else{
            m_players->set_text(tr(QT_TR_NOOP("Select player then 'close'")));
        }
    }
    m_players->showNormal();
    if ( m_players->exec() == QDialog::Accepted ) {
    }
    int pl = -1;
    if( auth_mode ){
        pl = m_players->get_author();
    }else{
        pl = m_players->get_player_no();
    }
    this->showNormal();
    return pl;
}

void playstat::on_bt_blk_recv_clicked()
{
    if( is_game_ended() ){ return; }
    int pl = ask_player(players::author,tr(QT_TR_NOOP("who received block?")));
    m_store->AddScore(ifStore::blocks_recv,pl);
    UpdateScoreboard(ifStore::blocks_recv,m_store->GetScore(ifStore::blocks_recv));
    UpdateScoreboard(ifStore::val,m_store->GetScore(ifStore::val));
}

void playstat::on_bt_q_indicator_clicked()
{
  QString text;
  QMessageBox msgBox;
  bool store_time = true, parity = false, finished = false;

  if( is_game_ended() ){ return; }
  int my_pts = m_store->GetScore(ifStore::points);
  int oth_pts = m_store->GetScore(ifStore::oth_points);
  if( my_pts == oth_pts ){ parity = true; }
#if 0
  if( m_game_data->m_actual_quarter >= 4 ){
      text = tr(QT_TR_NOOP("Is game finished ?"));
      if( m_game_data->m_actual_quarter == 4 ){
          text += tr(QT_TR_NOOP(" Press No for overtime"));
      }
  }else{
      text = tr(QT_TR_NOOP("Is quarter finished ?"));
  }
#endif
  text = tr(QT_TR_NOOP("Is period finished ?"));
  msgBox.setText(text);
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::Yes);
  int ret = msgBox.exec();
  if( ret == QMessageBox::Yes ){
    finished = true;
  }

  if( finished )
  {
    if( m_game_data->m_actual_quarter < 4 ){
      m_store->AddScore(ifStore::actual_quarter,-1,0,0,m_game_data->m_actual_quarter);
      m_game_data->m_actual_quarter += 1;
      m_game_data->m_banner_time.m_min = m_game_data->m_quarter_duration;
      m_game_data->m_banner_time.m_sec = 0;
      m_store->ResetQuarterFauls();
      UpdateScoreboard(ifStore::my_fauls,m_store->GetScore(ifStore::my_fauls));
      UpdateScoreboard(ifStore::oth_fauls,m_store->GetScore(ifStore::oth_fauls));
    }else{
      if( parity ){
        // supplementare
        m_store->AddScore(ifStore::actual_quarter,-1,0,0,m_game_data->m_actual_quarter);
        m_game_data->m_actual_quarter += 1;
        m_game_data->m_banner_time.m_min = m_game_data->m_overtime_duration;
        m_game_data->m_banner_time.m_sec = 0;
      }else{
        m_store->AddScore(ifStore::actual_quarter,-1,0,0,m_game_data->m_actual_quarter);
        m_game_data->game_end = true;
      }
    }
  }else{
    // si considera che abbia premuto per errore
    store_time = false;
  }
  if( store_time ){
    m_players->EndOfPeriod();
    UpdateScoreboard(ifStore::actual_quarter,m_game_data->m_actual_quarter);
  }
}

bool playstat::is_game_ended()
{
    return m_game_data->game_end;
}

QString playstat::Azione(T_ActionDesc &code)
{
    QString text, add = "";

    if( code.item >= (sizeof(playstat::azioni) / sizeof(char *))){
        text = "???";
    }else{
        text = tr(azioni[code.item]);
        if( code.item == ifStore::fl_done || code.item == ifStore::fl_recv ){
            if( code.param > 0 ){
                if( code.param >= 1 && code.param <= 3 ){
                    add.sprintf(" (P%d)",code.param);
                }
            }else{
                if( code.param == TECH_FAUL ){
                    add = " (P2) / T";
                }else if( code.param == ANTISP_FAUL ){
                    add = " (P2) / A";
                }else{
                    add = " (P)";
                }
            }
            text += add;
        }
    }
    return text;
}

void playstat::on_bt_oth_points_clicked()
{
    m_oth_pt->showNormal();
}
