#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include"terrain/terrain.h"
#include<QList>
#include<QMap>
#include"manager/manager.h"
#include<QObject>

class TerrainManager:public QObject,public Singleton<TerrainManager>,public Manager
{
    Q_OBJECT
public:
    TerrainManager();
    ~TerrainManager();
    void init(QGraphicsScene* s,QString& worldName);
    bool read(QString& worldName);
    void update();
    void clear();
    QList<Terrain*>& getAllTerrain(){return allTerrain;}
    int getTotalNumber(){return allTerrain.size();}
    Terrain* addTerrain(const QString& name);
    Sprite* add(Sprite *p);
    QMap<QString,Terrain*>& getPrototype(){return prototype;}
    void setShowRect(bool s);
signals:
    void selected(Sprite* p);
protected:
    QList<Terrain*> allTerrain;
    QGraphicsScene* scene;
    QMap<QString,Terrain*> prototype;
};

#endif // TERRAINMANAGER_H
