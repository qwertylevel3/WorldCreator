#include "sit.h"

Sit::Sit(Sprite* sp,int state)
    :Skill(sp,state)
{
    setPriority(2);
}

Sit::~Sit()
{

}
