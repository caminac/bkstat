#include <QMessagebox>
#include <QFileDialog>
#include <QInputDialog>
#include <QObject>
#include <QFile>
#include <QStringList>
#include <QTextCodec>
#include <QString>
#include <vector>
#include "scorer.h"
#include "players.h"
#include "setup.h"
#include "Utility.h"
#include "info.h"

// indice MAX_PLAYERS per coach / team
int score[ifStore::last_button][MAX_PLAYERS+1][MAX_QTR];    // una riga in + per falli a coach/team
int throws_on_fauls[MAX_PLAYERS+1][2][4];                   // player/{DONE|REC}/{P0|P1|P2|P3}
int score2[scorer::_last_internal_item];

std::vector<T_ActionDesc> cmd_queue;

scorer::scorer(T_GameData  *m_game_data, PlayTimeData *time_data)
{
    scorer();
    m_game = m_game_data;
    m_last_action = -1;
    m_time_data = time_data;
}

int scorer::GetLastAction()
{
    return m_last_action;
}

scorer::scorer()
{
    m_viewer = 0;
    m_quarter = 0;
};

scorer::~scorer()
{
}

void scorer::Reset()
{
    int i;
    for( i=0; i<ifStore::last_button; i++ ){
        score[i][0][0] = 0;
    }
    for( i=0; i<scorer::_last_internal_item; i++ ){
        score2[i] = 0;
    }
}

void scorer::ResetQuarterFauls()
{
    score2[scorer::_my_fauls] = 0;
    score2[scorer::_oth_fauls] = 0;
}

void scorer::AddScore(int item, int player_index, int team_index, int p1, int p2, int q)
{
  m_last_action = item;
  if( item == ifStore::subst_out ||
      item == ifStore::subst_in )
  {
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    tmp.item = item;
    tmp.player_index = player_index;
    tmp.min = p1;
    tmp.sec = p2;
    if( q == 0 ){
        tmp.quarter = m_game->m_actual_quarter;
    }else{
        tmp.quarter = q;
    }
    cmd_queue.push_back(tmp);

    if( item == ifStore::subst_out ){
      GameTime exit_time;
      exit_time.m_min = p1;
      exit_time.m_sec = p2;
      m_time_data->AddPlayedTime(player_index,exit_time,get_current_gap());
    }else if( item == ifStore::subst_in ){
      GameTime enter_time;
      enter_time.m_min = p1;
      enter_time.m_sec = p2;
      m_time_data->SetEnterTime(player_index,enter_time,get_current_gap());
    }
  }else if( item == ifStore::actual_quarter ){
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    tmp.item = item;
    tmp.player_index = player_index;
    tmp.min = p1;
    tmp.sec = p2;
    tmp.quarter = q; // m_game->m_actual_quarter;
    cmd_queue.push_back(tmp);
  }else if( item == ifStore::starting_five ){
    GameTime init_time;
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    tmp.player_index = player_index;
    init_time.m_min = m_game->m_quarter_duration;
    init_time.m_sec = 0;
    tmp.item = item;
    tmp.player_index = player_index;
    cmd_queue.push_back(tmp);
    m_players->set_enter_time(player_index,init_time);
  }else if( item == ifStore::my_timeout || item == ifStore::oth_timeout ){
      T_ActionDesc tmp;
      this->init_T_ActionDesc(tmp);
      tmp.item = item;
      tmp.player_index = -1;
      tmp.min = p1;
      tmp.sec = p2;
      if( q == 0 ){
          tmp.quarter = m_game->m_actual_quarter;
      }else{
          tmp.quarter = q;
      }
      cmd_queue.push_back(tmp);
  }else if( item == ifStore::fl_done || item == ifStore::fl_recv ){ 
    SetScore(item, player_index, team_index, 1, p1, p2);
  }else{
    SetScore(item, player_index, team_index, 1);
  }
}

void scorer::SetScore(int item, int player_index, int team_index, int action_sign, int param, int param2)
{
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    bool upd_pts = false;
    tmp.item = item;
    tmp.player_index = player_index;
    bool exit = false;

    if( item == ifStore::fl_done || item == ifStore::fl_recv ){
      int ft = 0, faul_type = F_RECV;
      int faul_count = 1;
      tmp.param = param;

      if( item == ifStore::fl_done ){
        if( param2 != -1 ){
            faul_type = F_RECV;
        }else{
            faul_type = F_DONE;
        }
      }
      if( player_index == COACH_INDEX || player_index == BENCH_INDEX ){
          faul_count = 0;
      }
      if( param2 == COACH_INDEX || param2 == BENCH_INDEX ){
          faul_count = 0;
      }
      throws_on_fauls[player_index][faul_type][ft]++;
      if( item == ifStore::fl_done ){
        score2[scorer::_my_fauls] += faul_count;
      }else{
        score2[scorer::_oth_fauls] += faul_count;
      }
    }
    // ! passo di qui anche in caso di undo (e non devo registrare)
    if( action_sign > 0 ){
        cmd_queue.push_back(tmp);
    }
    if( exit ){
       return;
    }
    if( item >= 0 && item < ifStore::last_button ){
        if( item == ifStore::actual_quarter ){
        }else{
            score[item][player_index][0] += action_sign;
            switch(item){
                case ifStore::t1_ok:
                    upd_pts = true;
                    if( team_index == ifStore::team_A ){
                        score[ifStore::t1_ko][player_index][0] += action_sign;
                    }else{
                        score2[scorer::_oth_t1] += action_sign;
                    }
                    break;
                case ifStore::t2_ok:
                    upd_pts = true;
                    if( team_index == ifStore::team_A ){
                        score[ifStore::t2_ko][player_index][0] += action_sign;
                    }else{
                        score2[scorer::_oth_t2] += action_sign;
                    }
                    break;
                case ifStore::t3_ok:
                    upd_pts = true;
                    if( team_index == ifStore::team_A ){
                        score[ifStore::t3_ko][player_index][0] += action_sign;
                    }else{
                        score2[scorer::_oth_t3] += action_sign;
                    }
                    break;
            }            
        }
    }else if( item == ifStore::my_timeout ||
              item == ifStore::oth_timeout ){
        // my_fauls,oth_fauls,oth_points,
    }else{
        QMessageBox msgBox;
        msgBox.setText("SetScore: item >= ifStore::last_button");
        msgBox.exec();
    }
}

void scorer::SetViewer(ifViewer *v)
{
    m_viewer = v;
}

