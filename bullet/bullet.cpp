#include "bullet.h"

#include"skill/restore.h"
#include<QDir>
#include<QTextStream>
#include<QDebug>

Bullet::Bullet(const QString &worldName,const QString &name,GraphicsView* rec,QGraphicsItem * parent)
    :Sprite(worldName,name,rec,parent)
{
    read(worldName,name);
    dragable=false;

    Restore* restore=new Restore(this,0);
    skillBox.push_back(restore);

    vx=0;
    vy=0;
}

Bullet::~Bullet()
{

}

Bullet* Bullet::clone()
{
    Bullet* p=new Bullet;
    p->setZValue(this->zValue());

    //setTransformOriginPoint(boundingRect().center());
    p->setCurrState(0);
    p->setCurrSkill(0);
    p->setOrientation(1);
    p->setDragable(isDragable());
    p->setStateTotal(stateTotal);
    
    for(int i=0;i<stateBox.size();i++)
    {
        State* state=new State(stateBox[i]);
        state->setSprite(p);
        p->getStateBox().push_back(state);
    }

    Restore* restore=new Restore(p,0);
    p->getSkillBox().push_back(restore);
    p->setVx(0);
    p->setVy(0);
    p->setName(name);

    return p;
}

bool Bullet::read(const QString &worldName, const QString &name)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"sprite"
            +QDir::separator()+"bullet"
            +QDir::separator()+name
            +QDir::separator()+"data.dat";

    QFile file(path);

    //qDebug()<<path<<endl;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"can not find file:"<<path<<"data.dat"<<endl;
        return false;
    }
    QTextStream in(&file);

    int z;
    in>>z;
    this->setZValue(z);

    in>>stateTotal;
    for(int i=0;i<stateTotal;i++)
    {
        State* state=new State(this);
        state->read(in);
        stateBox.push_back(state);
    }
    return true;
}

