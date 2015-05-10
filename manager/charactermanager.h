#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include"singleton.h"
#include<QGraphicsScene>
#include<character/character.h>
#include<QList>
#include<QMap>

class Player;


class CharacterManager: public Singleton<CharacterManager>
{
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
protected:
    QList<Character*> allCharacter;
    QGraphicsScene* scene;
    QMap<QString,Character*> prototype;
};

#endif // CHARACTERMANAGER_H
