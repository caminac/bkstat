#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QCoreApplication>
#include <QMessagebox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QFileInfo>
#include <QInputDialog>
#include <QTextStream>
#include <QDesktopWidget>
#include "utility.h"
#include "info.h"
#include "setup.h"

MainWindow::MainWindow(QSettings *settings, QString l, QWidget *parent )
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    T_PlaytimeData time_registry[MAX_PLAYERS];
    int i;
    m_export_dir = IMPORT_EXPORT_DIR;
    QString dir = QDir::currentPath();

    //QCoreApplication *app = QCoreApplication::instance();
    QDesktopWidget *dt = QApplication::desktop();
    m_screen = dt->screenGeometry();

    m_current_language = l;
    GameTime ti(10,0), t2(9,59), t3(2,0), t4, t5(12,2);
    t4 = ti - t2;
    t4 = ti - t3;
    t4 = t2 + t5;

    for( i=0; i<MAX_PLAYERS; i++ ){
        time_registry[i].m_enter_time = GameTime();
        time_registry[i].m_played_time = GameTime();       
    }
    ui->setupUi(this);
    m_game_data.simplified = false;
    m_game_data.game_end = false;
    m_game_data.game_started = false;
    m_game_data.m_quarter_duration = 10; // in caso di load ed opzioni != 10 dà risultati falsati
    m_game_data.m_overtime_duration = 5;
    m_game_data.m_actual_quarter = 0;
    players_registry.clear();

    for( i=0; i<N_FIELD; i++ ){ m_field[i] = -1; }
    for( i=0; i<MAX_SUBST; i++ ){ m_substitutes[i] = -1; }

    // QSize sz = this->size();
    // int h = sz.rheight(), w = sz.rwidth();

    m_time_data = new PlayTimeData();
    m_team = new teamselection(&players_registry,&m_game_data,this);
    m_sco = new scorer(&m_game_data,m_time_data);
    m_sco->Reset();
    m_play = 0;
    m_players = new players(m_sco,&players_registry,m_field,m_substitutes,&m_game_data,m_time_data,this);

    m_sco->set_players(m_players);

    m_play = new playstat(m_sco,&m_game_data,m_players,this);
    m_statistic = new statistics(m_sco,&m_game_data,m_players,m_time_data,this);
    m_options = new dlg_options(settings, l);
    m_options->set_export_dir(m_export_dir);
    m_status = ST_INIT;
    update_status();

    int width,height;
    width = m_screen.width();
    height = m_screen.height();

    QString desc;
    //desc = QString(p_name) + QString(" ") + QString(p_vers) + " Res:" + QString::number(width,10) + "x" + QString::number(height,10) + QString(" ") + QString(p_build);
    desc = "Res:" + QString::number(width,10) + "x" + QString::number(height,10);
    ui->lb_main->setText(desc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        //attribute = Qt::WA_LockPortraitOrientation;
        //attribute = Qt::PortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        //attribute = Qt::WA_LockLandscapeOrientation;
        //attribute = Qt::LandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        //attribute = Qt::WA_AutoOrientation;
        //attribute = Qt::PortraitOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

void MainWindow::on_but_new_clicked()
{
    newgame *p = new newgame(&m_game_data,this);
    p->showNormal();
    m_status = ST_GAME_DEFINED;
    update_status();
}

void MainWindow::on_but_view_clicked()
{
    m_statistic->set_player(0);
    m_statistic->showNormal();
}

void MainWindow::on_but_play_clicked()
{
    m_play->startGame();
    m_play->showNormal();
}

void MainWindow::on_bt_team_clicked()
{
    //m_team->showNormal();
    m_team->exec();
    if( players_registry.size() >= N_FIELD && !m_game_data.game_started ){
        m_status = TEAM_LOADED;
    }
    update_status();
}

void MainWindow::on_bt_field_clicked()
{
    if( players_registry.size() >= N_FIELD ){
        m_players->set_author_mode(players::select_start_5);
        m_players->set_text(tr(QT_TR_NOOP("Select starting 5\nusing <->")));
        m_players->showNormal();
        m_status = FIELD_OK;
        m_game_data.m_actual_quarter = 1;
        m_play->UpdateScoreboard(ifStore::actual_quarter,m_game_data.m_actual_quarter);

        update_status();
    }else{
        m_status = ST_GAME_DEFINED;
        update_status();
    }
}

void MainWindow::update_status()
{
    switch( m_status ){
        case ST_INIT:
            ui->but_new->setEnabled(true);
            ui->bt_team->setEnabled(false);
            ui->but_play->setEnabled(false);
            ui->but_view->setEnabled(false);
            ui->bt_field->setEnabled(false);
#if !defined(DEMO_VERSION)
            ui->bt_load->setEnabled(true);
#else
            ui->bt_load->setEnabled(false);
#endif
            ui->bt_save->setEnabled(false);
            ui->but_export->setEnabled(false);
            ui->but_exp_stat->setEnabled(false);
            ui->but_del_dirs->setEnabled(true);
#if !defined(DEMO_VERSION)
            ui->but_del_files->setEnabled(true);
#else
            ui->but_del_files->setEnabled(false);
#endif
            break;
        case ST_GAME_DEFINED:
            ui->but_new->setEnabled(false);
            ui->bt_team->setEnabled(true);
            ui->but_play->setEnabled(false);
            ui->but_view->setEnabled(false);
            ui->bt_field->setEnabled(false);
            ui->bt_load->setEnabled(false);
            ui->bt_save->setEnabled(false);
            ui->but_export->setEnabled(false);
            ui->but_exp_stat->setEnabled(false);
            ui->but_del_files->setEnabled(false);
            ui->but_del_dirs->setEnabled(false);
            break;
        case TEAM_LOADED:
            ui->but_new->setEnabled(false);
            ui->bt_team->setEnabled(false);
            ui->but_play->setEnabled(false);
            ui->but_view->setEnabled(false);
            ui->bt_field->setEnabled(true);
            ui->bt_load->setEnabled(false);
            ui->bt_save->setEnabled(false);
            ui->but_export->setEnabled(false);
            ui->but_exp_stat->setEnabled(false);
            ui->but_del_files->setEnabled(false);
            ui->but_del_dirs->setEnabled(false);
            break;
        case FIELD_OK:
            ui->but_new->setEnabled(false);
            ui->bt_team->setEnabled(true);
            ui->but_play->setEnabled(true);
            ui->but_view->setEnabled(true);
            ui->bt_field->setEnabled(false);
#if !defined(DEMO_VERSION)
            ui->but_export->setEnabled(true);
            //ui->but_exp_stat->setEnabled(true);
            ui->bt_load->setEnabled(false);
            ui->bt_save->setEnabled(true);
#else
            ui->bt_load->setEnabled(false);
            ui->bt_save->setEnabled(true);
#endif
            ui->but_del_files->setEnabled(false);
            ui->but_del_dirs->setEnabled(false);
            break;
        case VIEW_ONLY:
            ui->but_new->setEnabled(false);
            ui->bt_team->setEnabled(false);
            ui->but_play->setEnabled(false);
            ui->but_view->setEnabled(true);
            ui->bt_field->setEnabled(false);
            ui->bt_load->setEnabled(false);
            ui->bt_save->setEnabled(false);
#if !defined(DEMO_VERSION)
            ui->but_export->setEnabled(true);
#endif
            //ui->but_exp_stat->setEnabled(true);
            ui->but_del_files->setEnabled(false);
            ui->but_del_dirs->setEnabled(false);
            break;
    }
}

void MainWindow::on_bt_help_clicked()
{
    QString text;
    text = p_name + " " + p_vers + "\n" + tr(QT_TR_NOOP("Info: ")) + p_contact + "\n" + p_website;
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::on_bt_save_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    QString fileName = m_game_data.filename;

    if( m_game_data.game_end ){
        if ( !fileName.isNull() ) {
            QString       str, nbr;

            QFile data(fileName);
            if (data.open(QFile::ReadWrite)) {
                this->store_game_data(data);
                m_team->store_team(data);
                m_sco->store_match(data);
                data.close();
            }
        }
    }else{
      QMessageBox msgBox;
      QString text = tr(QT_TR_NOOP("Match is not yet finished"));
      msgBox.setText(text);
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
    }
#endif
}

void MainWindow::on_bt_load_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    QString fileName = Utility::selectFile(this,".","*.gme", tr("Load game"), tr("game to load:"));
    if ( fileName.size() > 0 ) {
        QFile data(fileName);
        if (data.open(QFile::ReadOnly)) {
            if( this->load_game_data(data) ){
                int players, error;
                QString firstErr;
                data.seek(0);
                error = m_team->load_team(data,players,firstErr,teamselection::load);
                if( error == 0 ){
                    data.seek(0);
                    m_sco->load_match(data,m_play);
                    data.close();
                    m_game_data.filename = fileName;
                    m_game_data.game_end = true;
                    m_status = VIEW_ONLY; //TEAM_LOADED;
                    update_status();
                    m_loaded_file = fileName;
                }else{
                    QMessageBox msgBox;
                    QString text = tr("Bad data, last error: ") + firstErr;
                    msgBox.setText(text);
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                }
            }
        }
    }else{
        QMessageBox msgBox;
        QString text = tr("No game present");
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
#endif
}

void MainWindow::closeEvent(QCloseEvent *event)
{
     if (ask_exit_confirm()) {
         event->accept();
     } else {
         event->ignore();
     }
}

bool MainWindow::ask_exit_confirm()
{
     bool retV = false;
     QMessageBox msgBox;
     QString text = tr("Confirm exit ?");
     msgBox.setText(text);
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Ok);
     int ret = msgBox.exec();
     if( ret == QMessageBox::Ok){
         retV = true;
     }
     return retV;
}

