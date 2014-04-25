#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint), skype_was_killed(false)
{
    /* Back-end */
    //Settings
    settings = new QSettings("skype-mood.ini", QSettings::IniFormat, this);

    //Translation
    initTranslator();

    //History data
    history_model = new QStringListModel(settings->value("history/list").toStringList(), this);

    //Prepare SQLite connection
    maindb = QSqlDatabase::addDatabase("QSQLITE");
    maindb.setHostName("localhost");
    maindb.setUserName("root");
    maindb.setPassword("");

    /* GUI */
    //Title
    setWindowTitle("Skype Richtext Mood Editor");

    //Filling the window
    setCentralWidget(initContent());
    disableEditing();
    resize(640, 390);

    //Centering the window on the current screen
    QDesktopWidget desktop_widget;
    QRect screen_geometry = desktop_widget.availableGeometry();
    move(screen_geometry.width() / 2 - width() / 2, screen_geometry.height() / 2 - height() / 2);

    /* Looking for main.db */
    if(!listMaindb())
    {
        QMessageBox::warning(this, tr("AppData/Skype not found"), tr("There is no Skype profile for this user."));
    }
}

MainWindow::~MainWindow()
{
    //Close the database connection
    if(maindb.isOpen())
    {
        maindb.close();
    }
    QSqlDatabase::removeDatabase(maindb.connectionName());

    //Save the history
    settings->setValue("history/list", history_model->stringList());

    //Restart Skype if we killed it
    if(skype_was_killed)
    {
        QSettings registry("HKEY_CURRENT_USER\\Software\\Skype\\Phone", QSettings::NativeFormat);
        if(!QProcess::startDetached(registry.value("SkypePath").toString().prepend('"').append('"')))
        {
            QMessageBox::critical(this, tr("Unable to start Skype"), tr("Skype has not been started, sorry."));
        }
    }
}

void MainWindow::initTranslator()
{
    Q_UNUSED(QT_TRANSLATE_NOOP("meta", "language"));

    qDebug() << "Locale :" << QLocale::system().name();
    QTranslator *tr = new QTranslator(qApp);
    QString path = settings->value("ui/lang", QString(":translations/%1.qm").arg(QLocale::system().name())).toString();
    if(tr->load(path))
    {
        qApp->installTranslator(tr);
        settings->setValue("ui/lang", path);
    }
}

