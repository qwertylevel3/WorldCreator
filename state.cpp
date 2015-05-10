#include "state.h"

#include<QTextStream>
#include<QPainter>
#include"sprite.h"
#include<QTransform>
#include"frame.h"
#include<qDebug>


State::State(Sprite *sp)
{
    sprite=sp;
    xoffset=0;
    yoffset=0;
    xscale=1;
    yscale=1;
    rotate=0;
    frameTotal=0;
    frameDelay=5;
    isRepeat=false;
    currFrame=0;
    frameClock=0;

    repeatStart=0;
    repeatOver=0;

    reverseX=false;
    reverseY=false;
    
}

//构造后记得设置sprite。。。
State::State(State *s)
{
    sprite=0;

    isRepeat=false;
    currFrame=0;
    frameClock=0;

    reverseX=false;
    reverseY=false;

    xoffset=s->getXoffset();
    yoffset=s->getYoffset();
    xscale=s->getXscale();
    yscale=s->getYscale();
    rotate=s->getRotate();
    frameDelay=s->getFrameDelay();

    frameTotal=s->getFrameTotal();
    for(int i=0;i<frameTotal;i++)
    {
        Frame f(s->frameBox[i]);
        frameBox.push_back(f);
    }
    //更行repeat index
    repeatStart=0;
    repeatOver=frameBox.size();
}

void State::read(QTextStream &in)
{
    in>>xoffset;
    in>>yoffset;
    in>>xscale;
    in>>yscale;
    in>>rotate;
    in>>frameDelay;

    in>>frameTotal;
    for(int i=0;i<frameTotal;i++)
    {
        Frame f;
        f.read(in);
        frameBox.push_back(f);
    }
    //更行repeat index
    repeatStart=0;
    repeatOver=frameBox.size();
}

//状态开始，可能会做一些其他事情
void State::start()
{
    currFrame=repeatStart;
}
//状态结束
void State::end()
{
    //currFrame=0;
}
//更新，返回状态：0空，1忙
int State::update()
{
    if(frameClock++==frameDelay)
    {
        frameClock=0;
        if(isRepeat)
        {
            currFrame=(++currFrame==repeatOver?0:currFrame);
            return 1;
        }
        else
        {
            if(++currFrame==repeatOver)
            {
                currFrame=repeatStart;
                return 0;
            }
        }
    }
    return 1;
}

void State::draw(QPainter *painter, int oritation, bool showRect)
{
    painter->setRenderHint(QPainter::Antialiasing,true);
    
    if(oritation==-1)
    {
        QTransform t(-1,0,0,1,0,0);
        QPixmap p=frameBox[currFrame].pixmap.transformed(t);

        painter->drawPixmap(sprite->pos().x(),sprite->pos().y(),p);
    }
    else
    {
        painter->drawPixmap(sprite->pos().x(),sprite->pos().y(),frameBox[currFrame].pixmap);
    }
    //绘制碰撞矩形
    if(showRect)
    {
        painter->setOpacity(0.5);
        if(oritation==-1)
        {
            painter->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for(int i=0;i<frameBox[currFrame].mrects.size();i++)
            {
                double x,y,w,h;
                x=sprite->pos().x()+frameBox[currFrame].mrects[i].x();
                y=sprite->pos().y()+frameBox[currFrame].mrects[i].y();
                w=frameBox[currFrame].mrects[i].width();
                h=frameBox[currFrame].mrects[i].height();
                painter->drawRect(x,y,w,h);
            }
        }
        else if(oritation==1)
        {
            painter->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
            for(int i=0;i<frameBox[currFrame].rects.size();i++)
            {
                double x,y,w,h;
                x=sprite->pos().x()+frameBox[currFrame].rects[i].x();
                y=sprite->pos().y()+frameBox[currFrame].rects[i].y();
                w=frameBox[currFrame].rects[i].width();
                h=frameBox[currFrame].rects[i].height();
                painter->drawRect(x,y,w,h);
            }
        }
    }
    //绘制原点
    //painter->drawRect(sprite->pos().x(),sprite->pos().y(),10,10);
}
State::~State()
{

}

QVector<QRectF>& State::getRects()
{
    if(sprite->getOrientation()==1)
    {
        return frameBox[currFrame].rects;
    }
    else
    {
        return frameBox[currFrame].mrects;
    }
}
