#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<QSettings>
#include<QMessageBox>
#include<QFileInfo>
#include<QFileDialog>
#include<QCloseEvent>
#include"game.h"
#include<QDebug>
#include<QDockWidget>
#include<QListWidget>
#include"world.h"
#include<QDialog>
#include<QInputDialog>
#include"spritepanel.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world=new World();
    //world->init(QString("common"));
    //Game::instance()->init(QString("common"));

    //QGraphicsView* view=new QGraphicsView();
    this->setCentralWidget(world->getView());
    //this->setCentralWidget(world->getView());
    this->resize(1000,700);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    createDockWindow();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");

    connect(world,SIGNAL(modified()),this,SLOT(worldModified()));
    connect(terrainWidget,SIGNAL(addSprite()),this,SLOT(worldModified()));
    connect(characterWidget,SIGNAL(addSprite()),this,SLOT(worldModified()));
    connect(decorationWidget,SIGNAL(addSprite()),this,SLOT(worldModified()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
     contextMenu->exec(QCursor::pos());
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newWorld()
{
    if (okToContinue()) {
        world->clear();

        bool ok;
        QString fileName = QInputDialog::getText(this, tr("create new world"),
                                             tr("world name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !fileName.isEmpty())
        {
            world->createNewWorld(fileName);
            qDebug()<<world->getWorldName();
            setCurrentFile(world->getWorldName());
            updateDockWindow();
        }
    }
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open World"), ".",
                                                        tr("World files (*.wod)"));
        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            curFile=world->getWorldName();
            updateDockWindow();
        }

    }

}

void MainWindow::closeWorld()
{
    if(okToContinue())
    {
        world->close();
        clearDockWindow();
    }
    setCurrentFile("");
}

bool MainWindow::save()
{
    if(curFile!="")
    {
        return saveFile(curFile);
    }
    return false;
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About WorldCreator"),
            tr("<h2>WorldCreator 0.1</h2>"
               "<p>Copyright &copy; 2015 qwertylevel3"
               "<p>WorldCreator is a small application that "
               "you can create a small 2d game "
               "<p>If any question : qwertylevel3@126.com"));

}

void MainWindow::openRecentFile()
{
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
        {
            loadFile(action->data().toString());
            curFile=world->getWorldName();
            updateDockWindow();
        }

    }
}

void MainWindow::updateStatusBar()
{
    statusLabel->setText("world update...");
}

