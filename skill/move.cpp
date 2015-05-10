#include "move.h"
#include"sprite.h"
#include<qdebug.h>
#include"game.h"
#include"character/character.h"

Move::Move(Sprite *sp, int state)
    :Skill(sp,state)
{
    speed=5;
    setType(Skill::last);
    setPriority(1);
}

void Move::start()
{
    qobject_cast<Character*>(sprite)->setVx(sprite->getOrientation()*speed);
}
void Move::end()
{
    qobject_cast<Character*>(sprite)->setVx(0);
}

int Move::run()
{
    state->update();
    return 1;

}


Move::~Move()
{

}

