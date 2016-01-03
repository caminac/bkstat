#include "setup.h"
#include "teamselection.h"
#include "ui_teamselection.h"
#include "Utility.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

teamselection::teamselection(std::vector<T_PlayerData> *players_registry, T_GameData *game_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teamselection)
{
    m_loaded = false;
    ui->setupUi(this);
    registry = players_registry;
    ui->list_team->setAlternatingRowColors(true);
    ui->sb_number->setMinimum(MIN_PLAYER_NUMBER);
    m_game_data = game_data;
    m_separator = new QRegExp("[,;]");
#if defined(DEMO_VERSION)
    //ui->bt_load_file->setEnabled(false);
    //ui->bt_store_file->setEnabled(false);
    //ui->bt_import_file->setEnabled(false);
#endif

#if defined(Q_OS_ANDROID)
    QFont font("Times", 8);
    ui->bt_add->setFont(font);
#endif
}

teamselection::~teamselection()
{
    delete ui;
}

void teamselection::on_bt_add_clicked()
{
    T_PlayerData  tmp;
    QString name, str, nbr;

    name = ui->player_name->toPlainText();
    if( name.contains("\n") ){
        name.replace("\n"," ");
    }
    if (name.length() > MAX_LEN_NAMES ) {
      name = name.left(MAX_LEN_NAMES);
    }

    int number = ui->sb_number->value();
    if( number >= MIN_PLAYER_NUMBER && number <= MAX_PLAYER_NUMBER ){
        if( insert_player(number,name) ){
          ui->player_name->clear();
          ui->sb_number->setValue(number + 1);
        }
    }
}

bool teamselection::insert_player(int number, QString name)
{
    int size = registry->size();
    if( size >= MAX_PLAYERS ){
        return false;
    }

    if( !is_player_present(number) ){
        T_PlayerData  tmp;
        QString       str, nbr;
        int pos = registry->size();
        tmp.name = name;
        tmp.number = number;
        nbr = QString::number(number, 10);
        registry->push_back(tmp);
        str = nbr + " - " + name;
        int last_line = ui->list_team->count();
        ui->list_team->insertItem(last_line+1,str);
    }
    return true;
}

void teamselection::refresh_players()
{
    unsigned int n, last_line;
    T_PlayerData  tmp;

    ui->list_team->clear();
    for( n=0; n< registry->size(); n++ ){
        tmp = registry->at(n);

        QString       str, nbr;
        nbr = QString::number(tmp.number, 10);
        str = nbr + " - " + tmp.name;
        last_line = ui->list_team->count();
        ui->list_team->insertItem(last_line+1,str);
    }
}

bool teamselection::is_player_present(int number)
{
    unsigned int  n;
    T_PlayerData  tmp;
    QString       str, nbr;
    bool          found = false;

    for( n=0; n< registry->size(); n++ ){
        tmp = registry->at(n);
        if( tmp.number == number ){
            found = true;
            break;
        }
    }
    return found;
}