void MainWindow::on_but_export_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else    
    if( m_game_data.game_end ){
        QString    msg1, msg2, msg3;
        QStringList list;
        const char *formats[] = {
          QT_TR_NOOP("play by play"),
          QT_TR_NOOP("stat"),
          QT_TR_NOOP("html"),
          QT_TR_NOOP("numeric"),
        };
        list.append(tr(formats[0]));
        list.append(tr(formats[1]));
        list.append(tr(formats[2]));
        list.append(tr(formats[3]));

        msg1 = tr("Export format");
        msg2 = tr("Select export format: ");
        if( list.size() > 0 ){
            bool ok;
            QString item = QInputDialog::getItem(this, msg1, msg2, list, 0, false, &ok);
            if (ok && !item.isEmpty()){
                if( item == tr(formats[0]) ){
                    export_hr_info(HR_PBP);
                }else if( item == tr(formats[1]) ){
                    export_hr_info(HR_STAT);
                }else if( item == tr(formats[2]) ){
                    export_hr_info(HR_HTML);
                }else if( item == tr(formats[3]) ){
                    export_hr_info(HR_NUMERIC);
                }
            }
        }
    }else{
      QMessageBox msgBox;
      QString text = tr(QT_TR_NOOP("Match is not yet finished"));
      msgBox.setText(text);
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
    }
