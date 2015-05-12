#ifndef MANAGER_H
#define MANAGER_H

#include"sprite.h"

class Manager
{
public:
    Manager();
    virtual ~Manager(){}
    virtual void update()=0;
    virtual void clear()=0;
    virtual Sprite* add(Sprite* p)=0;
};

#endif // MANAGER_H
