#include "frame.h"

Frame::Frame()
{

}

Frame::Frame(Frame* f)
{
    pixmap=f->pixmap;
    rects=f->rects;
    mrects=f->mrects;
}

Frame::~Frame()
{

}

bool Frame::read(QTextStream &in)
{
    int rectTotal;//碰撞矩形总数
    QString pixmapPath;

    in>>pixmapPath;
    if(!pixmap.load(pixmapPath))
    {
        return false;
    }

    in>>rectTotal;
    for(int i=0;i<rectTotal;i++)
    {
        double x,y,width,height;
        in>>x>>y>>width>>height;
        QRectF temp(x,y,width,height);
        rects.push_back(temp);

        QRectF mtemp(pixmap.width()-x-width,
                    y,
                    width,
                    height);
        mrects.push_back(mtemp);

    }
    return true;
}
