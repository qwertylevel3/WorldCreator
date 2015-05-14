#ifndef CHARACTERSETTINGDIALOG_H
#define CHARACTERSETTINGDIALOG_H

#include <QDialog>
#include<character/character.h>

namespace Ui {
class CharacterSettingDialog;
}

class CharacterSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterSettingDialog(Character* c,QWidget *parent = 0);
    ~CharacterSettingDialog();
    Character::Type getType();
    int getZValue();
    int getHP();
    int getMP();
    int getMaxHP();
    int getMaxMP();
private:
    Ui::CharacterSettingDialog *ui;
    Character* character;
};

#endif // CHARACTERSETTINGDIALOG_H
