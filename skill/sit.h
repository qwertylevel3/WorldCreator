#ifndef SIT_H
#define SIT_H

#include"skill/skill.h"

class Sit : public Skill
{
public:
    Sit(Sprite *sp, int state);
    ~Sit();

};

#endif // SIT_H
