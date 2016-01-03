#include "oth_points_menu.h"
#include "ui_oth_points_menu.h"
#include "playstat.h"

oth_points_menu::oth_points_menu(playstat *stat, ifStore *store, T_GameData *game_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oth_points_menu)
{
    ui->setupUi(this);

    m_stat = stat;
    m_store = store;
    m_game_data = game_data;
}

oth_points_menu::~oth_points_menu()
{
    delete ui;
}

void oth_points_menu::on_buttonBox_accepted()
{
    int type = -1;
    if( m_game_data->game_end ){ return; }
    if( ui->rb_1->isChecked() ){
        type = ifStore::oth_t1;
    }else if( ui->rb_2->isChecked() ){
        type = ifStore::oth_t2;
    }else if( ui->rb_3->isChecked() ){
        type = ifStore::oth_t3;
    }
    if( type > 0 ){
        m_store->AddScore(type,-1);
        m_stat->UpdateScoreboard(ifStore::oth_points,m_store->GetScore(ifStore::oth_points));
    }
}
