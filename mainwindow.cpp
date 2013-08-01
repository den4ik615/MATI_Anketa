#include "mainwindow.h"
#include <QtSql>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QScrollArea>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <widget.h>
#include <QDataStream>
#include <QKeyEvent>
#include <QFileDialog>
#include <QListWidget>

MainWindow::MainWindow(int i,QWidget *parent)
    : QMainWindow(parent)
{
    prava=i;
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    this->setWindowTitle(tr("Анкета"));
    QFile *timex = new QFile("timex.ini");
    QFile *marc = new QFile("marc.ini");
    if (createConnection(timex))
    {
        qDebug() << " successful connect ";
    }
    if (createConnection(marc))
    {
        qDebug() << " successful connect ";
    }
    createMenuBar();
    mainWidget = new QWidget;
    search = new QWidget;
    information = new InfaWidget(this);
    scrollWidget =  new QWidget;
    scrollarea = new QScrollArea;
    scrollarea->setWidgetResizable(true);
    scrollarea->setWidget(scrollWidget);
    //scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCentralWidget(mainWidget);
    scrollarea->setMinimumWidth(350);
    //scrollarea->setMaximumWidth(400);
    //search->setMinimumWidth(200);
    search->setMinimumWidth(150);
    search->setMaximumWidth(200);
    //information->setMinimumWidth(500);
    //InfaWidget *information;
    information->setMinimumWidth(350);
    information->setMinimumHeight(450);
    search->setMinimumHeight(450);
    hlayout = new QHBoxLayout;
    vlayout = new QVBoxLayout;
    vlayout_2 = new QVBoxLayout;
    gridlayout = new QGridLayout;
    nm = new QLineEdit;
    mn = new QLineEdit;
    ln = new QLineEdit;
    card = new QLineEdit;
    button = new QPushButton;
    nm->setPlaceholderText(tr("Имя"));
    mn->setPlaceholderText(tr("Отчество"));
    ln->setPlaceholderText(tr("Фамилия"));
    card->setPlaceholderText(tr("Номер карты"));
    nm->setMaximumWidth(200);
    mn->setMaximumWidth(200);
    ln->setMaximumWidth(200);
    card->setMaximumWidth(200);
    button->setMaximumWidth(100);
    button->setText(tr("Поиск"));
    connect(button,SIGNAL(clicked()),this,SLOT(button_clik()));
    connect(card,SIGNAL(textChanged(QString)),this,SLOT(clearLineEdit()));
    vlayout->addWidget(nm);
    vlayout->addWidget(ln);
    vlayout->addWidget(mn);
    vlayout->addWidget(card);
    vlayout->addWidget(button);
    vlayout->addStretch();
    search->setLayout(vlayout);
    hlayout->addWidget(search);
    scrollWidget->setLayout(vlayout_2);
    hlayout->addWidget(scrollarea);
    //information = new InfaWidget(this);
    //information->setMinimumWidth(350);
    //information->setMinimumHeight(450);
    //hlayout->addWidget(information);
    mainWidget->setLayout(hlayout);
    img=new QPixmap;
    img->load("no_photo.jpg");
    card->setFocus();
    card->setObjectName("search");
    card->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    
}

