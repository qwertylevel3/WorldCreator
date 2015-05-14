#include "decorationsettingdialog.h"
#include "ui_decorationsettingdialog.h"

DecorationSettingDialog::DecorationSettingDialog(Decoration *d, QWidget *parent) :
    decoration(d),QDialog(parent),
    ui(new Ui::DecorationSettingDialog)
{
    ui->setupUi(this);
    ui->ZSpinBox->setValue(decoration->zValue());
}

DecorationSettingDialog::~DecorationSettingDialog()
{
    delete ui;
}

int DecorationSettingDialog::getZValue()
{
    return ui->ZSpinBox->value();
}
