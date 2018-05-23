#ifndef SERVERWIN_H
#define SERVERWIN_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QTime>
#include <QVector>
#include <QMap>
#include "mysqlconnect.h"
#include "serverwin.h"
#include "style.h"

class QTcpServer;
class QTcpSocket;
namespace Ui {
class ServerWin;
}

class ServerWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWin(int nPort,QWidget *parent = 0);
    ~ServerWin();
    QSqlTableModel* model;
    MySqlConnect MYC;
    QString NameTable;
    QList<QTcpSocket> NumConnectToClient;
    QHash<QString,QTcpSocket*> MapIdToConnectOfClients;/*add*17*/

private:
    Ui::ServerWin *ui;
    QTcpServer* m_pTcpServer;
    quint16 m_nNextBlockSize;
    void SendToData(QTcpServer* pSocket);
    void FirstSendToClient(QTcpServer* pSocket);
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void MessToClient(const QString& idIn, const QString& idOut, QTime time, const QString& str);
    void sendToClientInfo(QTcpSocket* pSocket, const QString& str, QString& id, QString& UserName);
    void MessToClientOfDB(const QString& idWr,const QString& idIn, const QString& idOut, QTime time, const QString& str);

public slots:
    void slotReadClient();
    void slotAuthClient();
    virtual void slotNewConnect();

private slots:
    void on_ListTable_editTextChanged(const QString &arg1);
    void on_ListTable_currentIndexChanged(int index);
    void on_txtStatus_destroyed();
    void on_butRefresh_clicked();
    void on_butApply_clicked();
    void on_butReset_clicked();
};

#endif // SERVERWIN_H
