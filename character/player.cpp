#include "character/player.h"
#include"inputmodule.h"
#include"skill/shoot.h"
#include<QKeyEvent>
#include"inputmodule.h"

Player::Player(const QString &worldName, const QString &name, GraphicsView *rec, QGraphicsItem *parent)
    :Character(worldName,name,rec,parent)
{
    type=Character::Player;

    Shoot* shoot=new Shoot(this,4);
    shoot->setShootDelay(7);
    skillBox.push_back(shoot);


    inputModule=new InputModule(this);
    inputModule->setSkill(InputModule::left,1);
    inputModule->setSkill(InputModule::right,1);
    inputModule->setSkill(InputModule::D_C,2);
    inputModule->setSkill(InputModule::A_C,4);

    setDragable(true);
}

Player::~Player()
{

}
void Player::keyPressEvent(QKeyEvent* e)
{
    if(e->isAutoRepeat())
        return;
    inputModule->input(e->key());
    skillStart(inputModule->getSkill());
}

void Player::keyReleaseEvent(QKeyEvent* e)
{
    if(e->isAutoRepeat())
        return ;
    skillEnd(inputModule->popSkill());
}


