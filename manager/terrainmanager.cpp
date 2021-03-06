#include "terrainmanager.h"
#include<QDir>
#include<QDebug>

TerrainManager::TerrainManager()
{

}

TerrainManager::~TerrainManager()
{

}
void TerrainManager::init(QGraphicsScene* s, QString &worldName)
{
    scene=s;
    read(worldName);
}

bool TerrainManager::read(QString &worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"terrain.ini";

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not find file:"<<path<<"data.dat"<<endl;
        return false;
    }
    QTextStream in(&file);
    int totalNumber;
    in>>totalNumber;

    for(int i=0;i<totalNumber;i++)
    {
        QString name;
        in>>name;

        Terrain* t=new Terrain(worldName,name,0);
        prototype[name]=t;

    }
}

Sprite *TerrainManager::add(Sprite *p)
{
    Terrain* t=qobject_cast<Terrain*>(p->clone());
    allTerrain.push_back(t);
    t->setManager(this);
    scene->addItem(t);
    return t;
}

void TerrainManager::setShowRect(bool s)
{
    for(int i=0;i<allTerrain.size();i++)
    {
        allTerrain[i]->setShowRect(s);
    }
}

void TerrainManager::update()
{
    for(int i=0;i<allTerrain.size();i++)
    {
        allTerrain[i]->update();
        if(allTerrain[i]->isSelected())
        {
            emit selected(allTerrain[i]);
        }
        if(allTerrain[i]->scene()==0)
        {
            allTerrain.removeAt(i);
        }
    }
}

Terrain *TerrainManager::addTerrain(const QString &name)
{
    Terrain* t=prototype[name]->clone();
    allTerrain.push_back(t);
    t->setManager(this);
    scene->addItem(t);
    return t;
}

void TerrainManager::clear()
{
    for(int i=0;i<allTerrain.size();i++)
    {
        scene->removeItem(allTerrain[i]);
    }
    allTerrain.clear();
}