QWidget *MainWindow::initContent()
{
    /* Popup dialogs */
    MenuDialog *dlg_menu = new MenuDialog(settings, this);

    /* Main window content */
    //main.db path section
    cb_maindb = new QComboBox;
    cb_maindb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(cb_maindb, SIGNAL(currentIndexChanged(int)), this, SLOT(onMaindbSelected(int)));
    QPushButton *btn_maindb = new QPushButton(tr("Manual selection"));
    connect(btn_maindb, SIGNAL(clicked()), this, SLOT(browseMaindb()));

    QHBoxLayout *layout_maindb = new QHBoxLayout;
    layout_maindb->addWidget(new QLabel(tr("Skype account :")));
    layout_maindb->addWidget(cb_maindb);
    layout_maindb->addWidget(btn_maindb);

    //Mood message section
    pte_mood = new TagsPlainTextEdit;
    pte_mood->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    connect(pte_mood, SIGNAL(textChanged()), this, SLOT(onMoodTextChanged()));

    lab_mood_preview = new QLabel;
    lab_mood_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    lab_mood_preview->setWordWrap(true);
    lab_mood_preview->setOpenExternalLinks(true);
    lab_mood_preview->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    contact_preview = new SkypeContactPreview;

    QVBoxLayout *layout_preview = new QVBoxLayout;
    layout_preview->setContentsMargins(0, 0, 0, 0);
    layout_preview->addWidget(lab_mood_preview);
    layout_preview->addWidget(contact_preview);

    QHBoxLayout *layout_mood = new QHBoxLayout;
    layout_mood->addWidget(pte_mood, 56);
    layout_mood->addLayout(layout_preview, 44);

    btn_apply = new QPushButton(tr("Apply"));
    connect(btn_apply, SIGNAL(clicked()), this, SLOT(applyAndClose()));

    //History section
    history_view = new QListView;
    history_view->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    history_view->setModel(history_model);
    history_view->setItemDelegate(new HtmlDelegate(this));

    btn_history_push = new QToolButton;
    btn_history_push->setToolTip(tr("Use as mood message"));
    btn_history_push->setAutoRaise(true);
    btn_history_push->setIconSize(QSize(24, 24));
    btn_history_push->setIcon(QIcon(":img/push.png"));
    connect(btn_history_push, SIGNAL(clicked()), this, SLOT(historyPushToMood()));
    QToolButton *btn_history_rm = new QToolButton;
    btn_history_rm->setAutoRaise(true);
    btn_history_rm->setToolTip(tr("Remove from history"));
    btn_history_rm->setIconSize(QSize(24, 24));
    btn_history_rm->setIcon(QIcon(":img/rm.png"));
    connect(btn_history_rm, SIGNAL(clicked()), this, SLOT(historyRemove()));
    QToolButton *btn_history_clear = new QToolButton;
    btn_history_clear->setToolTip(tr("Clear history"));
    btn_history_clear->setAutoRaise(true);
    btn_history_clear->setIconSize(QSize(24, 24));
    btn_history_clear->setIcon(QIcon(":img/clear.png"));
    connect(btn_history_clear, SIGNAL(clicked()), this, SLOT(historyClear()));

    QPushButton *btn_menu = new QPushButton;
    btn_menu->setIconSize(QSize(24, 24));
    btn_menu->setIcon(QIcon(":img/gear.png"));
    connect(btn_menu, SIGNAL(clicked()), dlg_menu, SLOT(open()));

    QVBoxLayout *layout_history_btn = new QVBoxLayout;
    layout_history_btn->setContentsMargins(0, 0, 0, 0);
    layout_history_btn->addWidget(btn_history_push, 0, Qt::AlignCenter);
    layout_history_btn->addWidget(btn_history_rm, 0, Qt::AlignCenter);
    layout_history_btn->addWidget(btn_history_clear, 0, Qt::AlignCenter);
    layout_history_btn->addStretch();
    layout_history_btn->addWidget(btn_menu, 0, Qt::AlignCenter);

    QHBoxLayout *layout_history = new QHBoxLayout;
    layout_history->addWidget(history_view);
    layout_history->addLayout(layout_history_btn);

    //Filling the window
    QVBoxLayout *layout_main = new QVBoxLayout;
    layout_main->addLayout(layout_maindb, 1);
    layout_main->addWidget(new EntitledSeparator(tr("Mood message")), 0);
    layout_main->addLayout(layout_mood, 35);
    layout_main->addWidget(btn_apply, 0);
    layout_main->addWidget(new EntitledSeparator(tr("History")), 0);
    layout_main->addLayout(layout_history, 44);

    QWidget *container = new QWidget;
    container->setLayout(layout_main);
    return container;
}

void MainWindow::enableEditing()
{
    pte_mood->setEnabled(true);
    contact_preview->setVisible(true);
    btn_history_push->setEnabled(true);
    if(skype_was_killed)
    {
        btn_apply->setText(tr("Apply and start Skype"));
    }
    else
    {
        btn_apply->setText(tr("Apply"));
    }
}

void MainWindow::disableEditing()
{
    pte_mood->setDisabled(true);
    contact_preview->setVisible(false);
    btn_history_push->setDisabled(true);
    if(skype_was_killed)
    {
        btn_apply->setText(tr("Close and start Skype"));
    }
    else
    {
        btn_apply->setText(tr("Close"));
    }
}

