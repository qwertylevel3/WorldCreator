#ifndef MISSION_H
#define MISSION_H


#include<QTextStream>
//关卡
//管理当前关卡载入，退出，环境变量，设置等
class Mission
{
public:
    Mission(const QString& worldName,const QString& name);
    ~Mission();
    void start();
    int run();
    void end();
    bool load();
    bool loadTerrain(QTextStream& in);
    bool loadCharacter(QTextStream& in);
    bool loadDecoration(QTextStream& in);

    void setG(double g){G=g;}
    void setT(double t){T=t;}

    double getG(){return G;}
    double getT(){return T;}
protected:
    double G,T;//重力加速度，单帧时间间隔
    QString worldName;
    QString name;

};

#endif // MISSION_H
