#include "shoot.h"
#include"bullet/bullet.h"
#include"game.h"
#include<QDebug>
#include"manager/bulletmanager.h"

Shoot::Shoot(Sprite *sp, int state)
    :Skill(sp,state)
{
    setType(Skill::instant);
    setPriority(3);
    shootDelay=15;
}

Shoot::~Shoot()
{

}

void Shoot::end()
{
}
int Shoot::run()
{
    if(shootCount++==shootDelay)
    {
        Bullet* b=BulletManager::instance()->addBullet("testBullet");
        b->setPos((sprite->pos().x()+
                  (sprite->getOrientation()==1?
                       sprite->getPixmapWidth()-b->getPixmapWidth()/2
                     :-b->getPixmapWidth())/2)
                ,(sprite->pos().y()+(sprite->getPixmapHeight()/4)));

        b->setVx(sprite->getOrientation()*10);
    }
    return state->update();
}

void Shoot::start()
{
    shootCount=0;
}
