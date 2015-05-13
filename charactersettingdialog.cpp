#include "charactersettingdialog.h"
#include "ui_charactersettingdialog.h"

CharacterSettingDialog::CharacterSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterSettingDialog)
{
    ui->setupUi(this);
}

CharacterSettingDialog::~CharacterSettingDialog()
{
    delete ui;
}
