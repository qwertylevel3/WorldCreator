#include "decorationmanager.h"
#include<QDir>
#include<QDebug>

DecorationManager::DecorationManager()
{

}

DecorationManager::~DecorationManager()
{

}

void DecorationManager::init(QGraphicsScene* s, QString &worldName)
{
    scene=s;
    read(worldName);
}

bool DecorationManager::read(QString &worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"decoration.ini";

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

        Decoration* t=new Decoration(worldName,name,0);
        prototype[name]=t;
    }
}


void DecorationManager::update()
{
    for(int i=0;i<allDecoration.size();i++)
    {
        allDecoration[i]->update();
    }
}

Decoration *DecorationManager::addDecoration(const QString& name)
{
    Decoration* d=prototype[name]->clone();
    allDecoration.push_back(d);
    scene->addItem(d);
    return d;
}



void DecorationManager::clear()
{
    for(int i=0;i<allDecoration.size();i++)
    {
        scene->removeItem(allDecoration[i]);
    }
    allDecoration.clear();
}
