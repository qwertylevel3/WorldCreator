#include "dead.h"

#include"character/character.h"
#include"sprite.h"

Dead::Dead(Sprite *sprite, int st)
    :Skill(sprite,st)
{
    setPriority(99);
}

Dead::~Dead()
{

}

void Dead::end()
{
    sprite->setVisible(false);
}
