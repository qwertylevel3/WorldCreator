#ifndef RESTORE_H
#define RESTORE_H

#include"skill/skill.h"

class Restore : public Skill
{
public:
    Restore(Sprite* sp,int state);
    ~Restore();
};

#endif // RESTORE_H
