#include "select_player.h"
#include "ui_select_player.h"

select_player::select_player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::select_player)
{
    ui->setupUi(this);
}

select_player::~select_player()
{
    delete ui;
}

void select_player::on_bt_pl1_clicked()
{
    m_sel = indexes[0];
    this->hide();
}

void select_player::on_bt_pl3_clicked()
{
    m_sel = indexes[1];
    this->hide();
}

void select_player::on_bt_pl2_clicked()
{
    m_sel = indexes[2];
    this->hide();
}

void select_player::on_bt_pl4_clicked()
{
    m_sel = indexes[3];
    this->hide();
}

void select_player::on_bt_pl5_clicked()
{
    m_sel = indexes[4];
    this->hide();
}

void select_player::set_numbers(int idx[], int numbers[])
{
    for( int i=0; i<N_FIELD; i++ ){ indexes[i] = idx[i]; }
    ui->bt_pl1->setText(QString::number(numbers[0], 10));
    ui->bt_pl2->setText(QString::number(numbers[1], 10));
    ui->bt_pl3->setText(QString::number(numbers[2], 10));
    ui->bt_pl4->setText(QString::number(numbers[3], 10));
    ui->bt_pl5->setText(QString::number(numbers[4], 10));
    m_sel = -1;
}
