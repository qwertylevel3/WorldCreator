#include "charactermanager.h"
#include"game.h"
#include"manager/terrainmanager.h"
#include"character/character.h"
#include"character/player.h"
#include<QDir>
#include<QDebug>

CharacterManager::CharacterManager()
{

}

CharacterManager::~CharacterManager()
{

}

void CharacterManager::init(QGraphicsScene* s, QString &worldName)
{
    scene=s;
    read(worldName);
}

bool CharacterManager::read(QString &worldName)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"character.ini";

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
        Character* c=new Character(worldName,name,0);
        prototype[name]=c;
    }
}

void CharacterManager::update()
{
    for(int i=0;i<allCharacter.size();i++)
    {
        allCharacter[i]->update();
    }
}


Character* CharacterManager::addCharacter(const QString& name)
{
    Character* c=prototype[name]->clone();
    scene->addItem(c);
    allCharacter.push_back(c);
    return c;
}

Player* CharacterManager::addPlayer(Player* p)
{
    allCharacter.insert(0,p);
    scene->addItem(p);
    return p;
}


void CharacterManager::clear()
{
    for(int i=1;i<allCharacter.size();i++)
    {
        scene->removeItem(allCharacter[i]);
    }
    allCharacter.clear();
}
