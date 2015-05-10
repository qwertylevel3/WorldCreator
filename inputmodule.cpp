#include "inputmodule.h"
#include<QDebug>

InputModule::InputModule(Sprite *receiver)
    :sprite(receiver)
{
    keyMap[Qt::Key_W]=up;
    keyMap[Qt::Key_S]=down;
    keyMap[Qt::Key_A]=left;
    keyMap[Qt::Key_D]=right;
    keyMap[Qt::Key_T]=A_C;
    keyMap[Qt::Key_F]=B_C;
    keyMap[Qt::Key_H]=C_C;
    keyMap[Qt::Key_G]=D_C;
    keyMap[Qt::Key_R]=E_C;
    keyMap[Qt::Key_Y]=F_C;
    getInput=true;
}

InputModule::~InputModule()
{

}

void InputModule::input(int key)
{
    if(getInput && keyMap.contains(key))
    {
        commandStack.push(keyMap[key]);
    }
}

int InputModule::getSkill()
{
    if(!commandStack.isEmpty())
    {
        Command temp=commandStack.top();
        if(commandMap.contains(temp))
        {
            if(temp==left)
            {
                sprite->setOrientation(-1);
            }
            else if(temp==right)
            {
                sprite->setOrientation(1);
            }
            return commandMap[temp];
        }
    }

    return 0;
}

int InputModule::popSkill()
{
    if(!commandStack.isEmpty())
    {
        Command temp=commandStack.pop();
        if(commandMap.contains(temp))
        {
            if(temp==left)
            {
                sprite->setOrientation(-1);
            }
            else if(temp==right)
            {
                sprite->setOrientation(1);
            }
            return commandMap[temp];
        }
    }
    return 0;
}