int scorer::GetScore(int item)
{
    int i, val = 0;
    if( item > ifStore::last_button ){
        switch( item ){
            case ifStore::oth_t1:
            val = score2[scorer::_oth_t1];
            break;
            case ifStore::oth_t2:
            val = score2[scorer::_oth_t2];
            break;
            case ifStore::oth_t3:
            val = score2[scorer::_oth_t3];
            break;
            case ifStore::my_fauls:
            val = score2[scorer::_my_fauls];
            break;
            case ifStore::oth_fauls:
            val = score2[scorer::_oth_fauls];
            break;
            case ifStore::oth_points:
            val = 3*score2[scorer::_oth_t3] + 2*score2[scorer::_oth_t2] + score2[scorer::_oth_t1];
            break;
        }
    }else{
        for( i=0; i<=MAX_PLAYERS; i++ ){
            val += GetScore(item, i);
        }
    }
    return val;
}

int scorer::GetScore(int item, int player_index, int team_index)
{
    int val = score[item][player_index][0];
    if( item == ifStore::points ){
        val = score[ifStore::t1_ok][player_index][0] + 2*score[ifStore::t2_ok][player_index][0] + 3*score[ifStore::t3_ok][player_index][0];
    }else if( item == ifStore::val ){
        val = score[ifStore::t1_ok][player_index][0] + 2*score[ifStore::t2_ok][player_index][0] + 3*score[ifStore::t3_ok][player_index][0];
        val -= (score[ifStore::t1_ko][player_index][0] - score[ifStore::t1_ok][player_index][0]);
        val -= (score[ifStore::t2_ko][player_index][0] - score[ifStore::t2_ok][player_index][0]);
        val -= (score[ifStore::t3_ko][player_index][0] - score[ifStore::t3_ok][player_index][0]);

        val += score[ifStore::rb_atk][player_index][0];
        val += score[ifStore::rb_def][player_index][0];

        val += score[ifStore::fl_recv][player_index][0];
        val -= score[ifStore::fl_done][player_index][0];

        val += score[ifStore::stl_done][player_index][0];
        val -= score[ifStore::stl_recv][player_index][0];

        val += score[ifStore::assist][player_index][0];
        val += score[ifStore::blocks_done][player_index][0];

        val -= score[ifStore::blocks_recv][player_index][0];
    }
    return val;
}

// per ora la fine del quarto non supporta l'undo
T_ActionDesc scorer::GetActionForUndo()
{
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    if( !cmd_queue.empty() ){
        tmp = cmd_queue.back();
        // azioni non annullabili
        if( tmp.item == ifStore::starting_five
            || tmp.item == ifStore::subst_in
            || tmp.item == ifStore::subst_out
            || tmp.item == ifStore::actual_quarter
           )
        {
            tmp.item = -1;
            tmp.player_index = -1;
        }
    }
    return tmp;
}

T_ActionDesc scorer::Undo()
{
    T_ActionDesc tmp;
    this->init_T_ActionDesc(tmp);
    if( !cmd_queue.empty() ){
        tmp = cmd_queue.back();
        cmd_queue.pop_back();
        SetScore(tmp.item, tmp.player_index, tmp.team_index, -1);
        // ripristina la penultima azione
        tmp = cmd_queue.back();
        if( tmp.item != ifStore::starting_five ){
            m_last_action = tmp.item;
        }
    }
    return tmp;
}

