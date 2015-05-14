#include "terrainsettingdialog.h"
#include "ui_terrainsettingdialog.h"

TerrainSettingDialog::TerrainSettingDialog(Terrain *t, QWidget *parent) :
    terrain(t),QDialog(parent),
    ui(new Ui::TerrainSettingDialog)
{
    ui->setupUi(this);
    ui->ZSpinBox->setValue(terrain->zValue());
}

TerrainSettingDialog::~TerrainSettingDialog()
{
    delete ui;
}

int TerrainSettingDialog::getZValue()
{
    return ui->ZSpinBox->value();
}