void MainWindow::worldModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new world"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newWorld()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the world to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    closeAction=new QAction(tr("Close"),this);
    closeAction->setStatusTip(tr("close the world"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(closeWorld()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current sprite "
                               "to the clipboard"));
    connect(cutAction, SIGNAL(triggered()), world, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current sprite "
                                "to the clipboard"));
    connect(copyAction, SIGNAL(triggered()), world, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the sprite into "
                                 "the current world"));
    connect(pasteAction, SIGNAL(triggered()),
            world, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's sprite"));

    connect(deleteAction, SIGNAL(triggered()),
            world, SLOT(del()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(world->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the world's "
                                    "grid"));
    connect(showGridAction, SIGNAL(toggled(bool)),
            world, SLOT(setShowGrid(bool)));

    simulateGravity = new QAction(tr("&Simulate Gravity"), this);
    simulateGravity->setCheckable(true);
    simulateGravity->setChecked(world->getSimulateGravity());
    simulateGravity->setStatusTip(tr("Switch simulate gravity on or "
                                      "off"));
    connect(simulateGravity, SIGNAL(toggled(bool)),
            world, SLOT(setSimulateGravity(bool)));

    characterSelectable=new QAction(tr("set character selectable"),this);
    characterSelectable->setCheckable(true);
    characterSelectable->setChecked(world->getCharacterSelectable());
    characterSelectable->setStatusTip(tr("Switch character selectable on or off"));
    connect(characterSelectable,SIGNAL(toggled(bool)),world,SLOT(setCharacterDragable(bool)));

    terrainSelectable=new QAction(tr("set terrain selectable"),this);
    terrainSelectable->setCheckable(true);
    terrainSelectable->setChecked(world->getTerrainSelectable());
    terrainSelectable->setStatusTip(tr("Switch terrain selectable on or off"));
    connect(terrainSelectable,SIGNAL(toggled(bool)),world,SLOT(setTerrainDragable(bool)));

    decorationSelectable=new QAction(tr("set decoration selectable"),this);
    decorationSelectable->setCheckable(true);
    decorationSelectable->setChecked(world->getDecorationSelectable());
    decorationSelectable->setStatusTip(tr("Switch decoration selectable on or off"));
    connect(decorationSelectable,SIGNAL(toggled(bool)),world,SLOT(setDecorationDragable(bool)));

    showRect=new QAction(tr("show collision rect"),this);
    showRect->setCheckable(true);
    showRect->setChecked(world->getShowRect());
    showRect->setStatusTip(tr("Switch show collision rect"));
    connect(showRect,SIGNAL(toggled(bool)),world,SLOT(setShowRect(bool)));

    spriteSettingAction=new QAction(tr("setting"),this);
    spriteSettingAction->setStatusTip(tr("open sprite setting panel"));
    connect(spriteSettingAction,SIGNAL(triggered()),world,SLOT(spriteSetting()));

    worldDescriptionAction=new QAction(tr("world description"),this);
    worldDescriptionAction->setStatusTip(tr("set the world description"));
    connect(worldDescriptionAction,SIGNAL(triggered()),world,SLOT(worldDescription()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File(&F)"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit(&E)"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    editMenu->addSeparator();
//    editMenu->addAction(findAction);
//    editMenu->addAction(goToCellAction);

    propertyMenu = menuBar()->addMenu(tr("Property(&P)"));
    propertyMenu->addAction(worldDescriptionAction);
//    toolsMenu->addAction(recalculateAction);
//    toolsMenu->addAction(sortAction);
    moduleMenu = menuBar()->addMenu(tr("Module(&M)"));

    optionsMenu = menuBar()->addMenu(tr("Options(&O)"));
    optionsMenu->addAction(simulateGravity);
    optionsMenu->addAction(characterSelectable);
    optionsMenu->addAction(decorationSelectable);
    optionsMenu->addAction(terrainSelectable);
    optionsMenu->addAction(showRect);



    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    contextMenu=new QMenu(this);
    contextMenu->addAction(cutAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);
    contextMenu->addSeparator();
    contextMenu->addAction(spriteSettingAction);
}

void MainWindow::createContextMenu()
{
//    world->addAction(cutAction);
//    world->addAction(copyAction);
//    world->addAction(pasteAction);
    //spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->setObjectName("fileToolBar");

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->setObjectName("editToolBar");

}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel;
    statusLabel->setIndent(3);

    statusBar()->addWidget(statusLabel);

//    connect(spreadsheet, SIGNAL(modified()),
//            this, SLOT(spreadsheetModified()));

    updateStatusBar();
}

void MainWindow::createDockWindow()
{
    terrainWidget=new TerrainPanel(this);
    characterWidget=new CharacterPanel(this);
    decorationWidget=new DecorationPanel(this);


    terrainDockWidget=new QDockWidget(tr("terrain"));
    terrainDockWidget->setObjectName("terrain");
    terrainDockWidget->setWidget(terrainWidget);
    addDockWidget(Qt::RightDockWidgetArea,terrainDockWidget);

    characterDockWidget=new QDockWidget(tr("character"));
    characterDockWidget->setObjectName("character");
    characterDockWidget->setWidget(characterWidget);
    addDockWidget(Qt::RightDockWidgetArea,characterDockWidget);

    decorationDockWidget=new QDockWidget(tr("decoration"));
    decorationDockWidget->setObjectName("decoration");
    decorationDockWidget->setWidget(decorationWidget);
    addDockWidget(Qt::RightDockWidgetArea,decorationDockWidget);

}

void MainWindow::readSettings()
{
    QSettings settings("qwertylevel3", "world");

    settings.beginGroup("mainwindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());
    recentFiles = settings.value("recentFiles").toStringList();
    settings.endGroup();
    updateRecentFileActions();
}

void MainWindow::writeSettings()
{
    QSettings settings("qwertylevel3", "world");

    settings.beginGroup("mainwindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state",saveState());
    settings.setValue("recentFiles", recentFiles);
    settings.endGroup();
}

bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("World"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!world->loadFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);

    this->setCentralWidget(world->getView());
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!world->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    if (!curFile.isEmpty()) {
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(curFile)
                                   .arg(tr("World")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2")
                           .arg(j + 1)
                           .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateDockWindow()
{
    characterWidget->update();
    terrainWidget->update();
    decorationWidget->update();
}

void MainWindow::clearDockWindow()
{
    characterWidget->clear();
    terrainWidget->clear();
    decorationWidget->clear();
}