QString scorer::get_perc( int item1, int item2, int player_index, int team_index )
{
    QString str;
    int v1, v2;
    float perc, sum;
    v1 = GetScore(item1,player_index);
    v2 = GetScore(item2,player_index);
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

QString scorer::get_perc( int val1, int tot )
{
    QString str;
    float perc, sum = tot;
    if( val1 > 0 ){
        perc = (float)(val1 / sum);
        perc *= 100;
        str.sprintf("%.1f %%",perc);
    }else{
        str = "-.- %";
    }
    return str;
}

void scorer::store_match(QFile &data)
{
    unsigned int n;
    T_ActionDesc  tmp;
    QTextStream out(&data);
    for( n=0; n< cmd_queue.size(); n++ ){
        tmp = cmd_queue.at(n);
        if( tmp.item == ifStore::subst_in ){
            out << "A" << tmp.item << "," << tmp.player_index << "," << tmp.min << "," << tmp.sec << "," << tmp.quarter << "\n";
        }else if( tmp.item == ifStore::subst_out ){
            out << "A" << tmp.item << "," << tmp.player_index << "," << tmp.min << "," << tmp.sec << "," << tmp.quarter << "\n";
        }else if( tmp.item == ifStore::my_timeout || tmp.item == ifStore::oth_timeout ){
            out << "A" << tmp.item << "," << tmp.player_index << "," << tmp.min << "," << tmp.sec << "," << tmp.quarter << "\n";
        }else if( tmp.item == ifStore::fl_done || tmp.item == ifStore::fl_recv ){
            out << "A" << tmp.item << "," << tmp.player_index << "," << tmp.param << "\n";
        }else if( tmp.item == ifStore::actual_quarter ){
            out << "A" << tmp.item << "," << tmp.quarter << "\n";
        }else{
            out << "A" << tmp.item << "," << tmp.player_index << "\n";
        }
    }
}

void scorer::store_pbp(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry)
{
    int           our_pts = 0, oth_pts = 0;
    QString       base, text;
    unsigned int n, actions;
    T_ActionDesc  tmp;
    T_PlayerData  player;
    QTextStream out(&data);
    actions = cmd_queue.size();
    for( n=0; n<actions; n++ ){
        tmp = cmd_queue.at(n);
        if( tmp.player_index >= 0 && tmp.player_index < MAX_PLAYERS ){
          player = players_registry->at(tmp.player_index);
        }else if( tmp.player_index == MAX_PLAYERS ){
          player.name = "?-1";
        }else{
          player.name = "?-2";
        }
        if( tmp.item == ifStore::actual_quarter ){
            if( tmp.quarter > 4 ){
                text = tr(QT_TR_NOOP("End of Overtime "));
                out << text << (tmp.quarter - 4) << "\n";
            }else{
                text = scoreboard->Azione(tmp);
                //QTextCodec* codec = QTextCodec::codecForName("ISO 8859-5");
                out << text << " " << tmp.quarter << "\n";
            }
            if( n == actions-1 ){
                text = tr(QT_TR_NOOP("End of Game"));
                out << text << "\n";
            }
        }else if( tmp.item == ifStore::subst_in || tmp.item == ifStore::subst_out ){
            out << scoreboard->Azione(tmp) << "," << player.name << "#" << player.number;
            if( tmp.quarter <= 4 ){
                out << ",Q" << tmp.quarter;
            }else{
                out << ",OT" << (tmp.quarter - 4);
            }
            QString time;
            time.sprintf("%02d:%02d",tmp.min,tmp.sec);
            out << "," << time << "\n";
        }else if( tmp.item == ifStore::fl_done ){
            text = scoreboard->Azione(tmp);
            if( tmp.param == TECH_FAUL ){
                out << tr(QT_TR_NOOP("TF done by coach or team")) << endl;
            }else{
                out << text << "," << player.name << "#" << player.number << "\n";
            }
        }else if( tmp.item == ifStore::fl_recv ){
            text = scoreboard->Azione(tmp);
            if( tmp.param == TECH_FAUL ){
                out << tr(QT_TR_NOOP("TF done by other coach or team")) << endl;
            }else{
                out << text << "," << player.name << "#" << player.number << "\n";
            }
        }else if( tmp.item == ifStore::oth_t1 || tmp.item == ifStore::oth_t2 || tmp.item == ifStore::oth_t3 ){
            if( tmp.item == ifStore::oth_t1 ){
                oth_pts += 1;
            }else if( tmp.item == ifStore::oth_t2 ){
                oth_pts += 2;
            }else if( tmp.item == ifStore::oth_t3 ){
                oth_pts += 3;
            }
            text = scoreboard->Azione(tmp);
            out << text << " (" << our_pts << "-" << oth_pts << ")\n";
        }else if( tmp.item == ifStore::t1_ok || tmp.item == ifStore::t2_ok || tmp.item == ifStore::t3_ok ){
            if( tmp.item == ifStore::t1_ok ){
                our_pts += 1;
            }else if( tmp.item == ifStore::t2_ok ){
                our_pts += 2;
            }else if( tmp.item == ifStore::t3_ok ){
                our_pts += 3;
            }
            text = scoreboard->Azione(tmp);
            out << text << "," << player.name << "#" << player.number << " (" << our_pts << "-" << oth_pts << ")\n";
        }else{
            text = scoreboard->Azione(tmp);
            out << text << "," << player.name << "#" << player.number << "\n";
        }
    }
}


void scorer::store_pbp_in_html(QFile &data, playstat *scoreboard, std::vector<T_PlayerData> *players_registry, QString charset)
{
    int           our_pts = 0, oth_pts = 0;
    QString       base, text, stile, full_player_name, my_team, oth_team;
    unsigned int n, actions;
    T_ActionDesc  tmp;
    T_PlayerData  player;
    QTextStream out(&data);
    actions = cmd_queue.size();
    QTextCodec* codec = QTextCodec::codecForName(charset.toLatin1());
    int           points[MAX_PLAYERS], f_done[MAX_PLAYERS], f_recv[MAX_PLAYERS], i;

    for( i=0; i<MAX_PLAYERS; i++ ){
        f_done[i] = 0;
        f_recv[i] = 0;
        points[i] = 0;
    }
    write_html_page_hdr(out,charset);
    write_stylesheet(out);

    out << "<TABLE width=\"50%\" class=\"cc\">" << endl;
    out << "<THEAD class=\"cc\">" << endl;
    out << "<TR>" << endl;
    my_team = m_game->this_team;
    //out << "<TD width=\"40%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Team 1"))) << "</P></TD>" << endl;
    out << "<TD width=\"40%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(my_team) << "</P></TD>" << endl;
    out << "<TD width=\"20%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Score"))) << "</P></TD>" << endl;
    //out << "<TD width=\"40%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Team 2"))) << "</P></TD>" << endl;
    oth_team = m_game->game_desc;
    out << "<TD width=\"40%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(oth_team) << "</P></TD>" << endl;
    out << "<TR>" << endl;
    out << "</TR>" << endl;
    out << "</THEAD>" << endl;
    out << "<TBODY>" << endl;

    for( n=0; n<actions; n++ ){
        if( n%2 == 0){
            stile = "pari";
        }else{
            stile = "dispari";
        }
        tmp = cmd_queue.at(n);
        if( tmp.player_index >= 0 && tmp.player_index < MAX_PLAYERS ){
          player = players_registry->at(tmp.player_index);
          full_player_name = codec->fromUnicode(player.name) + "#" + QString::number(player.number,10);
        }else if( tmp.player_index == MAX_PLAYERS ){
          player.name = tr(QT_TR_NOOP("Team"));
          full_player_name = codec->fromUnicode(player.name);
        }else{
          player.name = "?-2";
        }
        if( tmp.item == ifStore::actual_quarter ){
            if( tmp.quarter > 4 ){
                text = tr(QT_TR_NOOP("End of Overtime "));
                out << "<TR><TD class=" << stile << " colspan=3 align=\"center\"><P class=TableText><B>*** " << codec->fromUnicode(text) << (tmp.quarter - 4) << " ***</B></P></TD></TR>" << endl;
            }else{
                text = scoreboard->Azione(tmp);
                out << "<TR><TD class=" << stile << " colspan=3><P class=TableText><B>*** " << codec->fromUnicode(text) << " " << tmp.quarter << " ***</B></P></TD></TR>" << endl;
            }
            if( n == actions-1 ){
                text = tr(QT_TR_NOOP("End of Game"));
                out << "<TR><TD class=" << stile << " colspan=3><P class=TableText><B>" << codec->fromUnicode(text) << "</B></P></TD></TR>" << endl;
            }
        }else if( tmp.item == ifStore::subst_in || tmp.item == ifStore::subst_out ){
            out << "<TR><TD class=" << stile << " colspan=3><P class=TableText>" << codec->fromUnicode(scoreboard->Azione(tmp)) << "," << codec->fromUnicode(player.name) << "#" << player.number << endl;
            if( tmp.quarter <= 4 ){
                out << ",Q" << tmp.quarter;
            }else{
                out << ",OT" << (tmp.quarter - 4);
            }
            QString time;
            time.sprintf("%02d:%02d",tmp.min,tmp.sec);
            out << "," << time << "</P></TD></TR>" << endl;
        }else if( tmp.item == ifStore::my_timeout || tmp.item == ifStore::oth_timeout ){
            out << "<TR><TD class=" << stile << " colspan=3><P class=TableText>" << codec->fromUnicode(scoreboard->Azione(tmp)) << " ";
            if( tmp.item == ifStore::my_timeout ){
                out << my_team;
            }else{
                out << oth_team;
            }
            out << endl;
            if( tmp.quarter <= 4 ){
                out << ",Q" << tmp.quarter;
            }else{
                out << ",OT" << (tmp.quarter - 4);
            }
            QString time;
            time.sprintf("%02d:%02d",tmp.min,tmp.sec);
            out << "," << time << "</P></TD></TR>" << endl;
        }else if( tmp.item == ifStore::fl_done ){
            //-------------------------------------------------------------------
            //-------------------------- Faul done ------------------------------
            //-------------------------------------------------------------------
            out << "<TR><TD class=" << stile << " colspan=3><P class=TableText>";
            text = scoreboard->Azione(tmp);
            if( tmp.param == TECH_FAUL ){
                out << codec->fromUnicode(tr(QT_TR_NOOP("TF done by coach or team"))) << endl;
            }else{
                ++f_done[tmp.player_index];
                out << codec->fromUnicode(text) << "," << codec->fromUnicode(player.name) << "#" << player.number << " (" << f_done[tmp.player_index] << ")\n";
            }
            out << "</P></TD></TR>" << endl;
        }else if( tmp.item == ifStore::fl_recv ){
            //-------------------------------------------------------------------
            //-------------------------- Faul received --------------------------
            //-------------------------------------------------------------------
            out << "<TR><TD class=" << stile << " colspan=3><P class=TableText>";
            text = scoreboard->Azione(tmp);
            if( tmp.param == TECH_FAUL ){
                out << codec->fromUnicode(tr(QT_TR_NOOP("TF done by other coach or team"))) << endl;
            }else{
                ++f_recv[tmp.player_index];
                out << codec->fromUnicode(text) << "," << codec->fromUnicode(player.name) << "#" << player.number << " (" << f_recv[tmp.player_index] << ")\n";
            }
            out << "</P></TD></TR>" << endl;
        }else if( tmp.item == ifStore::oth_t1 || tmp.item == ifStore::oth_t2 || tmp.item == ifStore::oth_t3 ){
            if( tmp.item == ifStore::oth_t1 ){
                oth_pts += 1;
            }else if( tmp.item == ifStore::oth_t2 ){
                oth_pts += 2;
            }else if( tmp.item == ifStore::oth_t3 ){
                oth_pts += 3;
            }
            text = scoreboard->Azione(tmp);
            // out << text << " (" << our_pts << "-" << oth_pts << ")\n";
            out << "<TR><TD class=" << stile << "><P class=TableText></P></TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText><B>" << our_pts << "-" << oth_pts << "</B></P></TD>";
            out << "<TD class=" << stile << "><P class=TableRightText>" << codec->fromUnicode(text) << "</P></TD></TR>" << endl;
        }else if( tmp.item == ifStore::t1_ok || tmp.item == ifStore::t2_ok || tmp.item == ifStore::t3_ok ){
            if( tmp.item == ifStore::t1_ok ){
                our_pts += 1;
                points[tmp.player_index] += 1;
            }else if( tmp.item == ifStore::t2_ok ){
                our_pts += 2;
                points[tmp.player_index] += 2;
            }else if( tmp.item == ifStore::t3_ok ){
                our_pts += 3;
                points[tmp.player_index] += 3;
            }
            text = scoreboard->Azione(tmp);
            // out << text << "," << player.name << "#" << player.number << " (" << our_pts << "-" << oth_pts << ")\n";
            out << "<TR><TD class=" << stile << "><P class=TableText></P>" << full_player_name << " - " << codec->fromUnicode(text) << " (" << points[tmp.player_index] << ")</TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText><B>" << our_pts << "-" << oth_pts << "</B></P></TD>";
            out << "<TD class=" << stile << "></TD></TR>" << endl;
        }else{
            text = scoreboard->Azione(tmp);
            out << "<TR><TD class=" << stile << " colspan=3><P class=TableText></P>" << full_player_name << " - " << codec->fromUnicode(text) << "</TD>" << endl;
            out << "</TR>" << endl;
        }
    }
    out << "</TBODY></TABLE><br><br>" << endl;
    write_html_page_footer(out,codec);
}

