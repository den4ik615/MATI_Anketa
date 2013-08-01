#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QFile>
#include <QDialog>
#include <QListWidgetItem>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>

class InfaWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    int prava;
    InfaWidget *information;
    void add_change_user(QString str, QString str2, int index);
    void errorMesage(QString message);
    void add_update(QString *act,QObject *obj);
    void createMenuBar();
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void clearLayout(QLayout *layout);
    void infa(QObject *obj);
    MainWindow(int i, QWidget *parent = 0);
    ~MainWindow();
public slots:
    void update_timex_user();
    void save_user();
    void add_user();
    void delete_user();
    void change_user();
    void save_image();
    void download_image();
    void new_user();
    void fn_new_user();
    void fn_update_user();
    void reconnect();
    void settings();
    void clearLineEdit();
    void button_clik();

private:
    QWidget *mainWidget;
    QWidget *search;
    QWidget *scrollWidget;
    //InfaWidget *information;
    QScrollArea *scrollarea;
    QVBoxLayout *vlayout;
    QVBoxLayout *vlayout_2;
    QHBoxLayout *hlayout;
    QGridLayout *gridlayout;
    QLineEdit *nm,*ln,*mn,*card;
    QPushButton *button;
    QPixmap *img;
};

class InfaWidget : public QWidget
{
    Q_OBJECT

public:
    bool eventFilter(QObject *obj, QEvent *event);
    InfaWidget(MainWindow *window,QWidget *parent = 0);
    QGridLayout *leftLayout;
    MainWindow *wind;
    QLabel *lable;
    QComboBox *box;
    QLineEdit *name;
    QLineEdit *Lastname;
    QLineEdit *Midname;
    QLineEdit *cardnumber;
    QTextEdit *address;
    QLineEdit *ps_serial;
    QLineEdit *ps_number;
    QLineEdit *ps_date;
    QLineEdit *ps_place;
    QLineEdit *birthday;
    QLineEdit *email;
    QLineEdit *mobile;
    QLineEdit *depart;
    QPushButton *new_user;
    QPushButton *update_user;
    QPushButton *update_timex;
};

class QLoginDialog : public QDialog
{
    Q_OBJECT
public:
    int prava;
   // void login();
    void errorMesage(QString message);
    QLoginDialog(QWidget *parent = 0);
    //~QLoginDialog();
public slots:
    void enter_user();
};

bool createConnection(QFile *file);
void createConnectionSqlite();


#endif // MAINWINDOW_H