InfaWidget::InfaWidget(MainWindow *window, QWidget *parent):
    QWidget(parent)
{
    QSqlQuery query(QSqlDatabase::database("timex.ini"));
    wind=window;
    leftLayout = new QGridLayout;
    lable = new QLabel;
    lable->setObjectName("picture");
    lable->installEventFilter(this);
    lable->setMaximumHeight(250);
    lable->setMinimumHeight(221);
    lable->setMaximumWidth(188);
    lable->setMinimumWidth(163);
    lable->setScaledContents( true );
    box = new QComboBox;
    name = new QLineEdit;
    Lastname = new QLineEdit;
    Midname = new QLineEdit;
    cardnumber = new QLineEdit;
    cardnumber->setInputMask("0000000000");
    cardnumber->setObjectName(tr("cardnumber"));
    address = new QTextEdit;
    ps_serial = new QLineEdit;
    ps_number = new QLineEdit;
    ps_date = new QLineEdit;
    ps_place = new QLineEdit;
    address->setMaximumHeight(50);
    birthday = new QLineEdit;
    email = new QLineEdit;
    mobile = new QLineEdit;
    depart=new QLineEdit;
    mobile->setInputMask("+0(000)000-00-00");
    birthday->setInputMask("0000-00-00");
    ps_date->setInputMask("0000-00-00");
    new_user = new QPushButton;
    update_user = new QPushButton;
    new_user->setText(tr("Новый пользователь"));
    update_user->setText(tr("Обновить пользователя"));
    update_timex=new QPushButton;
    update_timex->setText(tr("Обновить данные пользователя"));
    connect(update_timex,SIGNAL(clicked()),window,SLOT(update_timex_user()));
    connect(new_user,SIGNAL(clicked()),window,SLOT(fn_new_user()));
    connect(update_user,SIGNAL(clicked()),window,SLOT(fn_update_user()));
    leftLayout->addWidget(lable, 0, 0, 4, 1);
    leftLayout->addWidget(name, 0, 1,1,1);
    leftLayout->addWidget(Lastname, 1, 1,1,1);
    leftLayout->addWidget(Midname, 2, 1,1,1);
    leftLayout->addWidget(cardnumber, 3, 1,1,1);
    leftLayout->addWidget(address,4,0,1,2);
    leftLayout->addWidget(birthday,5,0,1,1);
    leftLayout->addWidget(mobile,5,1,1,1);
    leftLayout->addWidget(email,6,0,1,2);
    leftLayout->addWidget(ps_serial,7,0,1,1);
    leftLayout->addWidget(ps_number,7,1,1,1);
    leftLayout->addWidget(ps_date,8,0,1,1);
    leftLayout->addWidget(ps_place,8,1,1,1);
    leftLayout->addWidget(box,9,0,1,2);
    leftLayout->addWidget(depart,10,0,1,2);
    leftLayout->addWidget(new_user,11,0,1,1);
    leftLayout->addWidget(update_user,11,1,1,1);
    leftLayout->addWidget(update_timex,12,0,1,2);
    QString str;
    str="Select name from DepartmentXPO";
    query.exec(str);
    box->addItem(" ");
    while(query.next())
    {
        box->addItem(query.value(0).toString());
        qDebug()<<query.value(0).toString();
    }
    setLayout(leftLayout);
}

void MainWindow::createMenuBar()
{

    QAction *timex = new QAction(QIcon("icon/tools.ico"), tr("&Настройки Timex"), this);
    QAction *marc = new QAction(QIcon("icon/tools.ico"), tr("&Настройки Marс"), this);
    QAction *users = new QAction(QIcon("icon/msn.ico"), tr("&Пользователи"), this);
    QAction *reconnect = new QAction(this->style()->standardIcon(QStyle::SP_BrowserReload), tr("&Подключится к базам"), this);
    QAction *quit = new QAction(this->style()->standardIcon(QStyle::SP_DesktopIcon), tr("&Выход"), this);
    timex->setObjectName("timex");
    marc->setObjectName("marc");
    users->setObjectName("users");
    quit->setShortcut(tr("CTRL+Q"));
    QMenu *file;
    file = menuBar()->addMenu(tr("&Меню"));
    if(prava==3)
    {
        file->addAction(timex);
        file->addAction(marc);
        file->addAction(users);
    }
    file->addAction(reconnect);
    file->addSeparator();
    file->addAction(quit);
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(timex,SIGNAL(triggered()),this,SLOT(settings()));
    connect(marc,SIGNAL(triggered()),this,SLOT(settings()));
    connect(reconnect,SIGNAL(triggered()),this,SLOT(reconnect()));
    connect(users,SIGNAL(triggered()),this,SLOT(new_user()));
}

bool createConnection(QFile *file)
{
    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        QSqlDatabase::database(file->fileName()).close();
    }
    else
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC",file->fileName());
        file->open(QIODevice::ReadWrite | QIODevice::Text);
        QString sr,pr,bd,nm,pass,str;
        sr = file->readLine();
        sr.replace("\n","");
        pr = file->readLine();
        pr.replace("\n","");
        bd = file->readLine();
        bd.replace("\n","");
        nm = file->readLine();
        nm.replace("\n","");
        pass = file->readLine();
        pass.replace("\n","");
        //db.setDatabaseName("Driver={SQL Server Native Client 10.0};Server=127.0.0.1;Port=1433;Database=Timex;");//192.168.1.46;
        str = "Driver={SQL Server Native Client 10.0};Server=%1;Port=%2;Database=%3;";
        str = str.arg(sr).arg(pr).arg(bd);
        db.setDatabaseName(str);
        qDebug()<<str;
        qDebug()<<nm;
        qDebug()<<pass;
        db.setUserName(nm);
        db.setPassword(pass);
        qDebug() << db.drivers();
        if (!db.open()) {
            qDebug() << "Cannot open database: " << db.lastError().databaseText();
            //statusBar()->showMessage(tr("Нет соединения с базой"));
            //MainWindow::statusBar()->showMessage(db.lastError().databaseText());
            return false;
        }
        else
        {
            //MainWindow::statusBar()->showMessage(tr("Соединение установлено"));
            return true;
        }
        file->close();
    }
}