void scorer::store_stat(QFile &data, std::vector<T_PlayerData> *registry)
{
    unsigned int n;
    int t, ok, tot, rd, ro;
    float   numeric_p;
    QString perc;
    T_PlayerData tmp;
    QTextStream out(&data);
    out << tr(QT_TR_NOOP("Player")) << "," << tr(QT_TR_NOOP("Points")) << ","
        << tr(QT_TR_NOOP("FG2")) << "," << tr(QT_TR_NOOP("FG2 tot")) << "," << tr(QT_TR_NOOP("FG2 %")) << ","
        << tr(QT_TR_NOOP("FG3")) << "," << tr(QT_TR_NOOP("FG3 tot")) << "," << tr(QT_TR_NOOP("FG3 %")) << ","
        << tr(QT_TR_NOOP("FG")) << "," << tr(QT_TR_NOOP("FG tot")) << "," << tr(QT_TR_NOOP("FG %")) << ","
        << tr(QT_TR_NOOP("FT")) << "," << tr(QT_TR_NOOP("FT tot")) << "," << tr(QT_TR_NOOP("FT %")) << ","
        << tr(QT_TR_NOOP("Reb Def")) << "," << tr(QT_TR_NOOP("Reb Off")) << "," << tr(QT_TR_NOOP("Reb tot")) << ","
        << tr(QT_TR_NOOP("Turnovers")) << "," << tr(QT_TR_NOOP("Stolen")) << ","
        << tr(QT_TR_NOOP("Fouls done")) << "," << tr(QT_TR_NOOP("Fouls received")) << ","
        << tr(QT_TR_NOOP("Assist")) << ","
        << tr(QT_TR_NOOP("Blocks done")) << "," << tr(QT_TR_NOOP("Blocks received")) << ","
        << tr(QT_TR_NOOP("Val")) << "," << tr(QT_TR_NOOP("Minutes")) << endl;

    for( n=0; n< registry->size(); n++ ){
        tmp = registry->at(n);
        QString       str, nbr;
        nbr = QString::number(tmp.number, 10);
        str = nbr + " - " + tmp.name;
        out << str << "," << GetScore(ifStore::points,n) << ",";
        /* -------------------------------------------- T2 --*/
        out << GetScore(ifStore::t2_ok,n) << "," << GetScore(ifStore::t2_ko,n) << "," << get_perc( ifStore::t2_ok, ifStore::t2_ko, n ) << ",";
        /* -------------------------------------------- T3 --*/
        out << GetScore(ifStore::t3_ok,n) << "," << GetScore(ifStore::t3_ko,n) << "," << get_perc( ifStore::t3_ok, ifStore::t3_ko, n ) << ",";
        /* -------------------------------------------- T tot --*/
        ok = GetScore(ifStore::t2_ok,n) + GetScore(ifStore::t3_ok,n);
        tot = GetScore(ifStore::t2_ko,n) + GetScore(ifStore::t3_ko,n);
        if( tot > 0 ){
            numeric_p = ((float)ok) / tot;
            numeric_p *= 100;
            perc.sprintf("%.1f %%",numeric_p);
            out << ok << "," << tot << "," << perc << ",";
        }else{
            out << ok << "," << tot << ",-,- %%" << ",";
        }
        /* -------------------------------------------- FT --*/
        out << GetScore(ifStore::t1_ok,n) << "," << GetScore(ifStore::t1_ko,n) << "," << get_perc( ifStore::t1_ok, ifStore::t1_ko, n ) << ",";
        /* -------------------------------------------- Reb --*/
        rd = GetScore(ifStore::rb_def,n);
        ro = GetScore(ifStore::rb_atk,n);
        out << rd << "," << ro << "," << (rd+ro) << ",";
        /* -------------------------------------------- Lost/Stolen --*/
        out << GetScore(ifStore::stl_recv,n) << "," << GetScore(ifStore::stl_done,n) << ",";
        /* -------------------------------------------- Fauls done/recv --*/
        out << GetScore(ifStore::fl_done,n) << "," << GetScore(ifStore::fl_recv,n) << ",";
        /* -------------------------------------------- Asst --*/
        out << GetScore(ifStore::assist,n) << ",";
        /* -------------------------------------------- Blocks done/recv --*/
        out << GetScore(ifStore::blocks_done,n) << "," << GetScore(ifStore::blocks_recv,n) << ",";
        /* -------------------------------------------- Blocks done/recv --*/
        out << GetScore(ifStore::val,n) << ",";
        t = m_time_data->GetPlayedTime(n);
        out << t;
        out << endl;
    }
}

