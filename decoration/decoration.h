#ifndef DECORATION_H
#define DECORATION_H

#include<sprite.h>

class Decoration : public Sprite
{
public:
    Decoration(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Decoration();
    Decoration(){}
    bool read(const QString& worldName,const QString& name);
    Decoration* clone();
};

#endif // DECORATION_H
