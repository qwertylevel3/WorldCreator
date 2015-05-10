#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<QSettings>
#include<QMessageBox>
#include<QFileInfo>
#include<QFileDialog>
#include<QCloseEvent>
#include"game.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game::instance()->init(QString("common"));

    //QGraphicsView* view=new QGraphicsView();
    this->setCentralWidget(Game::instance()->getView());
    this->resize(1000,700);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");

    Game::instance()->start();

}


MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::newFile()
{
    if (okToContinue()) {
        //spreadsheet->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open World"), ".",
                                   tr("World files (*.wod)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Save Spreadsheet"), ".",
                               tr("Spreadsheet files (*.sp)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
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
            loadFile(action->data().toString());
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
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

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

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setStatusTip(tr("Save the world under a new "
                                  "name"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

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

//    cutAction = new QAction(tr("Cu&t"), this);
//    cutAction->setIcon(QIcon(":/images/cut.png"));
//    cutAction->setShortcut(QKeySequence::Cut);
//    cutAction->setStatusTip(tr("Cut the current sprite "
//                               "to the clipboard"));
//    connect(cutAction, SIGNAL(triggered()), world, SLOT(cut()));

//    copyAction = new QAction(tr("&Copy"), this);
//    copyAction->setIcon(QIcon(":/images/copy.png"));
//    copyAction->setShortcut(QKeySequence::Copy);
//    copyAction->setStatusTip(tr("Copy the current sprite "
//                                "to the clipboard"));
//    connect(copyAction, SIGNAL(triggered()), world, SLOT(copy()));

//    pasteAction = new QAction(tr("&Paste"), this);
//    pasteAction->setIcon(QIcon(":/images/paste.png"));
//    pasteAction->setShortcut(QKeySequence::Paste);
//    pasteAction->setStatusTip(tr("Paste the sprite into "
//                                 "the current world"));
//    connect(pasteAction, SIGNAL(triggered()),
//            world, SLOT(paste()));

//    deleteAction = new QAction(tr("&Delete"), this);
//    deleteAction->setShortcut(QKeySequence::Delete);
//    deleteAction->setStatusTip(tr("Delete the current selection's sprite"));

//    connect(deleteAction, SIGNAL(triggered()),
//            world, SLOT(del()));

//    showGridAction = new QAction(tr("&Show Grid"), this);
//    showGridAction->setCheckable(true);
//    showGridAction->setChecked(spreadsheet->showGrid());
//    showGridAction->setStatusTip(tr("Show or hide the world's "
//                                    "grid"));
//    connect(showGridAction, SIGNAL(toggled(bool)),
//            spreadsheet, SLOT(setShowGrid(bool)));


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
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit(&E)"));
//    editMenu->addAction(cutAction);
//    editMenu->addAction(copyAction);
//    editMenu->addAction(pasteAction);
//    editMenu->addAction(deleteAction);

    editMenu->addSeparator();
//    editMenu->addAction(findAction);
//    editMenu->addAction(goToCellAction);

    propertyMenu = menuBar()->addMenu(tr("Property(&P)"));
//    toolsMenu->addAction(recalculateAction);
//    toolsMenu->addAction(sortAction);
    moduleMenu = menuBar()->addMenu(tr("Module(&M)"));

    windowMenu = menuBar()->addMenu(tr("Window(&W)"));

    optionsMenu = menuBar()->addMenu(tr("Options(&O)"));
    //optionsMenu->addAction(showGridAction);
    //optionsMenu->addAction(autoRecalcAction);



    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
//    spreadsheet->addAction(cutAction);
//    spreadsheet->addAction(copyAction);
//    spreadsheet->addAction(pasteAction);
    //spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
//    editToolBar->addAction(cutAction);
//    editToolBar->addAction(copyAction);
//    editToolBar->addAction(pasteAction);
//    editToolBar->addSeparator();
//    editToolBar->addAction(findAction);
//    editToolBar->addAction(goToCellAction);
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

void MainWindow::readSettings()
{
    QSettings settings("qwertylevel3", "world");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

//    bool showGrid = settings.value("showGrid", true).toBool();
//    showGridAction->setChecked(showGrid);

//    bool autoRecalc = settings.value("autoRecalc", true).toBool();
//    autoRecalcAction->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
    QSettings settings("qwertylevel3", "world");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
//    settings.setValue("showGrid", showGridAction->isChecked());
//    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
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
//    if (!spreadsheet->readFile(fileName)) {
//        statusBar()->showMessage(tr("Loading canceled"), 2000);
//        return false;
//    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
//    if (!spreadsheet->writeFile(fileName)) {
//        statusBar()->showMessage(tr("Saving canceled"), 2000);
//        return false;
//    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName)
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
