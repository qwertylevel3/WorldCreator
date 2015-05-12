#ifndef WORLDDESCRIPTIONDIALOG_H
#define WORLDDESCRIPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class WorldDescriptionDialog;
}

class WorldDescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorldDescriptionDialog(QWidget *parent = 0);
    ~WorldDescriptionDialog();

private:
    Ui::WorldDescriptionDialog *ui;
};

#endif // WORLDDESCRIPTIONDIALOG_H
