#ifndef NETIP_H
#define NETIP_H
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>
#include <QDebug>
#include "winauth.h"
#include "winwork.h"

class WinAuth;
class Winwork;

class netip : public QObject
{
    Q_OBJECT

public:
    explicit netip(QString HostName, int PortAdr,QObject *parent = nullptr);
    ~netip();
    QTcpSocket* n_pTcpSocket;
    QList<QString> BufSocket;
    QList<QPixmap> image_contact;
    WinAuth* WA; // WinAuth connect
    Winwork* WW; // Winwork connect
    quint16 m_nNextBlockSize;
    quint16 m_nNextBlockSize_X64;
    QString StrError, CMessage, strHost, Log, Pas;
    QString KeyA;
    QString Username;
    QString id_contact;
    QString name_contact;
    int nPort;
    short int counter = 0;
    void ConnectServer();
    void writeSocket();

private slots:
    void slotError(QAbstractSocket::SocketError);
    void slotConnect();
    void slotWriteSocket_A();
    void slotReadSocket_A();
    void slotWriteSocket_I();
    void slotReadSocket_I();
    void slotWriteSocket_W();
};

#endif // NETIP_H