int totals[ifStore::last_button];
int ok, tot, rd, ro, ft_caused;
int total_ok = 0, total_ko = 0;
float   numeric_p;
QString perc,tm;
int     fd[4] = {0,0,0,0}, fr[4] = {0,0,0,0};
GameTime    total_time, x_time;

void scorer::store_html(QFile &data, players *p, std::vector<T_PlayerData> *registry, QString charset)
{
    // int totals[ifStore::last_button],
    // int total_ok = 0, total_ko = 0;
    unsigned int n;
    int         ok, tot, i, myPoints, pl_number = 0; // otherPoints
    // float   numeric_p;
    QString text, name;
    T_PlayerData tmp;
    QTextStream out(&data);
    QString     stile;

    QTextCodec* codec = QTextCodec::codecForName(charset.toLatin1());
    for( i=0; i<ifStore::last_button; i++ ){ totals[i] = 0; }

    write_html_page_hdr(out,charset);
    write_stylesheet(out);

    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<div id=\"header\">";
    text = m_game->this_team;
    myPoints = GetScore(ifStore::points);

    if( text.isEmpty() ){
        text = QInputDialog::getText(
            NULL,
            tr(QT_TR_NOOP("Team name is empty, do you want to set it ?")),
            tr("Input your team name"),
            QLineEdit::Normal,
            tr(""));
    }else{
        int pos_truncate = text.indexOf(".");
        if( pos_truncate > 0 ){
            text.truncate(pos_truncate);
        }
    }
    out << "<h1>" << codec->fromUnicode(text) << " - " << m_game->game_desc << " : " << myPoints << " - " << m_game->other_team_points << "</h1>";
    out << "<h2>" ;
    if( !m_game->location.isEmpty() ){
        out << m_game->location << " - ";
    }
    out << m_game->datestring << "</h2>";
    if( !m_game->game_id.isEmpty() ){
        out << "<h2>" << codec->fromUnicode(tr(QT_TR_NOOP("Game id: "))) << m_game->game_id << "</h2>";
    }
    out << "</div>" << endl;

    QString comment = QInputDialog::getText(
        NULL,
        tr(QT_TR_NOOP("Input optional comment")),
        tr("Input optional comment"),
        QLineEdit::Normal,
        tr(""));
    if ( !comment.isEmpty() ){
      out << codec->fromUnicode(comment) << "<br><br>" << endl;
    }
    write_html_table_header(out,codec);

    for( n=0; n< registry->size(); n++ ){
        tmp = registry->at(n);
        QString       str, nbr;
        name = tmp.name;
        nbr = QString::number(tmp.number, 10);
        if( pl_number > 0 ){
            if( isInStarting5(n) ){
                str = nbr + " - " + name + " *";
            }else{
                str = nbr + " - " + name;
            }
        }else{
            str = name;
        }

        if( n%2 == 0){
            stile = "pari";
        }else{
            stile = "dispari";
        }

        write_html_row(out,codec,stile,str,n);
    }
    if( n%2 == 0){
        stile = "pari";
    }else{
        stile = "dispari";
    }
    write_html_row(out,codec,stile,"Team",MAX_PLAYERS);
    /*----------------------------------------------------------------------------------*/
    stile = "cc";
    out << "<TR>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>Tot</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::points] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t2_ok] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t2_ko] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc( totals[ifStore::t2_ok], totals[ifStore::t2_ko] ) << "</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t3_ok] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t3_ko] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc( totals[ifStore::t3_ok], totals[ifStore::t3_ko] ) << "</TD>" << endl;

    ok = totals[ifStore::t2_ok] + totals[ifStore::t3_ok];
    tot = totals[ifStore::t2_ko] + totals[ifStore::t3_ko];
    if( tot > 0 ){
        out << "<TD class=" << stile << "><P class=TableText></P>" << ok << "</TD>" << endl;
        out << "<TD class=" << stile << "><P class=TableText></P>" << tot << "</TD>" << endl;
        out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc(ok,tot) << "</TD>" << endl;
    }else{
        out << "<TD class=" << stile << "><P class=TableText></P>" << ok << "</TD>" << endl;
        out << "<TD class=" << stile << "><P class=TableText></P>" << tot << "</TD>" << endl;
        out << "<TD class=" << stile << "><P class=TableText></P>-,- %</TD>" << endl;
    }
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t1_ok] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::t1_ko] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc(totals[ifStore::t1_ok],totals[ifStore::t1_ko]) << "</TD>" << endl;

    rd = totals[ifStore::rb_def];
    ro = totals[ifStore::rb_atk];
    out << "<TD class=" << stile << "><P class=TableText></P>" << rd << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << ro << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << (rd+ro) << "</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P>" <<  totals[ifStore::stl_recv] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" <<  totals[ifStore::stl_done] << "</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P><B>" << totals[ifStore::fl_done];
    out << "</B> (" << fd[1] << "," << fd[2] << "," << fd[3] << ")</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P><B>" << totals[ifStore::fl_recv];
    out << "</B> (" << fr[1] << "," << fr[2] << "," << fr[3] << ")</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::assist] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::blocks_done] << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::blocks_recv] << "</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P>" << totals[ifStore::val] << "</TD>" << endl;
    tm = m_time_data->GetStringFullPlayedTime(total_time);
    out << "<TD class=" << stile << "><P class=TableText></P>" << tm << "</TD>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << "*" << "</TD>" << endl;
    out << "</TR>" << endl;

    out << "</TBODY></TABLE><br><br>" << endl;

    write_html_legenda(out,codec);
    write_html_page_footer(out,codec);
}

