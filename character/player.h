#ifndef PLAYER_H
#define PLAYER_H

#include"character/character.h"

class InputModule;

class Player : public Character
{
public:
    Player(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Player();
public slots:
    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent* e);

    InputModule* inputModule;

};
#endif //PLAYER_H
