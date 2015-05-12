#include "mission.h"
#include<QDebug>
#include"manager/terrainmanager.h"
#include"manager/decorationmanager.h"
#include"manager/charactermanager.h"
#include"character/player.h"
#include"game.h"
#include<QDir>


Mission::Mission(const QString &worldName, const QString &name)
    :worldName(worldName),name(name)
{
}

Mission::~Mission()
{

}

void Mission::start()
{
    load();
    //Player* p=new Player("common","koakuma",Game::instance()->getView());
    //CharacterManager::instance()->addPlayer(p);
    //p->setPos(0,-100);
}

int Mission::run()
{
    return 0;
}

void Mission::end()
{
    TerrainManager::instance()->clear();
    DecorationManager::instance()->clear();
    CharacterManager::instance()->clear();
}


bool Mission::load()
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"mission"
            +QDir::separator()+name;
    

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not find file:"<<path<<"data.dat"<<endl;
        return false;
    }
    QTextStream in(&file);   
    
    in>>G>>T;
    
    bool loadSuccess=false;
	loadSuccess=loadTerrain(in);
    if(!loadSuccess)
    {
 		qDebug()<<"load terrain fail"<<endl;
        return false;
    }
    loadSuccess=loadDecoration(in);
    if(!loadSuccess)
    {
        qDebug()<<"load decoration fail"<<endl;
        return false;
    }
 	loadSuccess=loadCharacter(in);
    if(!loadSuccess)
    {
        qDebug()<<"load character fail"<<endl;
        return false;
    }

    return true;
}

bool Mission::loadTerrain(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Terrain* t=TerrainManager::instance()->addTerrain(name);
        int x,y;
        in>>x>>y;
        t->setPos(x,y);
    }
    return true;
}

bool Mission::loadCharacter(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Character* c=CharacterManager::instance()->addCharacter(name);
        QString type;
        in>>type;
        if(type=="Enemy")
        {
            c->setType(Character::Enemy);
        }
        else if(type=="NPC")
        {
            c->setType(Character::NPC);
        }
        else if(type=="Player")
        {
            qDebug()<<"error to add player"<<endl;
        }
        else
        {
            qDebug()<<"unknow type"<<endl;
        }
        int x,y;
        in>>x>>y;
        c->setPos(x,y);
    }
    return true;
}

bool Mission::loadDecoration(QTextStream& in)
{
    int num;
    in>>num;
    for(int i=0;i<num;i++)
    {
        QString name;
        in>>name;
        Decoration* d=DecorationManager::instance()->addDecoration(name);
        int x,y;
        in>>x>>y;
        d->setPos(x,y);
    }
    return true;
}
