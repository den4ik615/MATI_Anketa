#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

class Widget : public QWidget
{
    Q_OBJECT
public:
    QFile *file;
    explicit Widget(QWidget *parent = 0);
    
signals:
    
public slots:
    void saveSettings();
};

#endif // WIDGET_H
