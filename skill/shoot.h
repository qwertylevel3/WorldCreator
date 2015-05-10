#ifndef SHOOT_H
#define SHOOT_H

#include"skill.h"

class Shoot:public Skill
{
public:
    Shoot(Sprite* sp,int state);
    ~Shoot();
    int run();
    void end();
    void start();
    void setShootDelay(int d){shootDelay=d;}
    int getShootDelay(int d){return shootDelay;}
protected:
    int shootDelay;
    int shootCount;
};

#endif // SHOOT_H