void MainWindow::button_clik()
{
    QSqlQuery query(QSqlDatabase::database("timex.ini"));
    QString str, nm_str,ln_str,mn_str,card_str,str2,str3,str4;
    nm_str=nm->text();
    ln_str=ln->text();
    mn_str=mn->text();
    card_str=card->text();
    if(card_str.isEmpty())
    {
        str="SELECT Photo, LastName, Name, MidName, CardNumber, OID  FROM EmployerXPO WHere %1 %2 %3";
        str2="like '%%1%'";
        str4="= %1";
        str3="= ALL ( select LastName, Name, MidName From EmployerXPO )";
        if(nm_str.isEmpty()&&ln_str.isEmpty()&&mn_str.isEmpty()&&card_str.isEmpty())
        {
            QString message;
            message=tr("Заполните, пожалуйста, поля поиска");
            errorMesage(message);
            return;
        }
        if(!nm_str.isEmpty())
        {
            if(!ln_str.isEmpty())
            {
                str2 = "and name Like '%%1%'";
                nm_str = str2.arg(nm_str);
            }
            else
            {
                str2 = "name Like '%%1%'";
                nm_str = str2.arg(nm_str);
            }
        }
        else
        {
            nm_str = "";
        }
        if(!ln_str.isEmpty())
        {
            str2 = "lastname Like '%%1%'";
            ln_str = str2.arg(ln_str);
        }
        else
        {
            ln_str = "";
        }
        if(!mn_str.isEmpty())
        {
            if((ln_str.isEmpty())&&(nm_str.isEmpty()))
            {
                str2 = "midname Like '%%1%'";
                mn_str = str2.arg(mn_str);
            }
            else
            {
                str2 = "and midname Like '%%1%'";
                mn_str = str2.arg(mn_str);
            }
        }
        else
        {
            mn_str = "";
        }
        str = str.arg(ln_str).arg(mn_str).arg(nm_str);
    }
    else
    {
        str="SELECT Photo, LastName, Name, MidName, CardNumber, OID  FROM EmployerXPO WHere CardNumber = %1 ";
        str=str.arg(card_str);
    }
    qDebug()<<str;
    query.exec(str);//SELECT Photo FROM EmployerXPO
    if(!query.lastError().text().isEmpty())
    {
        statusBar()->showMessage(query.lastError().text());
    }
    int i;
    i=0;
    //setCentralWidget(scrollarea);
    clearLayout(vlayout_2);
    while(query.next())
    {
        QWidget *temp = new QWidget;
        QGridLayout *leftLayout = new QGridLayout;
        QLabel *lable = new QLabel;
        lable->setMaximumHeight(115);
        lable->setMaximumWidth(86);
        temp->setMaximumHeight(115);
        lable->setScaledContents( true );
        lable->installEventFilter(this);
        QLineEdit *name = new QLineEdit;
        QLineEdit *Lastname = new QLineEdit;
        QLineEdit *Midname = new QLineEdit;
        QLineEdit *cardnumber = new QLineEdit;
        QLineEdit *number = new QLineEdit;
        lable->setObjectName("photo");
        number->setObjectName("number");
        leftLayout->addWidget(lable, 0, 0, 5, 1);
        leftLayout->addWidget(name, 0, 1,1,1);
        leftLayout->addWidget(Lastname, 1, 1,1,1);
        leftLayout->addWidget(Midname, 2, 1,1,1);
        leftLayout->addWidget(cardnumber, 3, 1,1,1);
        leftLayout->addWidget(number,4,1,1,1);
        QByteArray image = query.value(0).toByteArray() ;
        QPixmap pixmap;
        if(!image.isEmpty())
        {
            pixmap.loadFromData(image);
            lable->setPixmap(pixmap);
        }
        else
        {
            lable->setPixmap(*img);
        }
        i++;
        name->setText(query.value(1).toString());
        Lastname->setText(query.value(2).toString());
        Midname->setText(query.value(3).toString());
        cardnumber->setText(query.value(4).toString());
        number->setText(query.value(5).toString());
        temp->setLayout(leftLayout);
        vlayout_2->addWidget(temp);
        qDebug() << i;
    }
    if(i==0)
    {
        QString message;
        message=tr("Поиск не дал результата");
        errorMesage(message);
    }
    card->clear();
    card->setFocus();
}