//Returns true if some database was found, false otherwise
bool MainWindow::listMaindb()
{
    bool found_something = false;
    //Reading AppData path from the registry
    QSettings registry("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", QSettings::NativeFormat);
    QDir skype_data_dir(registry.value("AppData").toString().append("\\Skype"));
    if(skype_data_dir.exists())
    {
        //Listing Skype data folder
        QStringList dirs(skype_data_dir.entryList(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot));
        //Cleaning
        dirs.removeAll("Content");
        dirs.removeAll("DataRv");
        dirs.removeAll("DbTemp");
        dirs.removeAll("My Skype Received Files");
        dirs.removeAll("Pictures");
        dirs.removeAll("shared_dynco");
        dirs.removeAll("shared_httpfe");
        //Looking for main.db in subfolders
        foreach (QString dir_name, dirs)
        {
            QString maindb_path(dir_name);
            maindb_path.append("/main.db");
            if(skype_data_dir.exists(maindb_path))
            {
                //Signaling that we found something interesting
                found_something = true;
                //Populating the QComboBox with absolute path to main.db as userdata
                cb_maindb->addItem(dir_name, skype_data_dir.absoluteFilePath(maindb_path));
            }
        }
    }
    return found_something;
}

/*QString MainWindow::removeTags(QString str) const
{
    str.remove(QRegularExpression("<[^>]+>", QRegularExpression::CaseInsensitiveOption | QRegularExpression::DotMatchesEverythingOption));
    return str;
}*/

void MainWindow::browseMaindb()
{
    QString maindb = QFileDialog::getOpenFileName(this, tr("Choose a Skype user's main.db"), QString(), tr("Skype user database (main.db);;Any file (*.*)"));
    if(!maindb.isEmpty())
    {
        cb_maindb->setCurrentIndex(-1); //Without this reset, currentIndexChanged() would fire twice with real data. Now it fires first with -1 index, then with the main.db that was selected.
        cb_maindb->insertItem(0, maindb, maindb);
        cb_maindb->setCurrentIndex(0);
    }
}