#endif
}

void MainWindow::on_but_exp_stat_clicked()
{
#if 0
    if( m_game_data.game_end ){
        export_hr_info(HR_STAT);
    }else{
      QMessageBox msgBox;
      QString text = tr(QT_TR_NOOP("Match is not yet finished"));
      msgBox.setText(text);
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
    }
#endif
}

void MainWindow::export_hr_info( int type )
{
    bool remove_src = true;
    if( m_status == FIELD_OK || m_status == VIEW_ONLY )
    {
        QFileInfo basefile(m_game_data.filename);
        QString o_fileName;
        if( type == HR_PBP ){
            o_fileName = basefile.completeBaseName() + "_pbp.html"; //".csv";
        }else if( type == HR_STAT ){
            o_fileName = basefile.completeBaseName() + "_stat.csv";
        }else if( type == HR_HTML ){
            o_fileName = basefile.completeBaseName() + "_stat.html";
        }else if( type == HR_NUMERIC ){
            o_fileName = basefile.completeBaseName() + ".gme";
        }else{
            return;
        }
        QString charset = GetActualCharset();
        QString statfile = basefile.canonicalPath() + "/" + o_fileName;
        m_export_dir = m_options->GetExportDirectory();
        QString newdest = m_export_dir;
        if( !newdest.endsWith("/") ){
            newdest += "/";
        }
        newdest += o_fileName;

        QFile src(o_fileName);
        if (src.open(QFile::ReadWrite)) {
            if( type == HR_PBP ){
                // m_sco->store_pbp(src,m_play,&players_registry);
                m_sco->store_pbp_in_html(src,m_play,&players_registry,charset);
            }else if( type == HR_STAT ){
                m_sco->store_stat(src,&players_registry);
            }else if( type == HR_HTML ){
                m_sco->store_html(src,m_players,&players_registry,charset);
            }else if( type == HR_NUMERIC ){
                remove_src = false;
                // copia il .gme nella cartella di export
            }
            src.close();
            QMessageBox msgBox;
            QFile dst(newdest);
            if( dst.exists() ){
              dst.remove();
            }
            if( src.copy(newdest) == false ){
                QString msg = tr("export to ") + newdest + tr(" failed");
                msgBox.setText(msg);
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
            }else{
                QString msg = tr("export to ") + newdest + tr(" done");
                msgBox.setText(msg);
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
            }
            if( remove_src ){
                src.remove();
            }
        }
    }
}

