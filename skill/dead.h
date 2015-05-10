#ifndef DEAD_H
#define DEAD_H

#include"skill/skill.h"


class Dead:public Skill
{
public:
    Dead(Sprite* sprite,int st);
    ~Dead();
    void end();
};

#endif // DEAD_H