//This slot does all the data loading
void MainWindow::onMaindbSelected(int index)
{
    disableEditing();
    if(maindb.isOpen())
    {
        maindb.close();
    }
    if(index > -1)
    {
        QString maindb_path(cb_maindb->itemData(index, Qt::UserRole).toString());
        QString maindb_lock(maindb_path);
        maindb_lock.replace(maindb_path.size() - 2, 2, "lock");

        //If main.db is locked (main.lock file exists)
        if(QFile::exists(maindb_lock))
        {
            //Ask the user what to do
            if(QMessageBox::warning(this, tr("main.db locked"), tr("The database is locked by Skype!"), tr("Exit Skype manually"), tr("Exit Skype for me"), QString(), 1, 0) == 1) //Dialog box returns 1 when auto-exit Skype is pressed
            {
                //If the user chose to auto-exit Skype
                if(QProcess::execute("taskkill", QStringList() << "/im" << "Skype.exe") == 0)
                {
                    skype_was_killed = true; //Used in the destructor to restart Skype
                    //Waits a maximum of 15 sec (default for MAINDB_LOCK_TIMEOUT) for the lock to be released
                    ProgressDialog *dlg_progress = new ProgressDialog(this);
                    dlg_progress->open();
                    bool unlocked = false;
                    for(int t = 0; t < MAINDB_LOCK_TIMEOUT; t++)
                    {
                        dlg_progress->progress(tr("Waiting for Skype to release the lock on the database…"), t, MAINDB_LOCK_TIMEOUT + 1);
                        QApplication::processEvents(); //Prevents freezing while blocked in the loop
                        QThread::sleep(1);
                        if(!QFile::exists(maindb_lock))
                        {
                            unlocked = true;
                            break;
                        }
                    }
                    if(unlocked)
                    {
                        dlg_progress->success();
                    }
                    else
                    {
                        dlg_progress->error(tr("main.db locked"), tr("Skype has not released the lock on the databse after 15 s."));
                    }
                    //Restart from the beginning
                    onMaindbSelected(index); //Recursively calling insures that the db is really not locked anymore
                }
                else
                {
                    QMessageBox::critical(this, tr("Unable to terminate Skype.exe"), tr("Skype is not running or has not been terminated correctly (main.lock exists)."));
                }
            }
        }

        //Else open db connection
        else
        {
            maindb.setDatabaseName(maindb_path);
            if(maindb.open())
            {
                QSqlQuery query(maindb);
                   if(query.exec("SELECT skypename, fullname, rich_mood_text, mood_timestamp, avatar_image FROM Accounts")) //profile_attachments
                   {
                       if(query.next())
                       {
                           /* Name */
                           QString fullname(query.value("fullname").toString());
                           if(fullname.isEmpty())
                           {
                               //Set the skypename as name in contact preview instead
                               contact_preview->setName(query.value("skypename").toString());
                           }
                           else
                           {
                               //Set the fullname as name in contact preview
                               contact_preview->setName(fullname);
                           }

                           /* Mood message */
                           QString mood_text(query.value("rich_mood_text").toString());
                           TagsPlainTextEdit::decodeXMLEntities(mood_text);
                           uint mood_time = query.value("mood_timestamp").toUInt();

                           //Fill the text box with the current mood
                           pte_mood->setPlainText(mood_text);

                           //Set the mood text in the contact preview
                           contact_preview->setMood(mood_text);

                           //Add current mood into history
                           if(!mood_text.isEmpty())
                           {
                               int history_index = history_model->stringList().indexOf(mood_text);
                               if(history_index == -1)
                               {
                                   history_model->insertRows(0, 1);
                                   history_model->setData(history_model->index(0), mood_text, Qt::DisplayRole);
                               }
                               else if(history_index != 0)
                               {
                                   history_model->removeRows(history_index, 1);
                                   history_model->insertRows(0, 1);
                                   history_model->setData(history_model->index(0), mood_text, Qt::DisplayRole);
                               }
                           }

                           /* Profile picture */
                           QByteArray profile_pic(query.value("avatar_image").toByteArray());

                           //Extarct JPEG picture from the BLOB
                           profile_pic.remove(0, profile_pic.indexOf(QByteArray::fromHex("FFD8")));
                           profile_pic.truncate(profile_pic.indexOf(QByteArray::fromHex("FFD9")) + 2);

                           //Set the avatar in the contact preview
                           contact_preview->setPicture(profile_pic);

                           enableEditing();
                           qDebug() << QString("Last update: %1").arg(QDateTime::fromTime_t(mood_time).toString(Qt::SystemLocaleLongDate));
                       }
                       else
                       {
                           QMessageBox::critical(this, tr("Reading query"), tr("Cannot read current mood. Please report this issue."));
                       }
                   }
                   else
                   {
                       QMessageBox::critical(this, tr("Error querying the database!"), query.lastError().text());
                   }
            }
            else
            {
                QMessageBox::critical(this, tr("Error opening the database!"), maindb.lastError().text());
            }
        }
    }
    else
    {
        pte_mood->clear();
    }
}

//Links text box with preview
void MainWindow::onMoodTextChanged()
{
    //FIXME Filter Skype size
    lab_mood_preview->setText(pte_mood->toPlainText());
    contact_preview->setMood(pte_mood->toPlainText());
}

void MainWindow::applyAndClose()
{
    if(maindb.isOpen())
    {
        QSqlQuery query(maindb);
        query.prepare("UPDATE Accounts SET mood_timestamp = ?, rich_mood_text = ? WHERE id = 1");
        query.bindValue(0, QDateTime::currentDateTime().toTime_t());
        query.bindValue(1, TagsPlainTextEdit::filterTags(pte_mood->toPlainText()));
        query.exec();
        qDebug() << TagsPlainTextEdit::filterTags(pte_mood->toPlainText());
    }
    //UPDATE "main"."Accounts" SET "mood_timestamp" = ?1, "rich_mood_text" = ?2 WHERE  "id" = 1
    close();
}

void MainWindow::historyPushToMood()
{
    QModelIndex index(history_view->currentIndex());
    if(index.isValid())
    {
        pte_mood->setPlainText(history_model->data(index, Qt::DisplayRole).toString());
    }
}

void MainWindow::historyRemove()
{
    QModelIndex index(history_view->currentIndex());
    if(index.isValid())
    {
        history_model->removeRows(index.row(), 1);
    }
}

void MainWindow::historyClear()
{
    if(QMessageBox::question(this, tr("Clear history"), tr("Are you sure you want to clear the history?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        history_model->removeRows(0, history_model->rowCount());
    }
}
