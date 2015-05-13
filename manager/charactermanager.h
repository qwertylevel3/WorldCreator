#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include<character/character.h>
#include<QList>
#include<QMap>
#include"manager.h"

class Player;


class CharacterManager:public QObject,public Manager,public Singleton<CharacterManager>
{
    Q_OBJECT
public:
    CharacterManager();
    ~CharacterManager();
    void init(QGraphicsScene* s,QString& worldName);
    bool read(QString& worldName);
    void update();
    void clear();
    QList<Character*>& getAllCharacter(){return allCharacter;}
    int getTotalNumber(){return allCharacter.size();}
    Character* addCharacter(const QString& name);
    Player* addPlayer(Player* p);
    Sprite* add(Sprite *p);
    QMap<QString,Character*>& getPrototype(){return prototype;}
    void setShowRect(bool s);
signals:
    void selected(Sprite* s);
protected:
    QList<Character*> allCharacter;
    QGraphicsScene* scene;
    QMap<QString,Character*> prototype;
};



#endif // CHARACTERMANAGER_H
