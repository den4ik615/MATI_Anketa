#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H
#include <QWidget>

class setting_widget : public QWidget
{
    Q_OBJECT
public:
    explicit setting_widget(QWidget *parent = 0);
public slots:
    void saveSettings();
};

#endif // SETTING_WIDGET_H
