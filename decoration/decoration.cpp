#include "decoration.h"
#include"skill/restore.h"
#include<QDir>
#include<QTextStream>
#include<QDebug>
#include"decorationsettingdialog.h"

Decoration::Decoration(const QString &worldName,const QString &name,GraphicsView* rec,QGraphicsItem * parent)
    :Sprite(worldName,name,rec,parent)
{
    read(worldName,name);

    Restore* restore=new Restore(this,0);
    skillBox.push_back(restore);
}

Decoration::~Decoration()
{

}

Decoration* Decoration::clone()
{
    Decoration* p=new Decoration();
    p->setZValue(zValue());

    p->setCurrState(0);
    p->setCurrSkill(0);
    p->setOrientation(1);
    p->setName(name);
    p->setStateTotal(stateTotal);
    p->setDragable(dragable);
    p->setShowRect(showRect);

    for(int i=0;i<stateTotal;i++)
    {
        State* state=new State(stateBox[i]);
        state->setSprite(p);
        p->getStateBox().push_back(state);
    }
    Restore* restore=new Restore(p,0);
    p->getSkillBox().push_back(restore);

    return p;
}

void Decoration::setting()
{
    DecorationSettingDialog dialog(this);
    if(dialog.exec())
    {
        this->setZValue(dialog.getZValue());
    }
}

bool Decoration::read(const QString &worldName, const QString &name)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"sprite"
            +QDir::separator()+"decoration"
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

