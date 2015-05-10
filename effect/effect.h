#ifndef EFFECT_H
#define EFFECT_H

#include"sprite.h"

class Effect : public Sprite
{
public:
    Effect(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Effect();
    Effect(){}
    bool read(const QString& worldName,const QString& name);
    Effect* clone();
    void skillRun(int index);
};

#endif // EFFECT_H
