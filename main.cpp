#include "mainwindow.h"
#include <QApplication>
#include<QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash =new QSplashScreen;
    splash->setPixmap(QString(":/images/logo.png"));
    splash->show();

    Qt::Alignment topRight=Qt::AlignRight | Qt::AlignTop;

    splash->showMessage(QObject::tr("start...."),topRight,Qt::white);


    MainWindow w;
    w.show();

    splash->finish(&w);
    delete splash;
    return a.exec();
}
