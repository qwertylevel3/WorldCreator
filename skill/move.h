#ifndef MOVE_H
#define MOVE_H

#include"skill/skill.h"

class Move : public Skill
{
public:
    Move(Sprite* sp,int state);
    ~Move();
    int run();
    void start();
    void end();
    void setSpeed(int s){speed=s;}
    int getSpeed(){return speed;}
protected:
    int speed;
};

#endif // MOVE_H
