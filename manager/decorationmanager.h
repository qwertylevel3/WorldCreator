#ifndef DECORATIONMANAGER_H
#define DECORATIONMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include"decoration/decoration.h"
#include<QList>
#include<QMap>
#include"manager/manager.h"
#include<QObject>

class DecorationManager:public QObject,public Manager,public Singleton<DecorationManager>
{
    Q_OBJECT
public:
    DecorationManager();
    ~DecorationManager();

    void init(QGraphicsScene* s,QString& worldName);
    bool read(QString& worldName);
    void update();
    QList<Decoration*>& getAllDecoration(){return allDecoration;}
    int getTotalNumber(){return allDecoration.size();}
    Decoration* addDecoration(const QString &name);
    void clear();
    Sprite* add(Sprite *p);
    QMap<QString,Decoration*>& getPrototype(){return prototype;}
signals:
    void selected(Sprite* p);
protected:
    QList<Decoration*> allDecoration;
    QGraphicsScene* scene;
    QMap<QString,Decoration*> prototype;
};


#endif // DECORATIONMANAGER_H
