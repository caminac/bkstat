#include "players.h"
#include "ui_players.h"
#include "ifStore.h"
#include <qmessagebox.h>

#define SLIDER_UNIT  10
#define SLIDER_PARTS 6
#define MIN_PARTS    (SLIDER_UNIT * SLIDER_PARTS)

QPushButton *players::in_buttons[N_FIELD];
QPushButton *players::out_buttons[MAX_SUBST];
QPushButton *players::extra_buttons[EXTRA_FOULS];

QString colori[] = {
    QString("color: rgb(0, 0, 0);\nbackground-color: rgb(85, 255, 127);"),
    QString("color: rgb(0, 0, 255);\nbackground-color: rgb(253, 253, 193);"),
    QString("color: rgb(0, 0, 255);\nbackground-color: rgb(240, 240, 60);"),
    QString("color: rgb(0, 0, 255);\nbackground-color: rgb(252, 205, 25);"),
    QString("background-color: rgb(255, 115, 0);"),
    QString("background-color: rgb(255, 0, 0);"),
    QString("background-color: rgb(255, 0, 0);"),
};

players::players(ifStore *st, std::vector<T_PlayerData> *players_registry, int field[], int substitutes[], T_GameData *game_data, PlayTimeData *time_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::players)
{
    started = false;
    init_done = false;
    ui->setupUi(this);
    //ui->in_seconds->setSingleStep(5);
    ui->in_seconds->setWrapping(true);
    ui->in_minutes->setWrapping(true);

    m_store = st;
    registry = players_registry;
    m_field = field;
    m_subst = substitutes;
    m_game_data = game_data;
    m_out = -1;
    m_in = -1;
    m_author_mode = players::none;
    banner_has_changed = false;
    is_quarter_init = true;
    m_time_data = time_data;
    in_buttons[0] = ui->bt_field1;
    in_buttons[1] = ui->bt_field2;
    in_buttons[2] = ui->bt_field3;
    in_buttons[3] = ui->bt_field4;
    in_buttons[4] = ui->bt_field5;

    out_buttons[0] = ui->bt_res_01;
    out_buttons[1] = ui->bt_res_02;
    out_buttons[2] = ui->bt_res_03;
    out_buttons[3] = ui->bt_res_04;
    out_buttons[4] = ui->bt_res_05;
    out_buttons[5] = ui->bt_res_06;
    out_buttons[6] = ui->bt_res_07;
    out_buttons[7] = ui->bt_res_08;
    out_buttons[8] = ui->bt_res_09;
    out_buttons[9] = ui->bt_res_10;

    extra_buttons[0] = ui->bt_f_none;
    extra_buttons[1] = ui->bt_f_coach;
    extra_buttons[2] = ui->bt_f_bench;

    m_intCurrentSlider = MIN_PARTS * m_game_data->m_banner_time.m_min;
    m_intPrevSlider = m_intCurrentSlider;
    m_iPrevMin = m_game_data->m_quarter_duration;
    m_iPrevSec = 0;
}

players::~players()
{
    delete ui;
}

int players::get_next_player(int current)
{
    unsigned int retv = current;
    if( retv == MAX_PLAYERS ){
      retv = 0;
    }else{
      ++retv;
      if( retv >= registry->size() ){
        retv = MAX_PLAYERS;
      }
    }
    return retv;
}

int players::get_prev_player(int current)
{
    int retv = current;
    if( retv == MAX_PLAYERS ){
      retv = registry->size() - 1;
    }else{
      --retv;
      if( retv < 0 ){
        retv = MAX_PLAYERS;
      }
    }
    return retv;
}

