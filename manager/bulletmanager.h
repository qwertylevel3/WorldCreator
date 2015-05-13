#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H


#include"singleton.h"
#include<QGraphicsScene>
#include<QList>
#include<QMap>
#include"bullet/bullet.h"
#include"manager/manager.h"

class BulletManager:public Singleton<BulletManager>,public Manager
{
public:
    BulletManager();
    ~BulletManager();
    void init(QGraphicsScene* s, const QString &worldName);
    bool read(const QString &worldName);
    void update();
    QList<Bullet*>& getAllBullet(){return allBullet;}
    int getTotalNumber(){return allBullet.size();}
    
    void clear();
    Sprite* add(Sprite *p);
    
    Bullet* getBullet(const QString& name);
    Bullet* addBullet(const QString& name);
    void setShowRect(bool s);
protected:
    QList<Bullet*> allBullet;//scene中所有bullet
    QGraphicsScene* scene;
    
    QMap<QString,Bullet*> prototype;//bullet原型
};

#endif // BULLETMANAGER_H
