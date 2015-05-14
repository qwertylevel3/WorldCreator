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
#include"charactersettingdialog.h"

QString Character::Type2QString(Character::Type t)
{
    if(t==NPC)
    {
        return QString("NPC");
    }
    else if(t==Enemy)
    {
        return QString("Enemy");
    }
    else if(t==Player)
    {
        return QString("Player");
    }
    else
    {
        qDebug()<<"error to read type"<<endl;
        return QString("error");
    }
}

Character::Type Character::QString2Type(QString s)
{
    if(s=="NPC")
    {
        return NPC;
    }
    else if(s=="Enemy")
    {
        return Enemy;
    }
    else if(s=="Player")
    {
        return Player;
    }
    else
    {
        qDebug()<<"error to read QString"<<endl;
        return NPC;
    }
}

void Character::init()
{
    Sprite::init();
    vx=0;
    vy=0;
    oldVx=0;
    stable=true;
    outOfScene=false;

    Restore* restore=new Restore(this,0);
    skillBox.push_back(restore);

    Move* move=new Move(this,1);
    skillBox.push_back(move);

    Jump* jump=new Jump(this,2);
    skillBox.push_back(jump);

    Dead* dead=new Dead(this,3);
    skillBox.push_back(dead);

    HP=100;
    MP=100;
    HPMax=100;
    MPMax=100;
    weight=5;
    type=NPC;
}

Character::Character(const QString &worldName,const QString &name,GraphicsView* rec,QGraphicsItem * parent)
    :Sprite(worldName,name,rec,parent)
{
    read(worldName,name);
    setName(name);
    setViewReceiver(rec);
    init();
}

Character* Character::clone()
{
    Character* p=new Character;
    p->setName(name);
    p->setViewReceiver(receiver);
    p->setStateTotal(stateTotal);
    p->setDragable(dragable);
    p->setShowRect(showRect);


    for(int i=0;i<stateTotal;i++)
    {
        State* state=new State(stateBox[i]);
        state->setSprite(p);
        p->getStateBox().push_back(state);
    }

    p->init();

    p->setZValue(zValue());
    p->setWeight(weight);
    p->setHP(HP);
    p->setMP(MP);
    p->setHPMax(HPMax);
    p->setMPMax(MPMax);
    p->setType(type);


    return p;
}

void Character::setting()
{
    CharacterSettingDialog dialog(this);
    if(dialog.exec())
    {
        this->setType(dialog.getType());
        this->setZValue(dialog.getZValue());
        this->setHP(dialog.getHP());
        this->setMP(dialog.getMP());
        this->setHPMax(dialog.getMaxHP());
        this->setMPMax(dialog.getMaxMP());
    }
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

//读取可变信息
void Character::readFromStream(QTextStream &in)
{
    Sprite::readFromStream(in);//读入坐标,z
    QString s;
    in>>s;
    setType(QString2Type(s));
    in>>weight;
    in>>HPMax>>HP;
    in>>MPMax>>MP;
}
//写可变信息
void Character::writeToStream(QTextStream &out)
{
    Sprite::writeToStream(out);//写name,x,y,z
    out<<Type2QString(type)<<endl;
    out<<weight<<endl;
    out<<HPMax<<" "<<HP<<endl;
    out<<MPMax<<" "<<MP<<endl;
}