void teamselection::on_bt_delete_clicked()
{
    T_PlayerData  tobeerased, moved;
    int size = registry->size();

    if( size > 0 ){
        int selected = ui->list_team->currentRow();
        if( selected != -1 ){
          if( selected != (size-1) ){
            tobeerased = registry->at(selected);
            moved = registry->back();
            registry->pop_back();
            registry->at(selected) = moved;
          }else{
            // ultimo elemento della lista
            registry->pop_back();
          }
          refresh_players();
        }else{
            QMessageBox msgBox;
            QString text = tr("No player selected");
            msgBox.setText(text);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }
    //registry.erase(selected);
}

void teamselection::on_bt_close_clicked()
{
    this->hide();
}

void teamselection::on_bt_load_file_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    if( m_loaded ){
        QMessageBox msgBox;
        QString text = tr("Only one load or import operation");
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    QString fileName = Utility::selectFile(this,".","*.tm",tr("select team"),tr("team:"));
    if ( fileName != "" ) {
        QString       str, nbr;

        QFile data(fileName);
        if (data.open(QFile::ReadOnly)) {
            int players;
            QString err;
            load_team(data,players,err,teamselection::load);
            data.close();
            m_loaded = true;
            int pos_truncate = fileName.indexOf(".");
            fileName.truncate(pos_truncate);
            m_game_data->this_team = fileName;
        }
    }else{
        QMessageBox msgBox;
        QString text = tr("No team available or selected");
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
#endif
}

void teamselection::on_bt_store_file_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    if( !can_save() ){
        QMessageBox msgBox;
        QString text = tr("Can't save team");
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    QMessageBox msgBox;
    bool ok, save = true;
    QString team_name = m_game_data->this_team;
    if( team_name == "" ){
      team_name = QInputDialog::getText(this, tr("Save new team"),
                    tr("Team name:"), QLineEdit::Normal,
                    "", &ok);
    }

    if( team_name.size() > 0 ){
        QString fileName = "./" + team_name + ".tm";
        QFile tobesaved(fileName);

        if( tobesaved.exists() ){
            QString text = tr("Team ") + team_name + tr(" already exists, overwrite ?");
            msgBox.setText(text);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            if( ret != QMessageBox::Ok){
               save = false;
            }
        }
        if ( save ) {
            QString       str, nbr;
            QFile data(fileName);
            if (data.open(QFile::ReadWrite)) {
                store_team(data);
                data.close();
            }
        }
    }else{
        QString text = tr("Team name is empty");
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }

#endif
}

void teamselection::store_team(QFile &data)
{
    unsigned int n;
    T_PlayerData  tmp;
    QTextStream out(&data);
    for( n=0; n< registry->size(); n++ ){
        tmp = registry->at(n);
        if( tmp.number >0 ){
            out << "#" << tmp.number << "," << tmp.name << "," << tmp.birthdate << "," << tmp.fed_id << "," << tmp.team_id << "\n";
        }
        tmp.number = 0;
    }
}

int teamselection::load_team(QFile &data, int &players, QString &firstError, int mode)
{
    int           lineNumber, errors = 0;
    T_PlayerData  tmp;
    QTextStream stream(&data);
    QString     line;
    lineNumber = 0;
    players    = 0;
    firstError = "";
    do {
        bool ok;
        line = stream.readLine();
        lineNumber++;
        if( line[0] == '#' ){
            line.remove(0,1);
            QStringList list1 = line.split(*m_separator);
            if( list1.size() >= 2 ){
                tmp.number = list1[0].toInt(&ok, 10);
                tmp.name = list1[1];
                if( list1.size() >= 3 ){
                    tmp.birthdate = list1[2];
                }else{
                    tmp.birthdate = "";
                }
                if( list1.size() >= 4 ){
                    tmp.fed_id = list1[3];
                }else{
                    tmp.fed_id = "";
                }
                if( list1.size() >= 5 ){
                    tmp.team_id = list1[4];
                }else{
                    tmp.team_id = "";
                }
                if( tmp.number >= MIN_PLAYER_NUMBER && tmp.number <= MAX_PLAYER_NUMBER ){
                    if( tmp.name.size() == 0 ){
                        QString fake_name;
                        fake_name = tr(QT_TR_NOOP("Player ")) + QString::number(tmp.number,10);
                        tmp.name = fake_name;
                        if( mode == teamselection::load ){
                            insert_player(tmp.number, tmp.name);
                        }
                      /*  if( firstError == ""){
                            firstError = tr(QT_TR_NOOP("Player name empty at line ")) + QString::number(lineNumber,10);
                        }
                        ++errors; */
                    }else if( tmp.name.size() <= MAX_LEN_NAMES ){
                        players++;
                        if( players > MAX_PLAYERS ){
                            if( firstError == ""){
                                firstError = tr(QT_TR_NOOP("Too much players: maximum is ")) + QString::number(MAX_PLAYERS,10);
                            }
                            ++errors;
                        }else{
                            if( mode == teamselection::load ){
                                insert_player(tmp.number, tmp.name);
                            }
                        }
                    }else{
                        if( firstError == ""){
                            firstError = tr(QT_TR_NOOP("Player name too long at line ")) + QString::number(lineNumber,10);
                        }
                        ++errors;
                    }
                }else{
                    if( firstError == ""){
                        firstError = tr(QT_TR_NOOP("Bad player number at line ")) + QString::number(lineNumber,10);
                    }
                    ++errors;
                }
            }else{
                if( firstError == ""){
                    firstError = tr(QT_TR_NOOP("Bad line format at line ")) + QString::number(lineNumber,10);
                }
                ++errors;
            }
        }else{
            if( line[0] != 'D' && line[0] != 'A' ){
                if( line != "" ){
                    if( firstError == ""){
                        firstError = tr(QT_TR_NOOP("Invalid code at line ")) + QString::number(lineNumber,10);
                    }
                    ++errors;
                }
            }
        }
    } while( !stream.atEnd() );
    // while (!line.isNull());
    return errors;
}

bool teamselection::can_save()
{
    bool retV = false;
    if( ui->list_team->count() >= 5 ){
        retV = true;
    }
    return retV;
}

void teamselection::on_bt_import_file_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    if( m_loaded ){
        QMessageBox msgBox;
        QString text = tr(QT_TR_NOOP("Only one load or import operation"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    int errs = 0;
    bool delete_old_dest = false;
    QMessageBox  msgBox;
    QString      basename, team2beimported = Utility::selectFile(this,IMPORT_EXPORT_DIR,IMPORT_WILDCHAR, tr("Select team"), tr("team to import:"));
    if ( team2beimported != "" ) {
        QStringList list1 = team2beimported.split(".");
        basename = list1[0];
        QString srcFileName = IMPORT_EXPORT_DIR + team2beimported,
                destFileName = "./" + basename + IMPORT_EXTENSION;
        QFile   srcFile(srcFileName),
                dstFile(destFileName);

        if( dstFile.exists() ){
            QString text = tr(QT_TR_NOOP("Team ")) + team2beimported + tr(QT_TR_NOOP(" already exists, overwrite ?"));
            msgBox.setText(text);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int ret = msgBox.exec();
            if( ret != QMessageBox::Ok){
               return;
            }else{
               // dstFile.remove();
               delete_old_dest = true;
            }
        }
        // check
        QFile src2betested(srcFileName);
        if (src2betested.open(QFile::ReadOnly)) {
            int players;
            QString firstErr;
            errs = load_team(src2betested,players,firstErr,teamselection::test_only);
            src2betested.close();
            if( errs > 0 ){
                QString text = tr(QT_TR_NOOP("Team ")) + team2beimported + tr(QT_TR_NOOP(" contains errors, will delete it.\nFirst error is: ")) + firstErr;
                msgBox.setText(text);
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
                src2betested.remove();
                return;
            }else{
                if( players == 0 ){
                    QString text = tr(QT_TR_NOOP("Team ")) + team2beimported + tr(QT_TR_NOOP(" doesn't contain any valid player, will delete it."));
                    msgBox.setText(text);
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                    src2betested.remove();
                    return;
                }
            }
        }
        // check passed
        if( delete_old_dest ){
          dstFile.remove();
        }
        if( srcFile.copy(destFileName) ){
            QFile data(destFileName);
            if (data.open(QFile::ReadOnly)) {
                int players;
                QString firstErr;
                errs = load_team(data,players,firstErr);
                data.close();
                m_loaded = true;
                int pos_truncate = team2beimported.indexOf(".");
                team2beimported.truncate(pos_truncate);
                m_game_data->this_team = team2beimported;
            }
        }else{
            QString text = tr(QT_TR_NOOP("Team ")) + team2beimported + tr(QT_TR_NOOP(" import failed (can't copy to private directory')"));
            msgBox.setText(text);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }else{
        QMessageBox msgBox;
        QString text = tr(QT_TR_NOOP("No team available or selected for import"));
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
#endif
}

void teamselection::showEvent( QShowEvent * event )
{
  if( m_game_data->game_started ){
    ui->bt_delete->setEnabled(false);
    ui->bt_import_file->setEnabled(false);
    ui->bt_store_file->setEnabled(true);
    ui->bt_load_file->setEnabled(false);
  }else{
    ui->bt_delete->setEnabled(true);
    ui->bt_import_file->setEnabled(true);
    ui->bt_store_file->setEnabled(true);
    ui->bt_load_file->setEnabled(true);
  }
}

void teamselection::warnForVersion()
{
    QMessageBox msgBox;
    QString text = tr(QT_TR_NOOP("Feature available only in bkstat full"));
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}