void scorer::write_html_row(QTextStream &out,QTextCodec* codec, QString stile, QString str, int n)
{
    out << "<TR>" << endl;
    out << "<TD class=" << stile << "><P class=TableText></P>" << codec->fromUnicode(str) << "</TD>" << endl;
    if( n < MAX_PLAYERS ){
        out << "<TD class=" << stile << "><P class=TableText></P><B>" << GetScore(ifStore::points,n) << "</B></TD>" << endl;
        totals[ifStore::points] += GetScore(ifStore::points,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t2_ok,n) << "</TD>" << endl;
        totals[ifStore::t2_ok] += GetScore(ifStore::t2_ok,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t2_ko,n) << "</TD>" << endl;
        totals[ifStore::t2_ko] += GetScore(ifStore::t2_ko,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc( ifStore::t2_ok, ifStore::t2_ko, n ) << "</TD>" << endl;

        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t3_ok,n) << "</TD>" << endl;
        totals[ifStore::t3_ok] += GetScore(ifStore::t3_ok,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t3_ko,n) << "</TD>" << endl;
        totals[ifStore::t3_ko] += GetScore(ifStore::t3_ko,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc( ifStore::t3_ok, ifStore::t3_ko, n ) << "</TD>" << endl;
        ok = GetScore(ifStore::t2_ok,n) + GetScore(ifStore::t3_ok,n);
        total_ok += ok;
        tot = GetScore(ifStore::t2_ko,n) + GetScore(ifStore::t3_ko,n);
        total_ko += tot;
        if( tot > 0 ){
            numeric_p = ((float)ok) / tot;
            numeric_p *= 100;
            perc.sprintf("%.1f %%",numeric_p);
            out << "<TD class=" << stile << "><P class=TableText></P>" << ok << "</TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText></P>" << tot << "</TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText></P>" << perc << "</TD>" << endl;
        }else{
            out << "<TD class=" << stile << "><P class=TableText></P>" << ok << "</TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText></P>" << tot << "</TD>" << endl;
            out << "<TD class=" << stile << "><P class=TableText></P>-,- %</TD>" << endl;
        }
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t1_ok,n) << "</TD>" << endl;
        totals[ifStore::t1_ok] += GetScore(ifStore::t1_ok,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::t1_ko,n) << "</TD>" << endl;
        totals[ifStore::t1_ko] += GetScore(ifStore::t1_ko,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << get_perc( ifStore::t1_ok, ifStore::t1_ko, n ) << "</TD>" << endl;
    }else{
      int i;
      for( i=0; i<13; i++){
        out << "<TD class=" << stile << "><P class=TableText></P></TD>" << endl;
      }
    }
    rd = GetScore(ifStore::rb_def,n);
    ro = GetScore(ifStore::rb_atk,n);
    out << "<TD class=" << stile << "><P class=TableText></P>" << rd << "</TD>" << endl;
    totals[ifStore::rb_def] += rd;
    out << "<TD class=" << stile << "><P class=TableText></P>" << ro << "</TD>" << endl;
    totals[ifStore::rb_atk] += ro;
    out << "<TD class=" << stile << "><P class=TableText></P>" << (rd+ro) << "</TD>" << endl;

    out << "<TD class=" << stile << "><P class=TableText></P>" <<  GetScore(ifStore::stl_recv,n) << "</TD>" << endl;
    totals[ifStore::stl_recv] += GetScore(ifStore::stl_recv,n);
    out << "<TD class=" << stile << "><P class=TableText></P>" <<  GetScore(ifStore::stl_done,n) << "</TD>" << endl;
    totals[ifStore::stl_done] += GetScore(ifStore::stl_done,n);

    out << "<TD class=" << stile << "><P class=TableText></P><B>" << GetScore(ifStore::fl_done,n) << "</B>";
    ft_caused = throws_on_fauls[n][F_DONE][1] + 2*throws_on_fauls[n][F_DONE][2] + 3*throws_on_fauls[n][F_DONE][3];
    // out << " (" << ft_caused << tr(QT_TR_NOOP(" FT")) << ")</TD>" << endl;
    fd[1] += throws_on_fauls[n][F_DONE][1];
    fd[2] += throws_on_fauls[n][F_DONE][2];
    fd[3] += throws_on_fauls[n][F_DONE][3];
    out << " (" << throws_on_fauls[n][F_DONE][1] << "," << throws_on_fauls[n][F_DONE][2] << "," << throws_on_fauls[n][F_DONE][3] << ")";
    out << "</TD>" << endl;
    totals[ifStore::fl_done] += GetScore(ifStore::fl_done,n);

    out << "<TD class=" << stile << "><P class=TableText></P><B>" << GetScore(ifStore::fl_recv,n) << "</B>";
    ft_caused = throws_on_fauls[n][F_RECV][1] + 2*throws_on_fauls[n][F_RECV][2] + 3*throws_on_fauls[n][F_RECV][3];
    out << " (" << throws_on_fauls[n][F_RECV][1] << "," << throws_on_fauls[n][F_RECV][2] << "," << throws_on_fauls[n][F_RECV][3] << ")";
    // out << " (" << ft_caused << tr(QT_TR_NOOP(" FT")) << ")</TD>" << endl;
    out << "</TD>" << endl;
    fr[1] += throws_on_fauls[n][F_RECV][1];
    fr[2] += throws_on_fauls[n][F_RECV][2];
    fr[3] += throws_on_fauls[n][F_RECV][3];
    totals[ifStore::fl_recv] += GetScore(ifStore::fl_recv,n);

    if( n < MAX_PLAYERS ){
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::assist,n) << "</TD>" << endl;
        totals[ifStore::assist] += GetScore(ifStore::assist,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::blocks_done,n) << "</TD>" << endl;
        totals[ifStore::blocks_done] += GetScore(ifStore::blocks_done,n);
        out << "<TD class=" << stile << "><P class=TableText></P>" << GetScore(ifStore::blocks_recv,n) << "</TD>" << endl;
        totals[ifStore::blocks_recv] += GetScore(ifStore::blocks_recv,n);
    }else{
        int i;
        for( i=0; i<3; i++){
          out << "<TD class=" << stile << "><P class=TableText></P></TD>" << endl;
        }
    }
    out << "<TD class=" << stile << "><P class=TableText></P><B>" << GetScore(ifStore::val,n) << "</B></TD>" << endl;
    totals[ifStore::val] += GetScore(ifStore::val,n);
    // t = m_time_data->GetPlayedTime(n);
    if( n < MAX_PLAYERS ){
      x_time = m_time_data->GetFullPlayedTime(n);
      total_time = total_time + x_time;
      tm = m_time_data->GetStringFullPlayedTime(x_time);
    }else{
      tm = "";
    }
    out << "<TD class=" << stile << "><P class=TableText></P>" << tm << "</TD>" << endl;
    int impact = m_time_data->GetImpact(n);
    out << "<TD class=" << stile << "><P class=TableText></P>" << impact << "</TD>" << endl;
    out << "</TR>" << endl;
}