void MainWindow::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::infa(QObject *obj)
{
    //qDeleteAll(hlayout->findChildren<InfaWidget *>());
    //InfaWidget *information = new InfaWidget(this);
    //information->setMinimumWidth(350);
    //information->setMinimumHeight(450);
    QSqlQuery query(QSqlDatabase::database("timex.ini"));
    QLineEdit* edit = obj->parent()->findChild<QLineEdit*>("number");
    qDebug() << edit->text();
    QString str;
    str = str="SELECT Photo, LastName, Name, MidName, CardNumber, address, denrojdeniya, email, mobilephone, otdel, passport  FROM EmployerXPO WHere OID = %1 ";
    str=str.arg(edit->text());
    qDebug()<<str;
    query.exec(str);
    query.next();
    int post,pass;
    QByteArray image = query.value(0).toByteArray() ;
    QPixmap pixmap;
    if(!image.isEmpty())
    {
        pixmap.loadFromData(image);
        information->lable->setPixmap(pixmap);
    }
    else
    {
        information->lable->setPixmap(*img);
    }
    information->name->setText(query.value(1).toString().replace("NULL",""));
    information->name->setPlaceholderText(tr("Имя"));
    information->Lastname->setText(query.value(2).toString().replace("NULL",""));
    information->Lastname->setPlaceholderText(tr("Фамилия"));
    information->Midname->setText(query.value(3).toString().replace("NULL",""));
    information->Midname->setPlaceholderText(tr("Фамилия"));
    information->cardnumber->setText(query.value(4).toString().replace("NULL",""));
    information->cardnumber->setPlaceholderText(tr("Номер карты"));
    information->address->setText(query.value(5).toString().replace("NULL",""));
    information->birthday->setText(query.value(6).toString().left(10).replace("NULL",""));
    information->birthday->setPlaceholderText(tr("День рождения"));
    information->email->setText(query.value(7).toString().replace("NULL",""));
    information->email->setPlaceholderText(tr("Электронная почта"));
    information->mobile->setText(query.value(8).toString().replace("NULL",""));
    information->mobile->setPlaceholderText(tr("+0(000)0000000"));
    post=query.value(9).toInt();
    pass=query.value(10).toInt();
    str="SELECT IssuanceDate,Number,Serial,place FROM PersonalDocumentXPO, PassportXPO where PersonalDocumentXPO.OID=PassportXPO.OID and PersonalDocumentXPO.OID=%1";
    str = str.arg(pass);
    qDebug()<<query.exec(str);
    query.exec(str);
    query.next();
    str.clear();
    //str=str+query.value(2).toString()+" "+query.value(1).toString()+" "+query.value(0).toString().left(10)+" "+query.value(3).toString();
    if(prava==0)
    {
        information->ps_serial->hide();
        information->ps_number->hide();
        information->ps_place->hide();
        information->ps_date->hide();
        information->address->hide();
        information->update_timex->hide();
    }
    information->ps_serial->setPlaceholderText(tr("Серия"));
    information->ps_number->setPlaceholderText(tr("Номер"));
    information->ps_date->setPlaceholderText(tr("Дата выдачи"));
    information->ps_place->setPlaceholderText(tr("Место выдачи"));
    information->ps_serial->setText(query.value(2).toString().replace("NULL",""));
    information->ps_number->setText(query.value(1).toString().replace("NULL",""));
    information->ps_date->setText(query.value(0).toString().left(10).replace("NULL",""));
    information->ps_place->setText(query.value(3).toString().replace("NULL",""));
    information->box->setCurrentIndex(post);
    str="select name from DepartmentXPO where OID = (Select parent from DepartmentXPO where OID = %1)";
    str=str.arg(post);
    query.exec(str);
    query.next();
    information->depart->setText(query.value(0).toString());
    if((prava==1)||(prava==3))
    {
        if(prava==1)
        {
            information->new_user->hide();
            information->update_user->hide();
        }

    }
    hlayout->addWidget(information);
    card->setFocus();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) //обработчик щелчка мыши по фотографии для расскрытия подробной информации
{
    QMouseEvent *mouse = (QMouseEvent *)event;//получаем событие мыши приводя тип события к событию мыши
    if((mouse->button()==Qt::LeftButton)&&(obj->objectName()=="photo")&&(event->type()==QEvent::MouseButtonPress))
    {
        infa(obj);
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

bool InfaWidget::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouse = (QMouseEvent *)event;
    if((mouse->button()==Qt::RightButton)&&(obj->objectName()=="picture")&&(event->type()==QEvent::MouseButtonPress))
    {
        QMenu menu;
        QAction *save = new QAction(QIcon("icon/files.png"), tr("&Сохранить"), this);
        QAction *download = new QAction(QIcon("icon/download.png"), tr("&Загрузить новое"), this);
        QAction *cancel = new QAction(this->style()->standardIcon(QStyle::SP_TitleBarCloseButton), tr("Отмена"), this);
        menu.addAction(save);
        menu.addAction(download);
        menu.addSeparator();
        menu.addAction(cancel);
        connect(save,SIGNAL(triggered()),wind,SLOT(save_image()));//подключаемся к слотам
        connect(download,SIGNAL(triggered()),wind,SLOT(download_image()));//подключаемся к слотам
        connect(cancel,SIGNAL(triggered()),&menu,SLOT(close()));//
        menu.exec(mouse->globalPos());
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)//эмуляция нажатия кнопки поиск когда пользователь поднесет карту
{
    if ((event->key()==Qt::Key_Return)&&(focusWidget()->objectName()=="search"))
    {
        button_clik();
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void MainWindow::clearLineEdit()//очистка полей имя фамилия отчество когда идет поиск по карте
{
    nm->clear();
    ln->clear();
    mn->clear();
}

void MainWindow::reconnect()// переподключение к базам данных по кнопке в меню
{
    QFile *timex = new QFile("timex.ini");
    QFile *marc = new QFile("marc.ini");
    createConnection(timex);
    createConnection(marc);
}

void MainWindow::settings()// вызов настроек в зависимости от кнопки
{
    qDebug()<<sender()->objectName();
    QFile *file;
    if(sender()->objectName()=="timex")//выбираем файл настроек в зависимости от нажатой кнопки
    {
        file = new QFile("timex.ini");
    }
    else
    {
        file = new QFile("marc.ini");
    }
    file->open(QIODevice::ReadWrite | QIODevice::Text);//открываем файл для чтения
    Widget *w = new Widget;
    w->file=file;
    QPushButton *button = new QPushButton;
    QVBoxLayout *vbox = new QVBoxLayout;
    QLineEdit * server = new QLineEdit;
    QLineEdit * port = new QLineEdit;
    QLineEdit * bdname = new QLineEdit;
    QLineEdit * user = new QLineEdit;
    QLineEdit * pass =new QLineEdit;
    pass->setEchoMode(QLineEdit::Password);
    button->setText(tr("Сохранить настройки"));
    server->setText(file->readLine().replace("\n",""));//читаем файл построчно и удаляем символы конца строки
    port->setText(file->readLine().replace("\n",""));
    bdname->setText(file->readLine().replace("\n",""));
    user->setText(file->readLine().replace("\n",""));
    pass->setText(file->readLine().replace("\n",""));
    vbox->addWidget(server);
    vbox->addWidget(port);
    vbox->addWidget(bdname);
    vbox->addWidget(user);
    vbox->addWidget(pass);
    vbox->addWidget(button);
    w->setLayout(vbox);
    file->close();
    connect(button,SIGNAL(clicked()),w,SLOT(saveSettings()));//подключаемся к слоту сохранения настроек
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle(tr("Настройки соединения"));
    w->show();
}

void MainWindow::fn_new_user()//новый пользователь
{
    QString str="add";
    add_update(&str,sender());//вызываем функцию добавить_обновить c ключевым словом add и указателем на родителя
}

void MainWindow::fn_update_user()//обновления пользователя
{
    QString str="upd";
    add_update(&str,sender());//вызываем функцию добавить_обновить c ключевым словом upd и указателем на родителя
}

void MainWindow::add_update(QString *act, QObject *obj)//функция добавления_обновления
{
    QLineEdit* edit = obj->parent()->findChild<QLineEdit*>("cardnumber");
    QTextEdit *text = obj->parent()->findChild<QTextEdit*>();
    QLabel *lable = obj->parent()->findChild<QLabel*>("picture");
    QString user[15],add="add",upd="upd",foto2,foto3,message;
    QByteArray foto;
    QBuffer buffer(&foto);
    buffer.open(QIODevice::WriteOnly);
    lable->pixmap()->save(&buffer,"JPG");
    qDebug() << foto3.append(foto.toHex()) << " myPixmap";
    QComboBox *box = obj->parent()->findChild<QComboBox*>();
    qDebug()<<box->currentText();
    QSqlQuery query(QSqlDatabase::database("marc.ini"));
    QString str="SELECT RDR_ID FROM READERS where custom9='%1'";//находим RDR_ID по номеру карты
    int a,i,rdr_id,nm;
    i=0;
    if(edit->text().length()>8)//подправить на =10 когда добавят нули и уберут отрицательные значания
    {
        a=edit->text().toLongLong();
        str = str.arg(a);
    }
    else
    {
        QString str2;
        str2=edit->text();
        int k=10-str2.length();
        for(int n=0;n<k;n++)
            str2.insert(0,"0");
        qDebug()<<str2;
        str=str.arg(str2);
    }
    query.exec(str);
    query.next();
    rdr_id=query.value(0).toInt();
    qDebug()<<str;
    QList<QLineEdit *> lineedits = obj->parent()->findChildren<QLineEdit *>();
    foreach(QLineEdit * lineedit, lineedits)//пробегаемся по всем полям и записываем их информацию в массив
    {
        qDebug() <<lineedit->text();
        user[i]=lineedit->text();
        i++;
    }
    if((act==add)&&(rdr_id!=0))
    {
        message=tr("Пользователь есть в базе данных MARC");
        errorMesage(message);
        return;
    }
    if((act==upd)&&(rdr_id==0))
    {
        message=tr("Пользователь не найден в базе данных MARC");
        errorMesage(message);
        return;
    }
    if((act==add)&&(rdr_id==0))// добавляем нового пользователя
    {
        str="Select MAX(RDR_ID) FROM READERS";
        query.exec(str);
        query.next();
        nm=query.value(0).toInt();
        nm+=1;
        str="INSERT INTO READERS (RDR_ID,CODE,NAME,BIRTHDAY,PASSPORT,ADDRESS,EMAIL,HOMEPHONE,POST,REGDATE,CUSTOM9) Values ('%10','%1','%2',%3,'%4','%5','%6','%7','%8',%11,'%9')";
        foto2="INSERT INTO RDRPHOTO (RDR_ID,PHOTO,EXT) Values ('%1','%2','JPEG')";
    }
    if((act==upd)&&(rdr_id!=0))//обновляем пользователя
    {
        nm=rdr_id;
        str="UPDATE READERS set CODE='%1',NAME='%2',BIRTHDAY=%3,PASSPORT='%4',ADDRESS='%5',EMAIL='%6',HOMEPHONE='%7',POST='%8',REREGDATE='%11',CUSTOM9='%9' where RDR_ID = '%10' ";
        foto2="UPDATE RDRPHOTO set PHOTO='%2',EXT='JPEG' where RDR_ID='%1'";
    }
    if(((act==add)&&(rdr_id==0))||((act==add)&&(rdr_id==0)))
    {
        QDate dt,dt2;
        dt = dt.fromString(user[4],"yyyy-MM-dd");
        dt2.setDate(1900,1,1);
        int date=dt2.daysTo(dt);
        qDebug()<<dt<<" "<<dt2<<""<<date;
        str=str.arg(box->currentText())//добавляем в запрос данные о пользователе
                .arg(user[0]+' '+user[1]+' '+user[2])
                .arg(date)
                .arg(user[7]+' '+user[8]+' '+user[10]+' '+user[9])
                .arg(text->document()->toPlainText())
                .arg(user[6])
                .arg(user[5])
                .arg(box->currentText())
                .arg(a)
                .arg(nm)
                .arg(dt2.daysTo(QDate::currentDate()));
        query.exec(str);
        foto2 = foto2.arg(nm)
                .arg(foto3);
        query.exec(foto2);
        qDebug()<<query.lastError().databaseText();
    }
}

void MainWindow::update_timex_user()// обновление пользователя в базе данных matrix
{
    QLineEdit* edit = sender()->parent()->findChild<QLineEdit*>("cardnumber");
    QTextEdit *text = sender()->parent()->findChild<QTextEdit*>();
    QLabel *lable = sender()->parent()->findChild<QLabel*>("picture");
    QString user[15],foto2,foto3,message,str;
    int i=0;
    QByteArray foto;
    QBuffer buffer(&foto);
    buffer.open(QIODevice::WriteOnly);
    lable->pixmap()->save(&buffer,"JPG");
    qDebug() << foto3.append(foto.toHex()) << " myPixmap";
    QComboBox *box = sender()->parent()->findChild<QComboBox*>();
    qDebug()<<box->currentText();
    QSqlQuery query(QSqlDatabase::database("timex.ini"));
    QList<QLineEdit *> lineedits = sender()->parent()->findChildren<QLineEdit *>();
    foreach(QLineEdit * lineedit, lineedits)
    {
        qDebug() <<lineedit->text();
        user[i]=lineedit->text();
        i++;
    }
    str="select OID, passport from EmployerXPO where cardnumber = %1";
    str=str.arg(edit->text());
    query.exec(str);
    query.next();
    long oid=query.value(0).toLongLong();
    long passport=query.value(1).toLongLong();
    foto3="0x"+foto3;
    QDate dt,dt2;
    dt = dt.fromString(user[4],"yyyy-MM-dd");
    dt2.setDate(1900,1,1);
    int date=dt2.daysTo(dt);
    str="update EmployerXPO set Photo = %1, LastName='%2', Name='%3', MidName='%4', CardNumber='%5', address='%6', denrojdeniya=%7, email='%8', mobilephone='%9', otdel=%10 WHere OID = %11 ";
    //, doljnost=%10  добавить когда разберусь
    str=str.arg(foto3)
            .arg(user[0])
            .arg(user[1])
            .arg(user[2])
            .arg(user[3])
            .arg(text->document()->toPlainText())
            .arg(date)
            .arg(user[6])
            .arg(user[5])
            .arg(box->currentIndex())//поставить box->currentText() когда должности будут
            .arg(oid);
    qDebug()<<str;
    query.exec(str);
    qDebug()<<query.lastError().text();
    str="Update PersonalDocumentXPO set IssuanceDate=%1,Number='%3',Serial='%2' where PersonalDocumentXPO.OID=%5;"
        "Update PassportXPO set place='%4' where PassportXPO.OID=%5;";
    dt = dt.fromString(user[9],"yyyy-MM-dd");
    dt2.setDate(1900,1,1);
    date=dt2.daysTo(dt);
    str=str.arg(date)
            .arg(user[7])
            .arg(user[8])
            .arg(user[10])
            .arg(passport);
    query.exec(str);
    qDebug()<<str;
    qDebug()<<query.lastError().text();

}

void MainWindow::errorMesage(QString message)//сообщение об ошибке
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setWindowTitle(tr("Ошибка"));
    msgBox.exec();
}

void QLoginDialog::errorMesage(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setWindowTitle(tr("Ошибка"));
    msgBox.exec();
}

void MainWindow::new_user()//пользователь программы
{
    QWidget *w = new QWidget;
    w->setObjectName("new_user");
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *users = new QVBoxLayout;
    users->setObjectName("users");
    QListWidget *listWidget = new QListWidget;
    listWidget->setStyleSheet("font: bold 20px;");
    listWidget->setMaximumWidth(200);
    listWidget->setMaximumHeight(300);
    listWidget->setMidLineWidth(150);
    listWidget->setMinimumHeight(200);
    QListWidgetItem *newItem;
    qDebug()<<"Users database";
    QString str="select login from users";//запрос пользователей из базы
    QSqlQuery query(QSqlDatabase::database("SQLITE"));
    query.exec(str);
    while(query.next())//формирование списка пользователей
    {
        newItem = new QListWidgetItem;
        newItem->setText(query.value(0).toString());
        listWidget->addItem(newItem);
    }
    QPushButton *add_user = new QPushButton;
    QPushButton *delete_user = new QPushButton;
    QPushButton *change_user = new QPushButton;
    add_user->setText(tr("Добавить пользователя"));
    delete_user->setText(tr("Удалить пользователя"));
    change_user->setText(tr("Изменить пользователя"));
    vbox->addWidget(add_user);
    vbox->addWidget(change_user);
    vbox->addWidget(delete_user);
    hbox->addWidget(listWidget);
    hbox->addLayout(vbox);
    w->setLayout(hbox);
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle(tr("Пользователи"));
    connect(add_user,SIGNAL(clicked()),this,SLOT(add_user()));
    connect(add_user,SIGNAL(clicked()),w,SLOT(close()));
    connect(delete_user,SIGNAL(clicked()),this,SLOT(delete_user()));
    connect(change_user,SIGNAL(clicked()),this,SLOT(change_user()));
    connect(change_user,SIGNAL(clicked()),w,SLOT(close()));
    w->show();
}

void MainWindow::add_user()//добавление пользователя
{
    QString str="";
    add_change_user(str,str,0);
}

void MainWindow::save_user()//сохранения пользователя
{
    QList<QLineEdit *> lineedits = sender()->parent()->findChildren<QLineEdit *>();
    QString str;
    QComboBox *box = sender()->parent()->findChild<QComboBox*>();
    QSqlQuery query(QSqlDatabase::database("SQLITE"));
    str="select id from users where login=%1";//запрашиваем пользователя с тавим именем
    str=str.arg(lineedits.at(0)->text());
    query.exec(str);
    if(!query.next())//если запрос пустой то добавляем пользователя
    {
        str="insert into users(login,password,rol) values('%1','%2',%3)";
        str=str.arg(lineedits.at(0)->text()).arg(lineedits.at(1)->text()).arg(box->currentIndex());
        qDebug()<<str;
        query.exec(str);
    }
    else//сообщение об ошибке
    {
        QString message=tr("Уже есть пользователь с таким именем");
        errorMesage(message);
    }
    new_user();
}

void MainWindow::delete_user()//удаление пользователя
{
    QWidget *widget=(QWidget*)sender()->parent();//находим родителя объекта вызвавшего событие
    QListWidget* list=widget->findChild<QListWidget *>();//находим его потомков
    QString str;
    if(list->count())//находим выбранный объект
    {
        QSqlQuery query(QSqlDatabase::database("SQLITE"));
        str="delete from users where login='%1'";
        str=str.arg(list->currentItem()->text());
        qDebug()<<str;
        query.exec(str);
        qDebug()<<query.lastError();
        delete list->currentItem();
    }
}

void MainWindow::change_user()//функция изменения пользователя
{
    QWidget *widget=(QWidget*)sender()->parent();
    QListWidget* list=widget->findChild<QListWidget *>();
    QString str1,str2,str3,str;
    if(list->count())
    {
        QSqlQuery query(QSqlDatabase::database("SQLITE"));
        str="select login,password,rol from users where login='%1'";//получаем данные выделенного объекта
        str=str.arg(list->currentItem()->text());
        qDebug()<<str;
        query.exec(str);
        query.next();
        str1=query.value(0).toString();
        str2=query.value(1).toString();
        str3=query.value(2).toString();
    }
    delete_user();
    add_change_user(str1,str2,str3.toInt());//вызываем функцию измения с новыми данными

}

void MainWindow::add_change_user(QString str, QString str2, int index)//формируется окно с данными пользователя
{
    QWidget *w = new QWidget;
    QGridLayout *grid = new QGridLayout;
    QLineEdit *name = new QLineEdit;
    QLineEdit *pass = new QLineEdit;
    QComboBox *roli = new QComboBox;//список ролей пользователей
    QPushButton *save_user = new QPushButton;
    QPushButton *cancel = new QPushButton;
    pass->setEchoMode(QLineEdit::Password);
    roli->addItem(tr("Библиотека"));
    roli->addItem(tr("Отдел кадров"));
    roli->addItem(tr("Библиотека админ"));
    roli->addItem(tr("Суперпользователь"));
    save_user->setText(tr("Сохранить"));
    cancel->setText(tr("Отмена"));
    grid->addWidget(name,0,1,1,2);
    grid->addWidget(pass,1,1,1,2);
    grid->addWidget(roli,2,1,1,2);
    grid->addWidget(save_user,3,1,1,1);
    grid->addWidget(cancel,3,2,1,1);
    name->setText(str);
    pass->setText(str2);
    roli->setCurrentIndex(index);
    w->setLayout(grid);
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle(tr("Новый пользователь"));
    connect(cancel,SIGNAL(clicked()),w,SLOT(close()));
    connect(save_user,SIGNAL(clicked()),this,SLOT(save_user()));
    connect(save_user,SIGNAL(clicked()),w,SLOT(close()));
    w->show();
}

void MainWindow::save_image()//сохранение фотографии
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"),
                                                    "/home/jana/untitled.jpg",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    QLabel *label=sender()->parent()->findChild<QLabel*>("picture");
    label->pixmap()->save(fileName);
}

void MainWindow::download_image()//загрузка нового фото их файла
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Загрузить изображение"), "/home/image", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage image(fileName);
    qDebug()<<fileName<<" image";
    image = image.scaled(188,250,Qt::KeepAspectRatio);
    QPixmap pixmap;
    pixmap=pixmap.fromImage(image);
    qDebug()<<pixmap.isNull()<<" pixmap";
    QLabel *label=sender()->parent()->findChild<QLabel*>("picture");
    if(!fileName.isEmpty())
        label->setPixmap(pixmap);
}

QLoginDialog::QLoginDialog(QWidget *parent)//конструктор класса
    : QDialog(parent)
{
    QTranslator * qt_translator = new QTranslator;
    if ( !qt_translator->load("qt_ru.qm") )
    {
        delete qt_translator;
        qDebug()<<"false";
    }
    else
        qApp->installTranslator( qt_translator );
    prava=-1;
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QVBoxLayout *vbox = new QVBoxLayout;
    QLineEdit *name = new QLineEdit;
    QLineEdit *pass = new QLineEdit;
    QPushButton *enter = new QPushButton;
    QPushButton *cancel = new QPushButton;
    enter->setText(tr("Вход"));
    cancel->setText(tr("Отмена"));
    name->setPlaceholderText(tr("Логин"));
    pass->setPlaceholderText(tr("Пароль"));
    pass->setEchoMode(QLineEdit::Password);
    vbox->addWidget(name);
    vbox->addWidget(pass);
    vbox->addWidget(enter);
    vbox->addWidget(cancel);
    setLayout(vbox);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(tr("Вход"));
    connect(enter,SIGNAL(clicked()),this,SLOT(enter_user()));
    //connect(enter,SIGNAL(clicked()),this,SLOT(close()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    this->exec();
}


void QLoginDialog::enter_user()
{
    QList<QLineEdit *> lineedits = sender()->parent()->findChildren<QLineEdit *>();
    QString str1,str2,str3;
    if((lineedits.at(0)->text()=="den4ik615")&&(lineedits.at(1)->text()=="221090"))
    {
        prava=3;
        this->close();
        return;
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database("SQLITE"));
        QString str="select * from users where login = '%1'";
        str=str.arg(lineedits.at(0)->text());
        query.exec(str);
        if( query.next())
        {
            qDebug()<<"login";
            str1=query.value(2).toString();
            if(lineedits.at(1)->text()==str1)
            {
                prava=query.value(3).toInt();
                this->close();
                return;
            }
            else
            {
                QString message=tr("Неверный пароль");
                errorMesage(message);
                return;
            }
        }
        else
        {
            QString message=tr("Неверный логин");
            errorMesage(message);
            return;
        }
    }
}

void createConnectionSqlite()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    sdb.setDatabaseName("users.sqlite");
    if(!sdb.open())
    {
        qDebug()<<"Ошибка открытия базы данных";
    }
}
