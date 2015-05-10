#ifndef SKILL_H
#define SKILL_H

#include"mainwindow.h"
#include"frame.h"
#include"sprite.h"
#include"state.h"

class Sprite;
class QGraphicsScene;

class Skill
{
public:
    Skill(Sprite* sp, int stateNo);
    virtual ~Skill()=0;

    //技能类型
    enum Skill_Type{instant,last};

    virtual void start();
    virtual void end();
    virtual int run();
    virtual void read();

    void setPriority(int p){priority=p;}
    int getPriority(){return priority;}

    void setType(Skill_Type t){type=t;}
    int getType(){return type;}

    int getStateNumber(){return stateNumber;}
protected:
    Sprite* sprite;
    State* state;
    QGraphicsScene* scene;

    int stateNumber;//相关联状态

    int priority;//优先级
    Skill_Type type;
};

#endif // SKILL_H
