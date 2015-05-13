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
    delete p;
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
        if(allCharacter[i]->isSelected())
        {
            emit selected(allCharacter[i]);
        }
        if(!scene->sceneRect().contains(allCharacter[i]->pos()))
        {
            allCharacter[i]->setOutOfScene(true);
            allCharacter[i]->setVx(0);
            allCharacter[i]->setVy(0);
        }
        else
        {
            allCharacter[i]->setOutOfScene(false);
        }
        if(allCharacter[i]->scene()==0)
        {
            allCharacter.removeAt(i);
        }
    }
}

Sprite *CharacterManager::add(Sprite *p)
{
    return addCharacter(p->getName());
}

void CharacterManager::setShowRect(bool s)
{
    for(int i=0;i<allCharacter.size();i++)
    {
        allCharacter[i]->setShowRect(s);
    }
}


Character* CharacterManager::addCharacter(const QString& name)
{
    Character* c=prototype[name]->clone();
    c->setManager(this);
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
    for(int i=0;i<allCharacter.size();i++)
    {
        scene->removeItem(allCharacter[i]);
    }
    allCharacter.clear();
}
