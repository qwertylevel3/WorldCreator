#include "effectmanager.h"
#include"effect/effect.h"
#include<QDir>
#include<QDebug>

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{

}

void EffectManager::init(QGraphicsScene* s,const QString& worldName)
{
    scene=s;
    read(worldName);
}

bool EffectManager::read(const QString& worldName)
{

    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"effect.ini";

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
        Effect* e=new Effect(worldName,name,0);
        prototype[name]=e;
    }

}

void EffectManager::update()
{
    for(int i=0;i<allEffect.size();i++)
    {
        allEffect[i]->update();
        if(!scene->sceneRect().contains(allEffect[i]->pos()))
        {
            scene->removeItem(allEffect[i]);
            delete allEffect[i];
            allEffect.removeAt(i);
        }
        if(allEffect[i]->scene()==0)
        {
            allEffect.removeAt(i);
        }
    }
}

Sprite* EffectManager::add(Sprite *p)
{
    return addEffect(p->getName());
}

void EffectManager::setShowRect(bool s)
{
    for(int i=0;i<allEffect.size();i++)
    {
        allEffect[i]->setShowRect(s);
    }
}

Effect* EffectManager::addEffect(const QString &name)
{
    Effect* e=prototype[name]->clone();
    allEffect.push_back(e);
    e->setManager(this);
    scene->addItem(e);
    return e;
}

void EffectManager::clear()
{
    for(QList<Effect*>::iterator i=allEffect.begin();i!=allEffect.end();i++)
    {
        scene->removeItem(*i);
    }
    allEffect.clear();
}