void MainWindow::on_but_del_files_clicked()
{
#if defined(DEMO_VERSION)
    warnForVersion();
#else
    QString    msg1, msg2, msg3, file2bedeleted;
    QStringList list;
    const char *formats[] = {
      QT_TR_NOOP("team"),
      QT_TR_NOOP("match"),
    };
    list.append(tr(formats[0]));
    list.append(tr(formats[1]));

    msg1 = tr("Delete data");
    msg2 = tr("Select data to delete: ");
    if( list.size() > 0 ){
        bool ok;
        QString item = QInputDialog::getItem(this, msg1, msg2, list, 0, false, &ok);
        if (ok && !item.isEmpty()){
            if( item == tr(formats[0]) ){
                file2bedeleted = Utility::selectFile(this,".","*.tm", tr("Delete team"), tr("team to delete:"));
            }else if( item == tr(formats[1]) ){
                file2bedeleted = Utility::selectFile(this,".","*.gme", tr("Delete game"), tr("game to delete:"));
            }
            if ( file2bedeleted.size() > 0 ) {
                QMessageBox msgBox;
                QString text = tr("Confirm to delete ") + file2bedeleted + " ?";
                msgBox.setText(text);
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int ret = msgBox.exec();
                if( ret == QMessageBox::Ok){
                    QFile src(file2bedeleted);
                    src.remove();
                }
            }else{
                QMessageBox msgBox;
                QString text = tr("No data selected");
                msgBox.setText(text);
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
            }
        }
    }
#endif
}

void MainWindow::on_but_options_clicked()
{
    m_options->showNormal();
    m_export_dir = m_options->GetExportDirectory();
}

void MainWindow::on_but_del_dirs_clicked()
{
}

void MainWindow::warnForVersion()
{
    QMessageBox msgBox;
    QString text = tr(QT_TR_NOOP("Feature available only in bkstat full"));
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::store_game_data(QFile &data)
{
    int otherPoints; /* = QInputDialog::getInt(
      NULL,
      tr(QT_TR_NOOP("points:")),
      tr(QT_TR_NOOP("Input other team points")),
      0, 0, 200, 1 ); */
    otherPoints = m_sco->GetScore(ifStore::oth_points);
    QTextStream out(&data);
    m_game_data.other_team_points = otherPoints;
    out << "D" << p_resource_prefix << "," << p_vers << "," << m_game_data.m_quarter_duration << "," << m_game_data.m_overtime_duration << "," << m_game_data.faul_bonus << "," << m_game_data.this_team << "," << m_game_data.game_desc << "," << otherPoints << "," << m_game_data.datestring << "," << m_game_data.game_id << "," << m_game_data.location << "\n";
}

bool MainWindow::load_game_data(QFile &data)
{
    bool        rVal = true;
    QTextStream stream(&data);
    QString     line;
    QRegExp     *separator;
    separator = new QRegExp("[,;]");
    do {
        bool ok;
        line = stream.readLine();
        if( line[0] == 'D' ){
            line.remove(0,1);
            QStringList list1 = line.split(*separator);
            if( list1[0] == p_resource_prefix ){
                m_game_data.m_quarter_duration = list1[2].toInt(&ok, 10);
                m_game_data.m_overtime_duration = list1[3].toInt(&ok, 10);
                m_game_data.faul_bonus = list1[4].toInt(&ok, 10);
                m_game_data.this_team = list1[5];
                m_game_data.game_desc = list1[6];
                m_game_data.other_team_points = list1[7].toInt(&ok, 10);
                m_game_data.datestring = list1[8];
                m_game_data.game_id = list1[9];
                m_game_data.location = list1[10];
            }else{
                rVal = false;
            }
        }
    } while (!line.isNull());
    return rVal;
}

void MainWindow::on_bt_exit_clicked()
{

}

QString MainWindow::GetActualCharset()
{
    QString cs = "UTF-8";
    if( m_current_language == "it" ||
        m_current_language == "fr" ||
        m_current_language == "es" || m_current_language == "pt"
        || m_current_language == "de"){
        cs = "ISO-8859-1";
    }else if( m_current_language == "ru" ){
        cs = "ISO-8859-5";
    }
    return cs;
}
