#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include"terrain/terrain.h"
#include<QList>
#include<QMap>

class TerrainManager:public Singleton<TerrainManager>
{
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
protected:
    QList<Terrain*> allTerrain;
    QGraphicsScene* scene;
    QMap<QString,Terrain*> prototype;
};

#endif // TERRAINMANAGER_H
