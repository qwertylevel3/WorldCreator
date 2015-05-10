#include "skill.h"
#include<QGraphicsScene>

Skill::Skill(Sprite *sp,int stateNo)
{
    sprite=sp;
    stateNumber=stateNo;
    state=sp->getState(stateNumber);
    scene=sp->scene();

    priority=0;
    type=instant;
    read();
}
//读取配置信息
void Skill::read()
{

}

void Skill::start()
{
}

void Skill::end()
{
}

//返回当前skill状态
//0结束
//1忙
int Skill::run()
{
    return state->update();
}

Skill::~Skill()
{

}

