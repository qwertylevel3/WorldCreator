#ifndef DECORATIONSETTINGDIALOG_H
#define DECORATIONSETTINGDIALOG_H

#include <QDialog>
#include<decoration/decoration.h>

namespace Ui {
class DecorationSettingDialog;
}

class DecorationSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecorationSettingDialog(Decoration* d,QWidget *parent = 0);
    ~DecorationSettingDialog();
    int getZValue();
private:
    Decoration* decoration;
    Ui::DecorationSettingDialog *ui;
};

#endif // DECORATIONSETTINGDIALOG_H
