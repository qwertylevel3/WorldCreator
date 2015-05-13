#ifndef CHARACTERSETTINGDIALOG_H
#define CHARACTERSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class CharacterSettingDialog;
}

class CharacterSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterSettingDialog(QWidget *parent = 0);
    ~CharacterSettingDialog();

private:
    Ui::CharacterSettingDialog *ui;
};

#endif // CHARACTERSETTINGDIALOG_H
