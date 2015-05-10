#ifndef WORLD_H
#define WORLD_H

#include"game.h"
#include<QObject>

class World:public QObject
{
    Q_OBJECT
public:
    World();
    ~World();
public slots:
    void cut();
    void copy();
    void paste();
    void del();
signals:
    void modified();
protected slots:
    void somethingChanged(){}
protected:
    QGraphicsScene* scene;
    GraphicsView* view;
    Sprite* currSprite;

};

#endif // WORLD_H
