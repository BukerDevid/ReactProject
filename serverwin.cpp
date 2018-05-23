/*
 * В программе несколько слотов и методов которые отвечают за работу с входящими подключениями.
 * Для того что бы аунтифицировать подключение используется слот slotAuthClient, для формирования ответа
 * клиенту, он использует метод FerstSendToClien. Для дальнейших действий существует следующий слот,
 * который реагирует на команду, в слечае команды n$ обнавление чата (при открытии чата с клиентом с id - n).
 * выгружаются последнии 40 сообщений. если команда @, идет работа с чатом и обмен сообщениями - slotReadClient.
 */

#include "serverwin.h"
#include "ui_serverwin.h"

ServerWin::ServerWin(int nPort,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWin), m_nNextBlockSize(0)
{
    ui->setupUi(this);
/************************STYLE*********************************/
/**/    new TextStyle(ui->txtStatus->document());           /**/
/**/    QPalette pal = ui->txtStatus->palette();            /**/
/**/    pal.setColor(QPalette::Base, Qt::black);            /**/
/**/    pal.setColor(QPalette::Text, Qt::green);            /**/
/**/    ui->txtStatus->setPalette(pal);                     /**/
/**************************************************************/
    ui->txtStatus->append("Server: start");
/*======Server setting begin======*/
    m_pTcpServer = new QTcpServer(this);
    if(!m_pTcpServer->listen(QHostAddress::Any,nPort)) /* See all connect in port */
    {
        ui->txtStatus->append("Server: Error start the server: "+m_pTcpServer->errorString());
        m_pTcpServer->close();
        return;
    }
    ui->txtStatus->append("Server: Sucess start the server.");
    connect(m_pTcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnect()));
    ui->txtRead->setReadOnly(true);
    ui->txtStatus->append("Server: add ReadOnly");
/*======Server setting end======*/
    if(!MYC.db.open())
    {
        ui->txtStatus->append("Server: Error connect to Database");
    }
    else
    {
        ui->txtStatus->append("Server: Connect to database sucess");
    }
/*======Element of ComboBox setting begin======*/
    ui->ListTable->setIconSize(QSize(20,20));
    ui->ListTable->addItem(QPixmap("./2.png"),"Table of user");
    ui->ListTable->addItem(QPixmap("./1.png"),"Table of contact");
    ui->ListTable->addItem(QPixmap("./3.png"),"Table of chat");
/*======Element of interface setting end======*/
}

ServerWin::~ServerWin()
{
    delete ui;
}
/*====== Make UI Begin======*/
void ServerWin::on_txtStatus_destroyed() //no Delete!
{}

void ServerWin::on_ListTable_editTextChanged(const QString &arg1) //no Delete!
{}

void ServerWin::on_ListTable_currentIndexChanged(int index)
{
    switch(index){
    case 0: { NameTable = "ux_User";  break;}
    case 1: { NameTable = "ux_friend";  break;}
    default: { NameTable = "ux_Message";  break;}
    }
}

void ServerWin::on_butRefresh_clicked() // but Refresh
{
    /*======SQL MODEL setting begin======*/
    model = new QSqlTableModel(this,MYC.db);
    model->setTable(NameTable);
    model->select();
    ui->tableView->setModel(model);
    /*======SQL MODEL setting end======*/
}

void ServerWin::on_butApply_clicked() // but Apply
{
    model->submitAll();
}

void ServerWin::on_butReset_clicked() // but Refresh
{
    model->revertAll();
}
/*====== Make UI End======*/
/*====== Make Slot Begin======*/
void ServerWin::slotNewConnect() // connect new slot
{
    QTcpSocket* pClientSocket = m_pTcpServer->nextPendingConnection();

    connect(pClientSocket, SIGNAL(readyRead()),
            this, SLOT(slotAuthClient()));
    ui->txtStatus->append("Server: New Connect.");
    sendToClient(pClientSocket, "430701911");
    sendToClient(pClientSocket, "430701912");
}

