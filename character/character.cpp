#include"character/character.h"

#include"skill/move.h"
#include"skill/restore.h"
#include"skill/sit.h"
#include"skill/jump.h"
#include"skill/shoot.h"
#include"skill/dead.h"
#include<QDir>
#include<QDebug>
#include<QKeyEvent>

Character::Character(const QString &worldName,const QString &name,GraphicsView* rec,QGraphicsItem * parent)
    :Sprite(worldName,name,rec,parent)
{
    vx=0;
    vy=0;
    oldVx=0;
    stable=true;
    type=NPC;
    outOfScene=false;

    read(worldName,name);
    Restore* restore=new Restore(this,0);
    skillBox.push_back(restore);

    Move* move=new Move(this,1);
    skillBox.push_back(move);

    Jump* jump=new Jump(this,2);
    skillBox.push_back(jump);

    Dead* dead=new Dead(this,3);
    skillBox.push_back(dead);
}

Character* Character::clone()
{
    Character* p=new Character;
    p->setZValue(zValue());
    p->setOutOfScene(this->isOutOfScene());

    p->setWeight(weight);

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

    p->setVx(vx);
    p->setVy(vy);
    p->setOldVx(oldVx);
    p->setStable(stable);
    p->setType(type);
    p->setName(name);

    Restore* restore=new Restore(p,0);
    p->getSkillBox().push_back(restore);

    Move* move=new Move(p,1);
    p->getSkillBox().push_back(move);

    Jump* jump=new Jump(p,2);
    p->getSkillBox().push_back(jump);

    Dead* dead=new Dead(p,3);
    p->getSkillBox().push_back(dead);

    return p;
}

Character::~Character()
{

}
bool Character::read(const QString &worldName, const QString &name)
{
    QString path=QDir::currentPath()
            +QDir::separator()+"world"
            +QDir::separator()+worldName
            +QDir::separator()+"sprite"
            +QDir::separator()+"character"
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

    in>>weight;

    in>>stateTotal;
    for(int i=0;i<stateTotal;i++)
    {
        State* state=new State(this);
        state->read(in);
        stateBox.push_back(state);
    }
    return true;
}


void Character::skillEnd(int index)
{
    if(index<skillBox.size())
    {
        if(skillBox[currSkill]->getPriority()<=skillBox[index]->getPriority())
        {
            //如果技能为last形，且优先级较高，立即结束，否则推迟到run中结束
            if(skillBox[currSkill]->getType()==Skill::last)
            {
                skillBox[currSkill]->end();
                if(getStable())//待命
                {
                    this->setVx(0);
                    currSkill=0;
                    currState=0;
                }
                else//跳跃
                {
                    currSkill=2;
                    currState=2;
                }
            }
        }
    }
}

void Character::skillRun(int index)
{
    if(index<skillBox.size())
    {
        //运行，发现已经结束
        if(skillBox[currSkill]->run()==0)
        {
            skillBox[currSkill]->end();
            if(getStable())//待命
            {
                this->setVx(0);
                currSkill=0;
                currState=0;
            }
            else//跳跃
            {
                currSkill=2;
                currState=2;
            }
        }
    }
}
