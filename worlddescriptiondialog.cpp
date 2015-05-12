#include "worlddescriptiondialog.h"
#include "ui_worlddescriptiondialog.h"

WorldDescriptionDialog::WorldDescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldDescriptionDialog)
{
    ui->setupUi(this);
}

WorldDescriptionDialog::~WorldDescriptionDialog()
{
    delete ui;
}
