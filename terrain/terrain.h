#ifndef TERRAIN_H
#define TERRAIN_H

#include"sprite.h"

class Terrain : public Sprite
{
    Q_OBJECT
public:
    Terrain(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Terrain();
    Terrain(){}
    bool read(const QString& worldName,const QString& name);
    Terrain* clone();
    void setting();
};

#endif // TERRAIN_H
