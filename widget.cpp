#include "widget.h"
#include "QDebug"
#include "QLineEdit"
#include <QFile>
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
}

void Widget::saveSettings()
{
    QWidget *w;
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    file->resize(0);
    w=(QWidget *)sender()->parent();
    QLineEdit *edit;
    QObjectList list;
    QTextStream out(file);
    list = w->children();
    qDebug()<<file->fileName();
    for(int i=1; i<=5; i++)
    {
        qDebug()<<i;
        edit=(QLineEdit *)list.at(i);
        out<<edit->text()<<"\n";
    }
    file->close();
    this->close();
}
