#include "missionmanager.h"
#include"mission.h"
#include<QDir>
#include<QDebug>

MissionManager::MissionManager()
{

}

MissionManager::~MissionManager()
{

}

void MissionManager::start(int index)
{
    if(index>=0 && index<allMission.size())
    {
        allMission[index]->start();
    }
}

void MissionManager::end(int index)
{
    if(index>=0 && index<allMission.size())
    {
        allMission[index]->end();
    }
}

void  MissionManager::init(const QString& worldName)
{
    read(worldName);
}

bool MissionManager::read(const QString& worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"mission.ini";

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not find file:"<<path<<"data.dat"<<endl;
        return false;
    }
    QTextStream in(&file);
    in>>missionNumber;

    for(int i=0;i<missionNumber;i++)
    {
        QString name;
        in>>name;
        Mission* m=new Mission(worldName,name);
        allMission.push_back(m);
    }
}
