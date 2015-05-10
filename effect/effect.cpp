#include "effect.h"
#include<QDir>
#include<QDebug>
#include"skill/restore.h"

Effect::Effect(const QString &worldName,const QString &name,GraphicsView* rec,QGraphicsItem * parent)
    :Sprite(worldName,name,rec,parent)
{
    read(worldName,name);

    Restore* restore=new Restore(this,0);
    skillBox.push_back(restore);

}

Effect* Effect::clone()
{
    Effect* p=new Effect();
    p->setZValue(zValue());

    p->setCurrState(0);
    p->setCurrSkill(0);
    p->setOrientation(1);
    p->setDragable(isDragable());

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

Effect::~Effect()
{

}
bool Effect::read(const QString &worldName, const QString &name)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"sprite"
            +QDir::separator()+"effect"
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
    setZValue(z);

    in>>stateTotal;
    for(int i=0;i<stateTotal;i++)
    {
        State* state=new State(this);
        state->read(in);
        stateBox.push_back(state);
    }
    return true;
}
void Effect::skillRun(int index)
{
    if(index<skillBox.size())
    {
        //运行，发现已经结束
        if(skillBox[currSkill]->run()==0)
        {
            currSkill=0;
            currState=0;
            this->setVisible(false);
        }
    }
}
