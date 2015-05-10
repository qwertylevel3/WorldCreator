#ifndef DECORATIONMANAGER_H
#define DECORATIONMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include"decoration/decoration.h"
#include<QList>
#include<QMap>

class DecorationManager:public Singleton<DecorationManager>
{
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
protected:
    QList<Decoration*> allDecoration;
    QGraphicsScene* scene;
    QMap<QString,Decoration*> prototype;
};


#endif // DECORATIONMANAGER_H
