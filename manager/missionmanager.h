#ifndef MISSIONMANAGER_H
#define MISSIONMANAGER_H

#include"singleton.h"
#include<QList>

class Mission;


class MissionManager:public Singleton<MissionManager>
{
public:
    MissionManager();
    ~MissionManager();
    bool read(const QString &worldName);
    void init(const QString &worldName);
    void start(int index);
    void end(int index);
protected:
    int missionNumber;//关卡总数
    QList<Mission*> allMission;
};

#endif // MISSIONMANAGER_H