void players::on_bt_change_clicked()
{
  int limit = get_limit();
  if( !init_done ){
      init();
      init_done = true;
      is_quarter_init = true;
      ui->bt_close->setEnabled(true);
      if( m_author_mode == players::select_start_5 ){
          for( int i=0; i<N_FIELD; i++ ){ in_buttons[i]->setEnabled(true); }
          for( int i=0; i<limit; i++ ){ out_buttons[i]->setEnabled(true); }
      }
  }else{
     if( m_author_mode == players::substitution ||
         m_author_mode == players::select_start_5 )
     {
        if( m_author_mode == players::select_start_5 ){
            for( int i=0; i<N_FIELD; i++ ){ in_buttons[i]->setEnabled(true); }
            for( int i=0; i<limit; i++ ){ out_buttons[i]->setEnabled(true); }
        }
        if( can_change_a_player() ){
          if( m_out != -1 && m_in != -1 ){
            T_PlayerData in_p, out_p;
            int number_of_player_going_out, number_of_player_going_in;
            int index_player_going_out, index_player_going_in;
            index_player_going_out = m_field[m_out];
            index_player_going_in = m_subst[m_in];

            exchange_players(m_out,m_in);

            out_p = registry->at(index_player_going_out);
            number_of_player_going_out = out_p.number;
            in_p = registry->at(index_player_going_in);
            number_of_player_going_in = in_p.number;

            if( started ){
                GameTime banner = GetUpdatedBanner();
                m_game_data->m_banner_time = banner;
                m_store->AddScore(ifStore::subst_out,index_player_going_out,banner.m_min,banner.m_sec,m_game_data->m_actual_quarter);
                m_store->AddScore(ifStore::subst_in,index_player_going_in,banner.m_min,banner.m_sec,m_game_data->m_actual_quarter);
            }
            int falli_player_out, falli_player_in;
            falli_player_out = m_store->GetScore(ifStore::fl_done,index_player_going_out);
            falli_player_in = m_store->GetScore(ifStore::fl_done,index_player_going_in);

            set_button(in_buttons[m_out], number_of_player_going_in, falli_player_in);
            set_button(out_buttons[m_in], number_of_player_going_out, falli_player_out);

            in_buttons[m_out]->setChecked(false);
            out_buttons[m_in]->setChecked(false);

            m_out = -1;
            m_in = -1;
            order_by_shirt_number();
          }
        }
    }else{
      m_out = MAX_PLAYERS;
      this->hide();
    }
  }
}

void players::order_by_shirt_number()
{
  T_PlayerData  p;
  T_player_info info[5];
  int           i, j, idx_of_min, tmp, new_order[5];

  for( i=0; i<5; i++ ){
    info[i].index = m_field[i];
    p = registry->at(m_field[i]);
    info[i].shirt = p.number;
    info[i].fauls = m_store->GetScore(ifStore::fl_done,info[i].index);
    new_order[i] = i;
  }

  for( i=0; i<4; i++ ){
    idx_of_min = i;
    for( j=i+1; j<5; j++ ){
      if( info[new_order[j]].shirt < info[new_order[idx_of_min]].shirt ){
        idx_of_min = j;
      }
    }
    if( idx_of_min != i ){
      tmp = new_order[idx_of_min];
      new_order[idx_of_min] = new_order[i];
      new_order[i] = tmp;
    }
  }
  for( i=0; i<5; i++ ){
    set_button(in_buttons[i], info[new_order[i]].shirt, info[new_order[i]].fauls);
    m_field[i] = info[new_order[i]].index;
  }
}

void players::set_text(QString text)
{
    ui->lb_spiega->setText(text);
}

void players::on_bt_field1_clicked()
{
    change_sel_for_exit(m_out,0);
    if( m_author_mode == players::author ){ this->hide(); }
}

void players::on_bt_field2_clicked()
{
    change_sel_for_exit(m_out,1);
    if( m_author_mode == players::author ){ this->hide(); }
}

void players::on_bt_field3_clicked()
{
    change_sel_for_exit(m_out,2);
    if( m_author_mode == players::author ){ this->hide(); }
}

