#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include"game.h"

class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void worldModified();

    QString strippedName(const QString &fullFileName);

    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void setCurrentFile(const QString& fileName);
    void updateRecentFileActions();
    QStringList recentFiles;
    QString curFile;
    enum {MaxRecentFiles=5};
    QAction* recentFileActions[MaxRecentFiles];
    QAction* separatorAction;

    QLabel* statusLabel;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* selectSubMenu;
    QMenu* propertyMenu;
    QMenu* moduleMenu;
    QMenu* windowMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QAction *showGridAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void openRecentFile();
    void updateStatusBar();


};

#endif // MAINWINDOW_H