void scorer::write_stylesheet(QTextStream &out)
{
    out << "<style media=\"screen\" type=\"text/css\">" << endl;
    out << "* { outline: none; }" << endl;
    out << "body { font: 100% \"Lucida Grande\", Arial, sans-serif; background-color: #f6f6f6; color: #3333FF; }" << endl;
    out << "h1 { text-align:center; font: 130%; color:#663333; }" << endl;
    out << "h2, h3, h4, h5 { text-align:center; font: 110%; color:#663333; }" << endl;
    out << "table.cc {" << endl;
    out << "border-collapse:collapse;" << endl;
    out << "background:#cdf5d0;" << endl;
    out << "border-spacing:1pt;" << endl;
    out << "border:solid black;" << endl;
    out << "}" << endl;
    out << "thead.cc {" << endl;
    out << "border: 1pt solid black;" << endl;
    out << "background:#a2eea7;" << endl;
    out << "padding: 0em" << endl;
    out << "}" << endl;
    out << "tbody.cc {" << endl;
    out << "border: 1pt solid black;" << endl;
    out << "background:#a2eea7;" << endl;
    out << "padding: 0em" << endl;
    out << "}" << endl;
    out << "td.cc {" << endl;
    out << "background:#a2eea7;" << endl;
    out << "border: 1pt solid black;" << endl;
    out << "padding: 0.2em" << endl;
    out << "}" << endl;
    out << "td.pari {" << endl;
    out << "background:#e2fae4;" << endl;
    out << "border: 1pt solid black;" << endl;
    out << "padding: 0.2em" << endl;
    out << "}" << endl;
    out << "td.dispari {" << endl;
    out << "background:#ffffff;" << endl;
    out << "border: 1pt solid black;" << endl;
    out << "padding: 0.2em" << endl;
    out << "}" << endl;
    out << "p.TableHeader, li.TableHeader, div.TableHeader {" << endl;
    out << "text-align:center;" << endl;
    out << "font-family:\"Verdana\";" << endl;
    out << "font-weight:bold" << endl;
    out << "}" << endl;
    out << "p.TableText {" << endl;
    out << "margin-top:0.2em;" << endl;
    out << "margin-bottom:0.2em;" << endl;
    out << "text-align:center;" << endl;
    out << "vertical-align:center;" << endl;
    out << "font-family:\"Verdana\"" << endl;
    out << "}" << endl;
    out << "p.TableRightText {" << endl;
    out << "margin-top:0.2em;" << endl;
    out << "margin-bottom:0.2em;" << endl;
    out << "text-align:right;" << endl;
    out << "vertical-align:center;" << endl;
    out << "font-family:\"Verdana\"" << endl;
    out << "}" << endl;
    out << "li.TableText, div.TableText {" << endl;
    out << "margin-top:0.2em;" << endl;
    out << "margin-bottom:0.2em;" << endl;
    out << "text-align:center;" << endl;
    out << "vertical-align:top;" << endl;
    out << "font-family:\"Verdana\"" << endl;
    out << "}" << endl;
    out << "</style>" << endl;
}

void scorer::write_html_page_hdr(QTextStream &out,QString charset)
{
    out << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">" << endl;
    out << "<html><head><title></title>" << endl;
    out << "<meta name=\"generator\" content=\"bkstat full\">" << endl;
    out << "<meta name=\"author\" content=\"caminac\">" << endl;
    out << "<meta name=\"date\" content=\"2012-08-17T13:45:27+0100\">" << endl;
    out << "<meta name=\"copyright\" content=\"\">" << endl;
    out << "<meta name=\"keywords\" content=\"\">" << endl;
    out << "<meta name=\"description\" content=\"\">" << endl;
    out << "<meta name=\"ROBOTS\" content=\"NOINDEX, NOFOLLOW\">" << endl;
    if( charset != ""){
      out << "<meta charset=\"" << charset << "\">" << endl;
    }
    //out << "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">" << endl;
    //out << "<meta http-equiv=\"content-type\" content=\"application/xhtml+xml; charset=UTF-8\">" << endl;
    out << "<meta http-equiv=\"content-style-type\" content=\"text/css\">" << endl;
    out << "<meta http-equiv=\"expires\" content=\"0\">" << endl;
}

void scorer::write_html_page_footer(QTextStream &out, QTextCodec* codec)
{
    out << "<div style=\"float: right;\" style=\"font-size: 10pt;\">" << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Made with: "))) << p_name << " (" << p_platform << ") " << p_vers << " <a href=\"http://" << p_website << "\">website</a>" << endl;
    out << "</div>" << endl;

    out << "</div>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;
}

