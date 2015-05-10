#ifndef BULLET_H
#define BULLET_H

#include"sprite.h"

class Bullet : public Sprite
{
public:
    Bullet(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Bullet();
    Bullet(){}
    bool read(const QString& worldName,const QString& name);
    Bullet* clone();

    void setDamage(int d){damage=d;}
    int getDamage(){return damage;}

    void setVx(int v){vx=v;}
    int getVx(){return vx;}

    void setVy(int v){vy=v;}
    int getVy(){return vy;}
protected:
    int damage;
    int vx;
    int vy;
};

#endif // BULLET_H
