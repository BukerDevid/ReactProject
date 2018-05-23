/*
 * WinWork - основная рабочая форма, окно, где отображается списки контактов, сообщения.*   ۞███████]▄▄▄▄▄▄▄▄▄▄▄
 * Подключает к себе netip, в головном файле.                                           *  ▄▅█████████▅▄▃▂
 *                                                                                      *  █★прорвемся!!★█
 *                                                                                      *  ◥⊙▲⊙▲⊙▲⊙▲⊙▲⊙▲⊙◤ */
#include "winwork.h"
#include "ui_winwork.h"
#include <string>

Winwork::Winwork(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Winwork)
{
    ui->setupUi(this);
    /*==============================STYLE=========================================*/
    /**/QPalette pal = ui->listDialog->palette();                               /**/
    /**/pal.setColor(QPalette::Base, QColor("#6b6b6b"));                        /**/
    /**/pal.setColor(QPalette::Highlight,QColor::fromRgb(0,94,255,60));         /**/
    /**/ui->listDialog->setPalette(pal);                                        /**/
    /**/QPalette pal2 = ui->listContacts->palette();                            /**/
    /**/pal2.setColor(QPalette::Base, QColor("#6b6b6b"));                       /**/
    /**/pal2.setColor(QPalette::Highlight,QColor::fromRgb(245,102,0,60));       /**/
    /**/ui->listContacts->setPalette(pal2);                                     /**/
    /**/QPalette pal3 = ui->centralwidget->palette();                           /**/
    /**/pal3.setColor(QPalette::Base, QColor("#6b6b6b"));                       /**/
    /**/pal3.setColor(QPalette::Text, QColor("#FFFFFF"));                       /**/
    /**/pal3.setColor(ui->centralwidget->backgroundRole(),QColor("#3d3d3d"));   /**/
    /**/ui->centralwidget->setPalette(pal3);                                    /**/
    /**/ui->centralwidget->setAutoFillBackground(true);                         /**/
    /**/QPalette pal4 = ui->butSay->palette();                                  /**/
    /**/pal4.setColor(QPalette::Base, QColor("#6b6b6b"));                       /**/
    /**/pal4.setColor(QPalette::Text, QColor("#FFFFFF"));                       /**/
    /**/pal4.setColor(ui->butSay->backgroundRole(),QColor("#6b6b6b"));          /**/
    /**/ui->butSay->setPalette(pal4);                                           /**/
    /*============================================================================*/
}

Winwork::~Winwork()
{
    delete ui;
}

void Winwork::WinBrash(){
    int counter=0;
    ui->lblName->setText("<p><font color=#FFFFFF>"+NameUser+"</font></p>");
    ui->listContacts->setIconSize(QSize(48,48));
    ui->listContacts->setSelectionMode(QAbstractItemView::SingleSelection);
    foreach(QString it ,id_contact){
        contacts.insert(it,name_contact[counter]);
        counter++;
    }
       ui->listContacts->clear();

        QMap<QString,QString>::iterator it = contacts.begin();
        for(;it != contacts.end(); ++it)
        {
            counter++;
            QListWidgetItem *item = new QListWidgetItem();
            item->setIcon(QPixmap("./Image/"+ it.key() +".jpg"));
            item->setText(it.value() + "\n#" + it.key());
            item->setBackgroundColor(QColor::fromRgb(0,0,0,20));
            item->setTextColor(Qt::white);
            ui->listContacts->addItem(item);
        }
        id_contact.clear();
        name_contact.clear();

}

void Winwork::on_listContacts_itemClicked() //no-Delete!!!
{}

void Winwork::on_listContacts_clicked(const QModelIndex &index)
{
    short int counter = 0;
    QString str,str2;
    str_id.clear();
    QTextStream inStr(&str_id);
        if(!index.isValid())
        {
            return;
        }

        if(QListWidget *listWdg = dynamic_cast< QListWidget* >(sender()))
        {
            if(QListWidgetItem *item = listWdg->item( index.row() ))
            {
                 str = item->text();
                 counter = str.length();
                 if(!str.isEmpty()){
                     for(; counter!=0 ;counter--)
                     {
                         if(str[counter] == "#")
                         {
                                break;
                         }

                         str2 = str[counter] + str2;

                         foreach(QString it, id_contact)
                         {
                            if(str2 == it)
                            {
                                str2.clear();
                                str2 = it;
                            }
                         }
                     }
                 }
            }
        }
        std::string stdstr;
        stdstr = str2.toUtf8().constData();
        str2.clear();
        str2 = QString::fromUtf8(stdstr.c_str());
        inStr << str2;
        ui->listDialog->clear();
        OutIDCI = str_id;
}

void Winwork::addOfMessage(const QString& idOut, const QString& Message)
{
    MessageContact.insert(idOut, Message);

    QMap<QString,QString>::iterator it = contacts.begin();
    for(;it != contacts.end(); ++it)
    {
        if(it.key()==idOut && it.key() == str_id){
            ui->listDialog->setIconSize(QSize(48,48));
            QListWidgetItem *item2 = new QListWidgetItem();
            item2->setIcon(QPixmap("./Image/"+id+".jpg"));
            item2->setText(it.value()+" Mess: "+Message);
            item2->setBackgroundColor(QColor::fromRgb(255,32,32,30));
            item2->setTextColor(Qt::white);
            ui->listDialog->addItem(item2);
            break;
        }
        else if(id == idOut)
        {
            ui->listDialog->setIconSize(QSize(48,48));
            QListWidgetItem *item2 = new QListWidgetItem();
            item2->setIcon(QPixmap("./Image/"+id+".jpg"));
            item2->setText(NameUser+" Mess: "+Message);
            item2->setBackgroundColor(QColor::fromRgb(32,32,255,30));
            item2->setTextColor(Qt::white);
            ui->listDialog->addItem(item2);
            break;
        }
    }
}

void Winwork::on_butSay_clicked()
{
    OutIDCI = str_id;
    OutMessage = ui->txtMessage->text();
    ui->txtMessage->clear();
}

void Winwork::AddDialogWin(const QString& str)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setIcon(QPixmap("./Image/"+id+".jpg"));
    item->setText(str);
    item->setBackgroundColor(QColor("#A1A1A1"));
    ui->listDialog->addItem(item);
}

void Winwork::setIdContact(const QString& str){
    id_contact << str;
}

void Winwork::setNameContact(const QString& str){
    name_contact << str;
}

void Winwork::setUserName(const QString& str){
    NameUser = str;
}

void Winwork::setId(const QString& str){
    id = str;
}

QWidget* Winwork::getSW(){
    return ui->butSay;
}

QString Winwork::getId()
{
    return id;
}

QString Winwork::getIdOut()
{
    return str_id;
}

QString Winwork::getMessage()
{
    return ui->txtMessage->text();
}

QWidget* Winwork::getWD()
{
    return ui->listDialog;
}

QWidget* Winwork::getListCont()
{
    return ui->listContacts;
}

