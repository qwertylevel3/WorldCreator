#ifndef STATE_H
#define STATE_H

#include<QVector>
#include<QPixmap>
#include"frame.h"

class Sprite;
class QPainter;
class QTextStream;


class State
{
public:
    State(Sprite* sp);
    State(State* s);
    virtual ~State();
    int update();
    void read(QTextStream& in);

    void draw(QPainter *painter, int oritation,bool showRect=false);

    void start();
    void end();

    void setSprite(Sprite* sp){sprite=sp;}
    void setXoffset(double x){xoffset=x;}
    void setYoffset(double y){yoffset=y;}
    void setXscale(double x){xscale=x;}
    void setYscale(double y){yscale=y;}
    void setRotate(double r){rotate=r;}
    void setFrameTotal(int n){frameTotal=n;}
    void setFrameDelay(int d){frameDelay=d;}
    void setCurrFrame(int index){currFrame=index;}
    void setRepeat(bool r){isRepeat=r;}
    void setRepeatStart(int index){repeatStart=index;}
    void setRepeatOver(int index){repeatOver=index;}


    double getXoffset(){return xoffset;}
    double getYoffset(){return yoffset;}
    double getXscale(){return xscale;}
    double getYscale(){return yscale;}
    double getRotate(){return rotate;}
    int getFrameTotal(){return frameTotal;}
    int getFrameDelay(){return frameDelay;}
    int getCurrFrame(){return currFrame;}
    bool getRepeat(){return isRepeat;}
    int getRepeatStart(){return repeatStart;}
    int getRepeatOver() {return repeatOver;}

    int getPixmapHeight(){return frameBox[currFrame].pixmap.height();}
    int getPixmapWidth(){return frameBox[currFrame].pixmap.width();}

    QPixmap getPixmap(){return frameBox[currFrame].pixmap;}

    QVector<QRectF>& getRects();

protected:
    Sprite* sprite;

    double xoffset;
    double yoffset;
    double xscale;
    double yscale;
    double rotate;

    int frameDelay;//每帧延迟
    int frameTotal;//总帧数
    bool isRepeat;//重复播放
    int currFrame;//当前帧
    int frameClock;//计时用

    int repeatStart;//重复开始帧
    int repeatOver;//重复终止帧

    bool reverseX;
    bool reverseY;

    int stateNo;

    QVector<Frame> frameBox;
};

#endif // STATE_H
