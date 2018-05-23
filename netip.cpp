#include "netip.h"

netip::netip(QString HostName, int portAdr,QObject *parent) : QObject(parent), m_nNextBlockSize(0)
{
    WW = new Winwork();
    WA = new WinAuth();
    WA->show();
    strHost = HostName;
    nPort = portAdr;
    n_pTcpSocket = new QTcpSocket(this);
    n_pTcpSocket->connectToHost(strHost, nPort);
    connect(n_pTcpSocket, SIGNAL(connected()),SLOT(slotConnect()));
    /*add slot*/
    if(connect(WA->getSW(), SIGNAL(clicked()),SLOT(slotWriteSocket_A())))
       connect(n_pTcpSocket, SIGNAL(readyRead()), this,SLOT(slotReadSocket_A()));

    connect(WW->getListCont(),SIGNAL(clicked(QModelIndex)),this,SLOT(slotWriteSocket_W()));
}

netip::~netip()
{
    QString KeyStr = "#@1***430701999";
    QTime time;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << WW->getIdOut() << WW->getId() << time << KeyStr;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    n_pTcpSocket->write(arrBlock);
}

void netip::slotConnect()
{
    connect(n_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void netip::slotError(QAbstractSocket::SocketError err)
{
    StrError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                         "The host was not found":
                                         err == QAbstractSocket::RemoteHostClosedError ?
                                         "The remote host is closed":
                                         err == QAbstractSocket::ConnectionRefusedError ?
                                         "The connection was refused":
                                                     QString(n_pTcpSocket->errorString())
                                         );
}

void netip::slotWriteSocket_A()
{
        QByteArray arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << quint16(0) << WA->LogAuth() << WA->PasAuth();
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        n_pTcpSocket->write(arrBlock);
}

void netip::slotReadSocket_A()
{
    m_nNextBlockSize = 0;
    QDataStream in(n_pTcpSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    int counter_Ad = 0;
    short int Ad;
        for(;;)
        {
            QString str_Ad;
            if(!m_nNextBlockSize){
                if(n_pTcpSocket->bytesAvailable() < sizeof(0))
                {
                    break;
                }
                in >> m_nNextBlockSize;
            }
            if(n_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
                  break;

            in >> str_Ad;
            if(str_Ad == "#@1***430701917")
                break;

            BufSocket << str_Ad;
                str_Ad="";
            m_nNextBlockSize = 0;
        }

        foreach (QString it, BufSocket) {
            if(it!=""){

                if(it == "#@1***430701912"){
                    counter_Ad++;
                }


                if(counter_Ad == 1 && it != "#@1***430701912"){
                    id_contact = it;
                    WW->setIdContact(id_contact);
                }

                if(counter_Ad == 2 && it != "#@1***430701912"){
                    name_contact = it;
                    WW->setNameContact(name_contact);
                }

                if(counter_Ad == 3 && it != "#@1***430701912"){
                    Username = it;
                    WW->setUserName(Username);
                }

                if(counter_Ad == 4 && it != "#@1***430701912"){
                    WW->setId(it);
                }

                if(it == "1912"){
                    counter_Ad++;
                    Ad = -1;
                }
            }
        }

        if(Ad == -1)
        {
            WW->show();
            WW->WinBrash();
            WA->hide();
            if(disconnect(n_pTcpSocket,SIGNAL(readyRead()),this,SLOT(slotReadSocket_A())))
            {
                connect(n_pTcpSocket, SIGNAL(readyRead()), this,SLOT(slotReadSocket_I()));
            }

            if(connect(WW->getSW(),SIGNAL(clicked()), this, SLOT(slotWriteSocket_I())))
            {
                connect(n_pTcpSocket, SIGNAL(readyRead()), this,SLOT(slotReadSocket_I()));
            }

        }
        return;
}

void netip::slotWriteSocket_I()
{
    QTime time;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(!WW->getId().isEmpty() && !WW->getIdOut().isEmpty())
    {
        out << quint16(0) << WW->getIdOut() << WW->getId() << time << WW->OutMessage;
        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));
        n_pTcpSocket->write(arrBlock);
    }
}

void netip::slotReadSocket_I()
{
    QString IDI, IDO, MESSAGE, WR;
    QTime TIME;
    QDataStream in(n_pTcpSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for(;;)
    {
        if(!m_nNextBlockSize_X64)
        {
            if(n_pTcpSocket->bytesAvailable() < sizeof(0))
            {
                break;
            }
           in >> m_nNextBlockSize_X64;
        }
        if(n_pTcpSocket->bytesAvailable() < m_nNextBlockSize_X64)
        {
            break;
        }

        in >> IDI >> IDO >> MESSAGE;

        if(!MESSAGE.isEmpty())
        {
            WW->addOfMessage(IDI,MESSAGE);
        }
        m_nNextBlockSize_X64 = 0;
    }
}

void netip::slotWriteSocket_W()
{
    QString KeyStr = "#@1***430701920";
    QTime time;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << WW->getIdOut() << WW->getId() << time << KeyStr;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    n_pTcpSocket->write(arrBlock);
}
