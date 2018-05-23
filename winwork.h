#ifndef WINWORK_H
#define WINWORK_H

#include <QMainWindow>
#include <QTime>
#include <QMap>
#include <QTextEdit>
#include "netip.h"

class netip;
namespace Ui {
class Winwork;
}

class Winwork : public QMainWindow
{
    Q_OBJECT

public:
    explicit Winwork(QWidget *parent = 0);
    ~Winwork();
    netip *NP; //connect net*
    QMultiMap<QString,QString> MessageContact;
    QMap<QString,QString> contacts;
    QList<QString> name_contact;
    QList<QString> id_contact;
    QByteArray getWrite();
    QString NameUser;
    QString str_id;
    QString id;
    QWidget* getSW();
    QWidget* getWD();
    QWidget* getListCont();
    QString OutIDCI, OutMessage;
    QString getId();
    QString getIdOut();
    QString getMessage();
    void setIdContact(const QString& str);
    void setNameContact(const QString& str);
    void setUserName(const QString& str);
    void AddDialogWin(const QString& str);
    void WinBrash();
    void addOfMessage(const QString& idOut, const QString& Message);
    void setId(const QString& str);

private slots:
    void on_listContacts_itemClicked();
    void on_listContacts_clicked(const QModelIndex &index);
    void on_butSay_clicked();

private:
    Ui::Winwork *ui;
};

#endif // WINWORK_H
