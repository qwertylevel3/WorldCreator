#ifndef TERRAINSETTINGDIALOG_H
#define TERRAINSETTINGDIALOG_H

#include <QDialog>
#include"terrain/terrain.h"

namespace Ui {
class TerrainSettingDialog;
}

class TerrainSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TerrainSettingDialog(Terrain* t,QWidget *parent = 0);
    ~TerrainSettingDialog();
    int getZValue();
private:
    Terrain* terrain;
    Ui::TerrainSettingDialog *ui;
};

#endif // TERRAINSETTINGDIALOG_H
