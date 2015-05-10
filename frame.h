#ifndef FRAME_H
#define FRAME_H

#include<QPixmap>
#include<QVector>
#include<QTextStream>

struct Frame
{
    Frame();
    ~Frame();
    Frame(Frame *f);
    bool read(QTextStream& in);

    QPixmap pixmap;
    //QVector<QRectF> redRect;
    QVector<QRectF> rects;
    QVector<QRectF> mrects;//镜像矩形
};

#endif // FRAME_H