void players::on_bt_field4_clicked()
{
    change_sel_for_exit(m_out,3);
    if( m_author_mode == players::author ){ this->hide(); }
}

void players::on_bt_field5_clicked()
{
    change_sel_for_exit(m_out,4);
    if( m_author_mode == players::author ){ this->hide(); }
}

void players::on_bt_res_01_clicked()
{
    change_sel_for_enter(m_out,0);
}

void players::on_bt_res_02_clicked()
{
    change_sel_for_enter(m_out,1);
}

void players::on_bt_res_03_clicked()
{
    change_sel_for_enter(m_out,2);
}

void players::on_bt_res_04_clicked()
{
    change_sel_for_enter(m_out,3);
}

void players::on_bt_res_05_clicked()
{
    change_sel_for_enter(m_out,4);
}

void players::on_bt_res_06_clicked()
{
    change_sel_for_enter(m_out,5);
}

void players::on_bt_res_07_clicked()
{
    change_sel_for_enter(m_out,6);
}

void players::on_bt_res_08_clicked()
{
    change_sel_for_enter(m_out,7);
}

void players::on_bt_res_09_clicked()
{
    change_sel_for_enter(m_out,8);
}

void players::on_bt_res_10_clicked()
{
    change_sel_for_enter(m_out,9);
}

void players::change_sel_for_exit(int from, int to)
{
    if( from != -1 ){
        in_buttons[from]->setChecked(false);
    }
    m_out = to;
    show_in_out_players();
}

void players::change_sel_for_enter(int from, int to)
{
    if( from != -1 ){
        out_buttons[from]->setChecked(false);
    }
    m_in = to;
    show_in_out_players();
}

void players::show_in_out_players()
{
  QString txt = "";
  int out_shirt = 0, in_shirt = 0;
  if( m_out > -1 ){
    out_shirt = get_field_shirt(m_field[m_out]);
  }
  if( m_in > -1 ){
    in_shirt  = get_field_shirt(m_subst[m_in]);
  }
  if( out_shirt > 0 ){
    txt = QString::number(out_shirt, 10);
  }
  txt += "<->";
  if( in_shirt > 0 ){
    txt += QString::number(in_shirt, 10);
  }
  ui->bt_change->setText(txt);
}

int players::get_author()
{
    int player = -1;
    if( m_out >= 0 && m_out < MAX_PLAYERS ){
        player = m_field[m_out];
    }else{
        player = MAX_PLAYERS;
    }
    return player;
}

int players::get_player_no()
{
    int pl = 0;
    if( m_out > -1 ){
        pl = m_field[m_out];
    }else if( m_in >= -1 ){
        pl = m_subst[m_in];
    }
    return pl;
}

void players::init()
{
    T_PlayerData tmp;
    int i, limit = get_limit();
    if( !started && registry->size() >= N_FIELD ){
        for( i=0; i<N_FIELD; i++ ){
            m_field[i] = i;
            tmp = registry->at(i);
            in_buttons[i]->setText(QString::number(tmp.number, 10));
        }
        m_intCurrentSlider = m_game_data->m_quarter_duration * MIN_PARTS;
        ui->time_slider->setMaximum(m_intCurrentSlider);
    }
    for( i=0; i<limit; i++ ){
        m_subst[i] = i+N_FIELD;
        tmp = registry->at(i+N_FIELD);
        out_buttons[i]->setText(QString::number(tmp.number, 10));
    }
    if( limit < MAX_SUBST ){
        for( i=limit; i<MAX_SUBST; i++ ){
            m_subst[i] = -1;
            out_buttons[i]->setVisible(false);
        }
    }
}

