#ifndef WORLD_H
#define WORLD_H

#include"game.h"
#include<QObject>
#include<QTextStream>

class Mission;

class World:public QObject
{
    Q_OBJECT
public:
    World();
    ~World();
    QGraphicsScene* getScene(){return scene;}
    GraphicsView* getView(){return view;}
    bool showGrid();
    bool writeFile(const QString &fileName);
    bool createNewWorld(const QString fileName);
    bool loadFile(const QString fileName);

    bool init(const QString& worldName);
    void clear(){}

    double getG(){return G;}
    double getT(){return T;}
    bool getSimulateGravity(){return doSimulate;}
    bool getCharacterSelectable(){return characterSelectable;}
    bool getDecorationSelectable(){return decorationSelectable;}
    bool getTerrainSelectable(){return terrainSelectable;}
    bool getShowRect(){return showRect;}


    bool loadWorld(const QString& worldName);
    bool loadTerrain(QTextStream& in);
    bool loadCharacter(QTextStream& in);
    bool loadDecoration(QTextStream& in);

    bool writeTerrain(QTextStream& out);
    bool writeCharacter(QTextStream& out);
    bool writeDecoration(QTextStream& out);

    QString getWorldName(){return worldName;}
public slots:
    void worldDescription();
    void spriteSetting();
    void cut();
    void copy();
    void close();
    void paste();
    void del();
    void addSpriteFromPanel(Sprite* p);
    void setShowGrid(bool s){}
    void setSimulateGravity(bool s);
    void update();
    void setTerrainDragable(bool d);
    void setCharacterDragable(bool d);
    void setDecorationDragable(bool d);
    void setShowRect(bool s);
signals:
    void modified();
protected slots:
    void somethingChanged();
    void setSelected(Sprite* p);
protected:
    QString worldName;
    QGraphicsScene* scene;
    GraphicsView* view;
    Sprite* currSprite;
    Sprite* spriteInClipboard;
    QTimer* timer;
    bool doSimulate;
    bool characterSelectable;
    bool terrainSelectable;
    bool decorationSelectable;

    //模拟环境
    void simulation();

    bool isCollision(Sprite* a,Sprite* b);

    bool showRect;//显示碰撞矩形

    double G;//重力加速度
    double T;//单帧时间间隔

    int misssionNumber;//关卡总数

};

#endif // WORLD_H
