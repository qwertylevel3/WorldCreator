#include "jump.h"
#include"state.h"
#include"character/character.h"

Jump::Jump(Sprite *sp, int st)
    :Skill(sp,st)
{
    F=200;
    setType(Skill::last);
    setPriority(2);
    mid=state->getFrameTotal()/2;
}

Jump::~Jump()
{

}

void Jump::start()
{
    Character* character=qobject_cast<Character*>(sprite);
    if(character)
    {
        if(!character->getStable())//没有着力点，跳出
            return;
        character->setVy(-(F/character->getWeight())*5);
        character->setVx(character->getOldVx());

        //起跳前半段开始
        state->setRepeatStart(0);
        state->setRepeatOver(mid);
        state->setCurrFrame(0);
    }
    character->setStable(false);//在碰撞检测中结束stable
}

void Jump::end()
{

}

int Jump::run()
{
    Character* character=qobject_cast<Character*>(sprite);
    if(character)
    {
        if(character->getVy()>0)//开始下落
        {
            //下落后半段
            state->setRepeatStart(mid);
            state->setRepeatOver(state->getFrameTotal());
        }
    }
    state->update();
    if(character->getStable())//终止
    {
        character->setVx(0);
        state->setRepeatStart(0);
        state->setRepeatOver(mid);
        state->setCurrFrame(0);
        return 0;
    }
    return 1;
}