void players::on_bt_close_clicked()
{
    bool done = true;
    if( !started ){
        int index_in, i;
        GameTime init_time;
        init_time.m_min = m_game_data->m_quarter_duration;
        init_time.m_sec = 0;
        m_game_data->game_started = true;
        for( i=0; i<N_FIELD; i++){
            index_in = m_field[i];
            if( index_in == -1 ){
              done = false;
            }else{
              m_store->AddScore(ifStore::starting_five,index_in);
              m_game_data->m_start5[i] = index_in;
            }
        }
        for( i=0; i<MAX_SUBST; i++){
            index_in = m_subst[i];
            if( index_in != -1 ){
              m_store->AddScore(ifStore::start_substitute,index_in);
            }
        }
        if( done ){ started = true; }
    }
    if( m_out != -1 ){
        in_buttons[m_out]->setChecked(false);
    }
    if( done ){
      this->hide();
      is_quarter_init = false;
    }
}

void players::set_author_mode(int author_mode, bool abort_allowed, bool team_allowed)
{
    m_author_mode = author_mode;
    m_out = -1;
    m_in = -1;
    bool in = false, out_enabled = false, out_visible = true, extra = false, tmout = false, subst = false;
    if( author_mode == players::author ){
        in = true;
        out_visible = false;
    }else if( author_mode == players::faul ){
        in = true;
        extra = true;
        tmout = true;
        out_visible = false;
    }else if( author_mode == players::substitution ){
        in = true;
        out_enabled = true;
        tmout = true;
        subst = true;
    }else if( author_mode == players::select_start_5 ){
        in = false;
        out_enabled = false;
    }
    for( int i=0; i<N_FIELD; i++ ){ in_buttons[i]->setEnabled(in); }
    for( int i=0; i<MAX_SUBST; i++ ){ out_buttons[i]->setEnabled(out_enabled); }
    for( int i=0; i<MAX_SUBST; i++ ){ out_buttons[i]->setVisible(out_visible); }
    for( int i=0; i<EXTRA_FOULS; i++ ){ extra_buttons[i]->setEnabled(extra); }
    if( abort_allowed ){
        ui->bt_close->setEnabled(true);
    }else{
        ui->bt_close->setEnabled(false);
    }
    ui->bt_change->setEnabled(subst);
    ui->bt_my_timeout->setEnabled(tmout);
    ui->bt_oth_tmout->setEnabled(tmout);
    if( author_mode == players::author ){
      if( team_allowed ){
        ui->bt_change->setText(tr(QT_TR_NOOP("team")));
        ui->bt_change->setEnabled(true);
      }
    }
    if( author_mode == players::select_start_5 ){
        ui->bt_change->setText("<->");
        ui->bt_change->setEnabled(true);
    }
}

void players::set_enter_time(int in_index, GameTime enter_time)
{
    int gap = m_store->get_current_gap();
    m_time_data->SetEnterTime(in_index,enter_time,gap);
}

void players::showEvent( QShowEvent * event )
{
  banner_has_changed = false;
  m_intPrevSlider = m_intCurrentSlider;
  ui->in_minutes->setValue(m_game_data->m_banner_time.m_min);
  ui->in_seconds->setValue(m_game_data->m_banner_time.m_sec);
  ui->time_slider->setSliderPosition(m_intCurrentSlider);
  if( !started ){
      ui->in_minutes->setEnabled(false);
      ui->in_seconds->setEnabled(false);
      ui->time_slider->setEnabled(false);
  }else{
      ui->in_minutes->setEnabled(true);
      ui->in_seconds->setEnabled(true);
      ui->time_slider->setEnabled(true);
      refresh_faul_state();
  }
}

GameTime players::GetUpdatedBanner()
{
  GameTime t;
  t.m_min = ui->in_minutes->value();
  t.m_sec = ui->in_seconds->value();
  return t;
}

