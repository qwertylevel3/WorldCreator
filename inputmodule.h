#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include<QMap>
#include<QStack>
#include"sprite.h"

//处理键盘映射
class InputModule
{
public:
    enum Command{up,down,left,right,A_C,B_C,C_C,D_C,E_C,F_C};

    InputModule(Sprite* receiver);
    ~InputModule();
    void input(int key);
    void setCommand(int key,Command c){keyMap[key]=c;}
    void setSkill(Command c,int skillIndex){commandMap[c]=skillIndex;}
    int getSkill();
    int popSkill();
protected:
    Sprite* sprite;
    bool getInput;
    QMap<int,Command> keyMap;//键盘映射表
    QStack<Command> commandStack;//命令栈
    QMap<Command,int> commandMap;//技能映射表

};

#endif // INPUTMODULE_H
