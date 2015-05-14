#ifndef CHARACTER_H
#define CHARACTER_H

#include"sprite.h"

class Character : public Sprite
{
    Q_OBJECT
public:
    enum Type{NPC,Enemy,Player};
    static QString Type2QString(Type t);
    static Type QString2Type(QString s);

    void init();

    Character(const QString &worldName,const QString &name,GraphicsView* rec=0,QGraphicsItem * parent = 0);
    ~Character();
    Character(){}
    bool read(const QString &worldName, const QString &name);
    Character* clone();

    void setting();

    void skillEnd(int index);
    void skillRun(int index);

    void setWeight(double w){weight=w;}
    void setVx(double v){oldVx=vx;vx=v;}
    void setOldVx(double v){oldVx=v;}
    void setVy(double v){vy=v;}
    void setStable(bool s){stable=s;}
    void setType(Type t){type=t;}
    void setOutOfScene(bool s){outOfScene=s;}
    void setHP(int h){HP=h;}
    void setMP(int m){MP=m;}
    void setHPMax(int h){HPMax=h;}
    void setMPMax(int m){MPMax=m;}

    int getHP(){return HP;}
    int getMP(){return MP;}
    int getHPMax(){return HPMax;}
    int getMPMax(){return MPMax;}
    bool isOutOfScene(){return outOfScene;}
    double getWeight(){return weight;}
    double getVx(){return vx;}
    double getOldVx(){return oldVx;}
    double getVy(){return vy;}
    bool getStable(){return stable;}
    Type getType(){return type;}

    void readFromStream(QTextStream &in);
    void writeToStream(QTextStream &out);
protected:
    //可变信息(每个实例有可能不同)
    double weight;//质量
    int HP;
    int MP;
    int HPMax;
    int MPMax;
    Type type;

    double vx;//x上速度，向右为正
    double oldVx;//x上速度，先前状态,jump用
    double vy;//y上速度，向下为正
    bool stable;
    bool outOfScene;

};


#endif // CHARACTER_H