void players::EndOfPeriod()
{
  GameTime t;
  GameTime pre(m_game_data->m_quarter_duration,0);
  if( m_game_data->m_actual_quarter > 4 ){
    pre.m_min = m_game_data->m_overtime_duration;
  }
  int i, index_pl, gap;
  gap = m_store->get_current_gap();
  for( i=0; i<N_FIELD; i++ ){
    index_pl = m_field[i];
    m_time_data->AddPlayedTime(index_pl,t,gap);
    m_time_data->SetEnterTime(index_pl,pre,gap);
  }
  m_game_data->m_banner_time = pre;
  m_intCurrentSlider = pre.m_min * MIN_PARTS;
  m_intPrevSlider = m_intCurrentSlider;
  ui->time_slider->setMaximum(m_intCurrentSlider);
  ui->time_slider->setSliderPosition(m_intCurrentSlider);
  ui->in_seconds->setValue(0);
  ui->in_minutes->setValue(pre.m_min);
  m_iPrevMin = pre.m_min;
  m_iPrevSec = 0;
  is_quarter_init = true;
}

void players::on_in_minutes_valueChanged(int arg1)
{
  if( started ){
    int newval = arg1 * MIN_PARTS + SLIDER_UNIT * ui->in_seconds->value();
    if( IsnewTimeAcceptable(newval,m_intPrevSlider) ){
      banner_has_changed = true;
      m_intCurrentSlider = newval;
      //ui->time_slider->setSliderPosition(m_intCurrentSlider);
      banner_has_changed = true;
    }else{
      QString msg = tr(QT_TR_NOOP("Time not acceptable"));
      QMessageBox msgBox;
      msgBox.setText(msg);
      msgBox.setStandardButtons(QMessageBox::Ok);
      // msgBox.exec();
    }
  }
}

void players::on_in_seconds_valueChanged(int arg1)
{
  if( started ){
    int newval;
    int min = ui->in_minutes->value();
    if( arg1 == 59 && m_iPrevSec == 0){
        if( min > 0 ){
            min = min - 1;
            ui->in_minutes->setValue(min);
        }
    }else if( arg1 == 0 && m_iPrevSec == 59){
        if( min < m_game_data->m_banner_time.m_min ){
            min = min + 1;
            ui->in_minutes->setValue(min);
        }
    }
    m_iPrevSec = arg1;
    newval = arg1 + MIN_PARTS * min;
    if( IsnewTimeAcceptable(newval,m_intPrevSlider) ){
      banner_has_changed = true;
      m_intCurrentSlider = newval;
      //ui->time_slider->setSliderPosition(m_intCurrentSlider);
      banner_has_changed = true;
    }else{
      // altrimenti potevo fare tempi > 10:00
      if( ui->in_minutes->value() == m_game_data->m_banner_time.m_min ){
        ui->in_seconds->setValue(0);
      }else{
        QString msg = tr(QT_TR_NOOP("Time not acceptable"));
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Ok);
        //msgBox.exec();
      }
    }
  }
}

void players::on_time_slider_sliderMoved(int position)
{
  int min, sec, slider;
  slider = ui->time_slider->sliderPosition();
  if( IsnewTimeAcceptable(slider,m_intPrevSlider) ){
      m_intCurrentSlider = slider;
      min = m_intCurrentSlider/MIN_PARTS;
      sec = SLIDER_UNIT * ((m_intCurrentSlider - min*MIN_PARTS) / SLIDER_UNIT);
      m_intCurrentSlider = min * MIN_PARTS + sec;
      ui->in_minutes->setValue(min);
      ui->in_seconds->setValue(sec);
  }
}

bool players::IsnewTimeAcceptable(int newtime, int prevtime)
{
  if( newtime <= prevtime ){
    return true;
  }else{
    return false;
  }
}

void players::refresh_faul_state()
{
    T_PlayerData tmp;
    int i, limit, falli, player_idx;

    for( i=0; i<N_FIELD; i++ ){
      player_idx = m_field[i];
      tmp = registry->at(player_idx);
      falli = m_store->GetScore(ifStore::fl_done,player_idx);
      set_button(in_buttons[i], tmp.number, falli);
    }
    limit = (registry->size() - N_FIELD);
    for( i=0; i<limit; i++ ){
        player_idx = m_subst[i];
        tmp = registry->at(player_idx);
        falli = m_store->GetScore(ifStore::fl_done,player_idx);
        set_button(out_buttons[i], tmp.number, falli);
    }
}

