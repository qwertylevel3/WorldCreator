#ifndef CHARACTER_H
#define CHARACTER_H

#include"sprite.h"

class Character : public Sprite
{
    Q_OBJECT
public:
    enum Type{NPC,Enemy,Player};
    Character(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Character();
    Character(){}
    bool read(const QString &worldName, const QString &name);
    Character* clone();

    void skillEnd(int index);
    void skillRun(int index);

    void setWeight(double w){weight=w;}
    void setVx(double v){oldVx=vx;vx=v;}
    void setOldVx(double v){oldVx=v;}
    void setVy(double v){vy=v;}
    void setStable(bool s){stable=s;}
    void setType(Type t){type=t;}
    void setOutOfScene(bool s){outOfScene=s;}

    bool isOutOfScene(){return outOfScene;}
    double getWeight(){return weight;}
    double getVx(){return vx;}
    double getOldVx(){return oldVx;}
    double getVy(){return vy;}
    bool getStable(){return stable;}
    Type getType(){return type;}
protected:
    double weight;//质量
    double vx;//x上速度，向右为正
    double oldVx;//x上速度，先前状态,jump用
    double vy;//y上速度，向下为正
    bool stable;
    bool outOfScene;
    Type type;
};


#endif // CHARACTER_H
