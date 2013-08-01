#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createConnectionSqlite();
    QLoginDialog dialog;
    int i;
    i=dialog.prava;
    qDebug()<<i;
    if(i>-1)
    {
        //qDebug()<<i;
        MainWindow w(i);
        w.setWindowModality(Qt::WindowModal);
        w.show();
        return a.exec();
    }
    else
        return 0;
}