void players::set_button(QPushButton *button, int maglia, int falli)
{
    QString txt;
    txt = QString::number(maglia, 10) + "/" + QString::number(falli, 10);
    //out_buttons[i]->setText(QString::number(tmp.number, 10));
    if( falli >= 0 && falli <= 5 ){
        button->setStyleSheet(colori[falli]);
    }
    button->setText(txt);
}

void players::exchange_players(int out, int in)
{
    if( out == -1 || in == -1 ){
        QString msg = tr(QT_TR_NOOP("bad index in edit time"));
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    int index_player_going_out, index_player_going_in;
    index_player_going_out = m_field[out];
    index_player_going_in = m_subst[in];
    m_field[out] = index_player_going_in;
    m_subst[in] = index_player_going_out;
    ui->bt_change->setText("<->");
    // !!! qui ci vuole set played e ... ?
}

void players::set_field_player(int role, int pl_index)
{
    if( role >= 0 && role < N_FIELD ){
        m_field[role] = pl_index;
    }
}

int players::lookup_field_pos_by_index(int pl_index)
{
    int role = -1, i;
    for( i=0; i<N_FIELD; i++ ){
        if( m_field[i] == pl_index ){
            role = i;
            break;
        }
    }
    return role;
}

int players::lookup_subst_pos_by_index(int pl_index)
{
    int role = -1, i;
    for( i=0; i<MAX_SUBST; i++ ){
        if( m_subst[i] == pl_index ){
            role = i;
            break;
        }
    }
    return role;
}

void players::set_subst_player(int role, int pl_index)
{
    if( role >= 0 && role < MAX_SUBST ){
        m_subst[role] = pl_index;
    }
}

void players::on_bt_my_timeout_clicked()
{
  if( init_done ){
    if( can_call_timeout() ){
      QString text;
      QMessageBox msgBox;
      text = tr(QT_TR_NOOP("Confirm timeout ?"));
      msgBox.setText(text);
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Ok);
      int ret = msgBox.exec();
      if( ret == QMessageBox::Ok){
          GameTime banner = GetUpdatedBanner();
          m_game_data->m_banner_time = banner;
          m_store->AddScore(ifStore::my_timeout,0,banner.m_min,banner.m_sec,m_game_data->m_actual_quarter);
      }
      this->hide();
    }
  }
}

void players::on_bt_oth_tmout_clicked()
{
  if( init_done ){
    if( can_call_timeout() ){
      QString text;
      QMessageBox msgBox;
      text = tr(QT_TR_NOOP("Confirm other team timeout ?"));
      msgBox.setText(text);
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Ok);
      int ret = msgBox.exec();
      if( ret == QMessageBox::Ok){
        GameTime banner = GetUpdatedBanner();
        m_game_data->m_banner_time = banner;
        m_store->AddScore(ifStore::oth_timeout,0,banner.m_min,banner.m_sec,m_game_data->m_actual_quarter);
      }
      this->hide();
    }
  }
}

bool players::can_change_a_player()
{
  bool rv = false;
  if( banner_has_changed ||
      is_quarter_init ||
      !(m_game_data->game_started) ){
    rv = true;
  }else{
    QString msg = tr(QT_TR_NOOP("Edit time"));
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
  }
  return rv;
}

bool players::can_call_timeout()
{
  bool rv = false;
  if( m_game_data->game_started ){
    if( banner_has_changed ){
      rv = true;
    }else{
      QString msg = tr(QT_TR_NOOP("Edit time"));
      QMessageBox msgBox;
      msgBox.setText(msg);
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
    }
  }
  return rv;
}
