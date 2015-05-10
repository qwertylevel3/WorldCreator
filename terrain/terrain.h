#ifndef TERRAIN_H
#define TERRAIN_H

#include"sprite.h"

class Terrain : public Sprite
{
public:
    Terrain(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Terrain();
    Terrain(){}
    bool read(const QString& worldName,const QString& name);
    Terrain* clone();
};

#endif // TERRAIN_H
