#ifndef JUMP_H
#define JUMP_H

#include"skill/skill.h"

class Jump : public Skill
{
public:
    Jump(Sprite* sp,int st);
    ~Jump();
    int run();
    void start();
    void end();

    void setF(double f){F=f;}
    double getF(){return F;}

    void setMid(int m){mid=m;}
    int getMid(){return mid;}
protected:
    double F;
    int mid;//帧循环中点
};

#endif // JUMP_H
