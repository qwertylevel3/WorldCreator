#include "bulletmanager.h"
#include"manager/charactermanager.h"
#include"game.h"
#include"manager/effectmanager.h"
#include"effect/effect.h"
#include<QDir>
#include<QDebug>

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{

}

void BulletManager::init(QGraphicsScene *s,const QString& worldName)
{
    scene=s;
    read(worldName);
}
bool BulletManager::read(const QString& worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"bullet.ini";

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
        Bullet* b=new Bullet(worldName,name,0);
        prototype[name]=b;
    }
}

void BulletManager::update()
{
    for(int i=0;i<allBullet.size();i++)
    {
        allBullet[i]->update();
    }
}

//添加bullet，返回指针，便于修改
Bullet *BulletManager::addBullet(const QString &name)
{
    Bullet* b=prototype[name]->clone();
    allBullet.push_back(b);
    scene->addItem(b);
    return b;
}

void BulletManager::clear()
{
    for(QList<Bullet*>::iterator i=allBullet.begin();i<allBullet.end();i++)
    {
        scene->removeItem(*i);
    }
    allBullet.clear();
}
