#include "sprite.h"

#include<QGraphicsSceneMouseEvent>
#include <QPainter>
#include<QKeyEvent>
#include<QGraphicsRotation>
#include"mainwindow.h"
#include<QDir>
#include<QImageReader>
#include"skill/restore.h"
#include"game.h"
#include"manager/manager.h"
//----------------------------Sprite------------------------------//

Sprite::Sprite(const QString &worldName, const QString &name, GraphicsView* rec, QGraphicsItem * parent)
    :QGraphicsObject(parent)
{
    this->name=name;
    setZValue(5);
    read(worldName,name);

    //setTransformOriginPoint(boundingRect().center());

    currState=0;
    currSkill=0;

    orientation=1;

    setViewReceiver(rec);

    dragable=true;
}
Sprite::~Sprite()
{
    for(int i=0;i<stateTotal;i++)
    {
        delete stateBox[i];
    }
    stateBox.clear();
}

Sprite* Sprite::clone()
{
    Sprite* p=new Sprite;
    p->setZValue(5);
    p->setName(name);
    //setTransformOriginPoint(boundingRect().center());
    p->setCurrState(0);
    p->setCurrSkill(0);
    p->setOrientation(1);
    p->setViewReceiver(receiver);
    p->setDragable(dragable);
    return p;
}

bool Sprite::read(const QString &worldName, const QString &name)
{
    return false;
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(isSelected())
    {
        painter->drawRect(boundingRect());
    }
    stateBox[currState]->draw(painter,orientation,Game::instance()->getShowRects());
}

void Sprite::skillStart(int index)
{
    if(index<skillBox.size())
    {
        //比较优先级，确定是否中断
        if(skillBox[currSkill]->getPriority()<skillBox[index]->getPriority())
        {
            //终止当前
            skillBox[currSkill]->end();
            //int height1=stateBox[currState]->getPixmapHeight();
            //更新
            currSkill=index;
            currState=skillBox[index]->getStateNumber();
            skillBox[currSkill]->start();
            //int height2=stateBox[currState]->getPixmapHeight();
            //矫正偏移
            //this->setPos(this->pos().x(),this->pos().y()-height2+height1);
        }
    }
}

void Sprite::skillEnd(int index)
{
    if(index<skillBox.size())
    {
        if(skillBox[currSkill]->getPriority()<=skillBox[index]->getPriority())
        {
            //如果技能为last形，且优先级较高，立即结束，否则推迟到run中结束
            if(skillBox[currSkill]->getType()==Skill::last)
            {
                skillBox[currSkill]->end();
                currSkill=0;
                currState=0;
            }
        }
    }
}

void Sprite::skillRun(int index)
{
    if(index<skillBox.size())
    {
        //运行，发现已经结束
        if(skillBox[currSkill]->run()==0)
        {
            currSkill=0;
            currState=0;
        }
    }
}

void Sprite::setting()
{

}

void Sprite::setViewReceiver(GraphicsView *rec)
{
    if(rec)
    {
        receiver=rec;
        connect(receiver,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(keyPressEvent(QKeyEvent*)));
        connect(receiver,SIGNAL(keyReleased(QKeyEvent*)),this,SLOT(keyReleaseEvent(QKeyEvent*)));
    }
}

void Sprite::update()
{
    skillRun(currSkill);
}

QRectF Sprite::boundingRect() const
{
    QRectF t;
    t.setX(this->pos().x());
    t.setY(this->pos().y());
    t.setWidth(stateBox[currState]->getPixmap().rect().width());
    t.setHeight(stateBox[currState]->getPixmap().rect().height());
    return t;
}
void Sprite::keyPressEvent(QKeyEvent *event)
{

}
void Sprite::keyReleaseEvent(QKeyEvent *event)
{

}

void Sprite::setDragable(bool d)
{
    setFlag(QGraphicsItem::ItemIsMovable, d);
    setFlag(QGraphicsItem::ItemIsSelectable, d);
    dragable=d;
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseOffset.setX(event->pos().x()/2-pos().x()/2);
    mouseOffset.setY(event->pos().y()/2-pos().y()/2);
}

void Sprite::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(dragable)
    {
        this->setPos(event->scenePos().x()/2-mouseOffset.x()
                     ,event->scenePos().y()/2-mouseOffset.y());

    }
}
