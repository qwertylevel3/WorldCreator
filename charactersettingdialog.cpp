#include "charactersettingdialog.h"
#include "ui_charactersettingdialog.h"

CharacterSettingDialog::CharacterSettingDialog(Character *c, QWidget *parent) :
    character(c),QDialog(parent),
    ui(new Ui::CharacterSettingDialog)
{
    ui->setupUi(this);
    ui->typeComboBox->setCurrentText(Character::Type2QString(c->getType()));
    ui->HPSpinBox->setValue(c->getHP());
    ui->MPSpinBox->setValue(c->getMP());
    ui->MaxHPSpinBox->setValue(c->getHPMax());
    ui->MaxMPSpinBox->setValue(c->getMPMax());
    ui->ZSpinBox->setValue(c->zValue());
}

CharacterSettingDialog::~CharacterSettingDialog()
{
    delete ui;
}

Character::Type CharacterSettingDialog::getType()
{
    QString t=ui->typeComboBox->currentText();
    return Character::QString2Type(t);
}

int CharacterSettingDialog::getZValue()
{
    return ui->ZSpinBox->value();
}

int CharacterSettingDialog::getHP()
{
    return ui->HPSpinBox->value();
}

int CharacterSettingDialog::getMP()
{
    return ui->MPSpinBox->value();
}

int CharacterSettingDialog::getMaxHP()
{
    return ui->MaxHPSpinBox->value();
}

int CharacterSettingDialog::getMaxMP()
{
    return ui->MaxMPSpinBox->value();
}