void scorer::write_html_legenda(QTextStream &out, QTextCodec* codec)
{
    out << codec->fromUnicode(tr(QT_TR_NOOP("Pts: Points; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("FG2 M-A: 2-point Field Goals (Made-Attempted); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("FG3 M-A: 3-point Field Goals (Made-Attempted); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("FG M-A: total Field Goals (Made-Attempted); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("FT M-A: Free Throws (Made-Attempted); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Rebounds: D (Defensive), O (Offensive), T (Total); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Ass: Assists; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("St: Steals; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("To: Turnovers; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Fouls: Cm (Commited), Rv (Received); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("(P1,P2,P3) = Foul with 1, 2 or 3 FT; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Bl: Blocks (Fv: In Favor / Ag: Against); "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Val: evaluation; "))) << endl;
    out << codec->fromUnicode(tr(QT_TR_NOOP("Min: Minutes played; "))) << endl;
    out << "<br><br>" << endl;
}

void scorer::write_html_table_header(QTextStream &out, QTextCodec* codec)
{
    out << "<TABLE width=\"100%\" class=\"cc\">" << endl;
    out << "<THEAD class=\"cc\">" << endl;
    out << "<TR>" << endl;
    // align="center" colspan="2"
    out << "<TD width=\"8%\" rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Player"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Pts"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\"  colspan=\"3\"  class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("FG2"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  colspan=\"3\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("FG3"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  colspan=\"3\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("FG"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  colspan=\"3\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("FT"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  colspan=\"3\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Rebounds"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("To"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("St"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\"  colspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Fouls (P1,P2,P3)"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Ass"))) << "</P></TD>" << endl;
    out << "<TD width=\"4%\"  colspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Bl"))) << "</P></TD>" << endl;
    //
    out << "<TD width=\"3%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Val"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Min"))) << "</P></TD>" << endl;
    out << "<TD width=\"1%\"  rowspan=\"2\" class=\"cc\"><P class=TableHeader>" << "+/-" << "</P></TD>" << endl;
    out << "</TR>" << endl;
    // col 1
    // col 2
    // 3 col x FG2
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("M"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("A"))) << "</P></TD>" << endl;
    out << "<TD width=\"4%\" class=\"cc\"><P class=TableHeader>" << "%" << "</P></TD>" << endl;
    // 3 col x FG3
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("M"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("A"))) << "</P></TD>" << endl;
    out << "<TD width=\"4%\" class=\"cc\"><P class=TableHeader>" << "%" << "</P></TD>" << endl;
    // 3 col x FG
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("M"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("A"))) << "</P></TD>" << endl;
    out << "<TD width=\"4%\" class=\"cc\"><P class=TableHeader>" << "%" << "</P></TD>" << endl;
    // 3 col x FT
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("M"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("A"))) << "</P></TD>" << endl;
    out << "<TD width=\"4%\" class=\"cc\"><P class=TableHeader>" << "%" << "</P></TD>" << endl;
    // 3 col x Reb
    out << "<TD width=\"3%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("D"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("O"))) << "</P></TD>" << endl;
    out << "<TD width=\"3%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("T"))) << "</P></TD>" << endl;
    // TO + ST
    // 2 col x faul
    out << "<TD width=\"5%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Cm"))) << "</P></TD>" << endl;
    out << "<TD width=\"5%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Rv"))) << "</P></TD>" << endl;
    // assist
    // 2 col x blk
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Fv"))) << "</P></TD>" << endl;
    out << "<TD width=\"2%\" class=\"cc\"><P class=TableHeader>" << codec->fromUnicode(tr(QT_TR_NOOP("Ag"))) << "</P></TD>" << endl;
    out << "<TR>" << endl;
    out << "</TR>" << endl;
    out << "</THEAD>" << endl;
    out << "<TBODY>" << endl;
}

void scorer::load_match(QFile &data, playstat *scoreboard)
{
    int           last_in = -1, last_out = -1, last_start = 0, last_subst = 0;
    T_ActionDesc  tmp = { 0,0,0,0,0,0,0,0 };
    QTextStream stream(&data);
    QString     line;
    // int n=0;
    m_game->m_actual_quarter = 1;
    do {
        bool ok;
        line = stream.readLine();
        if( line[0] == 'A' ){
            line.remove(0,1);
            QStringList list1 = line.split(",");
            tmp.player_index = list1[1].toInt(&ok, 10);
            tmp.item = list1[0].toInt(&ok, 10);
            tmp.min = -1;
            tmp.sec = -1;
            tmp.param = 0;
            tmp.quarter = m_game->m_actual_quarter;
            if( tmp.item == ifStore::subst_in ){
              tmp.min = list1[2].toInt(&ok, 10);
              tmp.sec = list1[3].toInt(&ok, 10);
              last_in = m_players->lookup_subst_pos_by_index(tmp.player_index);
              m_players->exchange_players(last_out, last_in);
            }else if( tmp.item == ifStore::subst_out ){
              tmp.min = list1[2].toInt(&ok, 10);
              tmp.sec = list1[3].toInt(&ok, 10);
              last_out = m_players->lookup_field_pos_by_index(tmp.player_index);
            }else if( tmp.item == ifStore::my_timeout || tmp.item == ifStore::oth_timeout ){
              tmp.min = list1[2].toInt(&ok, 10);
              tmp.sec = list1[3].toInt(&ok, 10);
            }else if( tmp.item == ifStore::actual_quarter ){
              tmp.quarter = list1[1].toInt(&ok, 10);
              m_game->m_actual_quarter = 1 + tmp.quarter;
              if( m_game->m_actual_quarter > 0 ){
                m_players->EndOfPeriod();
              }
            }else if( tmp.item == ifStore::starting_five ){
              m_players->set_field_player(last_start, tmp.player_index);
              m_game->m_start5[last_start] = tmp.player_index;
              last_start++;
            }else if( tmp.item == ifStore::start_substitute ){
              m_players->set_subst_player(last_subst, tmp.player_index);
              last_subst++;
            }else if( tmp.item == ifStore::fl_done || tmp.item == ifStore::fl_recv ){
              // il tipo di fallo o i TL sono messi nel 3o parametro
              tmp.min = list1[2].toInt(&ok, 10);
            }
            AddScore(tmp.item,tmp.player_index,tmp.team_index,tmp.min,tmp.sec,tmp.quarter);
            scoreboard->UpdateScoreboard(tmp.item,1,tmp.player_index);
        }
    } while (!line.isNull());
}

bool scorer::isInStarting5(int pl_index)
{
    bool rv = false;
    int  i;
    for( i=0; i<N_FIELD; i++ ){
      if( m_game->m_start5[i] == pl_index ){
        rv = true;
        break;
      }
    }
    return rv;
}

void scorer::init_T_ActionDesc( T_ActionDesc &x)
{
    x.coord_x = -1;
    x.coord_y = -1;
    x.item = -1;
    x.min = -1;
    x.sec = -1;
    x.param = 0;
    x.player_index = -1;
    x.quarter = -1;
}

int scorer::get_current_gap()
{
    int our = GetScore(ifStore::points);
    int oth = GetScore(ifStore::oth_points);
    int gap = our - oth;
    return gap;
}
