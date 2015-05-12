#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H


#include"singleton.h"
#include<QGraphicsScene>
#include"effect/effect.h"
#include<QList>
#include<QMap>
#include"manager/manager.h"
#include"QObject"

class EffectManager:public QObject,public Singleton<EffectManager>,public Manager
{
    Q_OBJECT
public:
    EffectManager();
    ~EffectManager();
    void init(QGraphicsScene* s,const QString& worldName);
    bool read(const QString &worldName);
    void update();
    QList<Effect*>& getAllEffect(){return allEffect;}
    int getTotalNumber(){return allEffect.size();}
    Effect* addEffect(const QString& name);
    void clear();
    Sprite* add(Sprite *p);
protected:
    QList<Effect*> allEffect;
    QGraphicsScene* scene;
    QMap<QString,Effect*> prototype;
};

#endif // EFFECTMANAGER_H