void ServerWin::slotReadClient() /* ===== Чтение запросов от подключения ===== */
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for(;;)
    {
        if(!m_nNextBlockSize)
        {
            if(pClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if(pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }

        QTime time,time2(17,4,23);
        QString str;
        QString strMessage;
        QString idIn,idOut;
        in >> idOut >> idIn >> time >> str;
        idOut = idOut.simplified();
        QString strMessage1 = "SELECT * FROM ux_Message where idIn in("+idIn+","+idOut+") and idOut in("+idIn+","+idOut+")";
        QString strMessage2 = "INSERT INTO ux_Message (idIn,idOut,mTime,Message) VALUES ( :Inid, :Outid, :mTime, :strM)";
         ui->txtRead->append("Sucess write message of " + idIn + "and" + idOut);
        if(!idIn.isEmpty() && !idOut.isEmpty())
        if (str != "#@1***430701920")
        {

            if(MYC.ModSql.prepare(strMessage2))
            {
                MYC.ModSql.bindValue(":Inid", idIn.toInt());
                MYC.ModSql.bindValue(":Outid", idOut);
                MYC.ModSql.bindValue(":mTime", time2.toString());
                MYC.ModSql.bindValue(":strM", ("\'"+str+"\'"));
            }
            else
                 ui->txtRead->append("Error SQL **Pre**");

                if(MYC.ModSql.exec())
                {
                        MessToClient(idIn,idOut,time2,str);
                }
                else
                {
                    ui->txtRead->append("Error SQL"+MYC.ModSql.lastError().text());
                }

        }
        else if (str == "#@1***430701999")
        {
            if (!MYC.ModSql.prepare("SELECT * FROM ux_User;")) {
                        qDebug() << "Unable to execute query - exiting";
                        return;
                    }
                if (!MYC.ModSql.exec()) {
                        qDebug() << "Unable to execute query - exiting";
                        return;
                    }
                      while(MYC.ModSql.next())
                      {
                           if(idIn == MYC.ModSql.value(0).toString())
                           {
                               ui->txtStatus->append(MYC.ModSql.value(0).toString() + " exit");
                               break;
                           }
                       }
                      ui->txtStatus->append("anonimus exit");
        }
        else
        {
            if(!MYC.ModSql.prepare(strMessage1)) {
               ui->txtRead->append("Error SQL"+MYC.ModSql.lastError().text());
            }
                if (!MYC.ModSql.exec()) {
                         ui->txtRead->append("Error SQL"+MYC.ModSql.lastError().text());
                    }
                    while(MYC.ModSql.next())
                          {

                                      MessToClientOfDB(idIn,
                                                   MYC.ModSql.value(0).toString(),
                                                   MYC.ModSql.value(1).toString(),
                                                   MYC.ModSql.value(2).toTime(),
                                                   MYC.ModSql.value(3).toString());
                            }
        }
        ui->txtRead->append(strMessage);
        m_nNextBlockSize = 0;
    }
}

void ServerWin::slotAuthClient() /* ===== Аунтификация ===== */
{
    QString log,pas,LogDB,PasDB;
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    QDataStream out(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for(;;)
    {
        m_nNextBlockSize = 0;
        log = "";
        pas = "";
        if(!m_nNextBlockSize)
        {
            if(pClientSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }


        QString id;
        in >> log >> pas;

        if (!MYC.ModSql.prepare("SELECT * FROM ux_User;")) {
                    qDebug() << "Unable to execute query - exiting";
                    return;
                }
            if (!MYC.ModSql.exec()) {
                    qDebug() << "Unable to execute query - exiting";
                    return;
                }
            if(log.isEmpty())
                return;

                  while(MYC.ModSql.next())
                  {
                       LogDB = MYC.ModSql.value(1).toString();
                       if(log == LogDB)
                       {
                           PasDB = MYC.ModSql.value(2).toString();
                           if(pas == PasDB)
                           {
                               ui->txtStatus->append(log+" authorized");

                               id = MYC.ModSql.value(0).toString();
                               MapIdToConnectOfClients.insert(id,pClientSocket);
                               sendToClientInfo(pClientSocket,"1912",id, log);

                               /*======Detect of accaunts and connect begin======*/
/*$$$$$$$$$$$$$$$$$$=======================data_info=========================$$$$$$$$$$$$$$$$$$$*/
                           }
                           else
                           {
                               sendToClient(pClientSocket,"430701918"); // Message of error pass
                           }
                       }
                       else
                       {
                           sendToClient(pClientSocket,"430701918"); // Message of error login
                       }
                  }
    }

}

void ServerWin::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint64(0) << str;
    out.device()->seek(0);
    out << quint64(arrBlock.size() - sizeof(quint64));
    pSocket->write(arrBlock);
}

void ServerWin::sendToClientInfo(QTcpSocket* pSocket, const QString& str, QString& id, QString& UserName)
{
    QByteArray arrBlock;
    QList<QString> id_contact;
//    QList<QString> name_contact; //don't****
//    QList<QPixmap> image_contact; //don't****
//    QMap<QString,QString> contacts; //don't****
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    sendToClient(pSocket,"1912");


            /*== Mysql serch to id friend ==*/
            if (!MYC.ModSql.prepare("SELECT * FROM ux_friend WHERE idUser1 LIKE "+id+";"))
            {

                qDebug() << "Unable to execute query - exiting";
                        return;
                    }
                if (!MYC.ModSql.exec()) {
                        qDebug() << "Unable to execute query - exiting";
                        return;
                    }

                    while(MYC.ModSql.next())
                          {
                                      sendToClient(pSocket,MYC.ModSql.value(1).toString());
                                      id_contact << MYC.ModSql.value(1).toString();
                          }

                    sendToClient(pSocket,"#@1***430701912");
            /*== Mysql serch to Name friend ==*/
            if (!MYC.ModSql.prepare("SELECT idUser, Login FROM ux_User;"))
            {
                        qDebug() << "Unable to execute query - exiting";
                        return;
                    }
                if (!MYC.ModSql.exec()) {
                        qDebug() << "Unable to execute query - exiting";
                        return;
                    }
                    while(MYC.ModSql.next())
                          {
                            foreach (QString nes, id_contact)
                            {
                                if(nes == MYC.ModSql.value(0).toString()){
//                                    name_contact << MYC.ModSql.value(1).toString();e
                                    sendToClient(pSocket,MYC.ModSql.value(1).toString());
                                }
                            }
                          }

        sendToClient(pSocket,"#@1***430701912");
        sendToClient(pSocket,UserName);
        sendToClient(pSocket,"#@1***430701912");
        sendToClient(pSocket,id);
        sendToClient(pSocket,"#@1***430701917");

        if(disconnect(pSocket, SIGNAL(readyRead()),this, SLOT(slotAuthClient())))
        {
            connect(pSocket, SIGNAL(readyRead()),this, SLOT(slotReadClient()));
        }
}
/****add*16-17-18-19-20-win****/
void ServerWin::MessToClient(const QString& idIn, const QString& idOut, QTime time, const QString& str)
{
    QTcpSocket* SocketIn;
    QTcpSocket* SocketOut;

        QByteArray mess;
        QDataStream out(&mess, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << quint16(0) << idIn << idOut << str;
        out.device()->seek(0);
        out << quint16(mess.size() - sizeof(quint16));

        if(!idIn.isEmpty() && idIn != "0" && !idIn.isNull()){
            SocketIn = MapIdToConnectOfClients.value(idIn);
            SocketIn->write(mess);
        }
        if(!idOut.isEmpty() && idOut != "0" && !idIn.isNull()){
            if(MapIdToConnectOfClients.contains(idOut)){
                SocketOut = MapIdToConnectOfClients.value(idOut);
                SocketOut->write(mess);
            }
        }


}

void ServerWin::MessToClientOfDB(const QString& idWr,const QString& idIn, const QString& idOut, QTime time, const QString& str)
{
        QTcpSocket* SocketIn;
        QByteArray mess;
        QDataStream out(&mess, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << quint16(0) << idIn << idOut << str;
        out.device()->seek(0);
        out << quint16(mess.size() - sizeof(quint16));

        if(!idWr.isEmpty() && idWr != "0" && !idWr.isNull()){
            if(MapIdToConnectOfClients.contains(idWr)){
                SocketIn = MapIdToConnectOfClients.value(idWr);
                SocketIn->write(mess);
                ui->txtRead->append("Sucess write message of " + idWr);
            }
        }

}
/*====== Make Slot End======*/
