#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>

class World;
class QLabel;
class QListWidget;
class QDockWidget;
class CharacterPanel;
class TerrainPanel;
class DecorationPanel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void contextMenuEvent(QContextMenuEvent *event);
private:
    Ui::MainWindow *ui;
    World* world;
    TerrainPanel* terrainWidget;
    CharacterPanel* characterWidget;
    DecorationPanel* decorationWidget;
    QDockWidget* terrainDockWidget;
    QDockWidget* characterDockWidget;
    QDockWidget* decorationDockWidget;


    void closeEvent(QCloseEvent *event);


    QString strippedName(const QString &fullFileName);

    void updateDockWindow();
    void clearDockWindow();
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void createDockWindow();
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
    QMenu* contextMenu;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* copyAction;
    QAction* closeAction;
    QAction* spriteSettingAction;
    QAction* worldDescriptionAction;

    QAction* showRect;
    QAction* characterSelectable;
    QAction* terrainSelectable;
    QAction* decorationSelectable;
    QAction* simulateGravity;
    QAction *showGridAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
private slots:
    void worldModified();
    void newWorld();
    void open();
    void closeWorld();
    bool save();
    void about();
    void openRecentFile();
    void updateStatusBar();


};

#endif // MAINWINDOW_H
