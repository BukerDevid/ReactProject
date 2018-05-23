#include "winauth.h"
#include "ui_winauth.h"


WinAuth::WinAuth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinAuth)
{
   ui->setupUi(this);
   QPalette pal;
//    pal.setBrush(ui->graphicsView->backgroundRole(),QBrush(QPixmap("/home/blackrouse/Documents/Files_cod/Fonreg.jpg")));
   pal.setColor(ui->graphicsView->backgroundRole(),QColor("#3d3d3d"));
   ui->graphicsView->setPalette(pal);
//    ui->graphicsView->resize(400,400);
   ui->graphicsView->setAutoFillBackground(true);
   ui->lblNameProg->setText("<p><center>Test<font color=#44DAFF>Mes</font></center></p>");
   ui->lblLogin->setText("<p><font color=#FFFFFF>Login</font></p>");
   ui->lblPass->setText("<p><font color=#FFFFFF>Pass</font></p>");
   QPalette pal2;
   pal2.setColor(ui->lineLog->backgroundRole(),QColor("#6d6d6d"));
   pal2.setColor(QPalette::Text,QColor("#ffffff"));
   ui->lineLog->setPalette(pal2);
   pal2.setColor(ui->linePas->backgroundRole(),QColor("#6d6d6d"));
   ui->linePas->setPalette(pal2);
   pal2.setColor(ui->butLogin->backgroundRole(),QColor("#6d6d6d"));
   pal2.setColor(QPalette::Text,QColor("#ffffff"));
   ui->butLogin->setPalette(pal2);
   pal2.setColor(ui->butRegister->backgroundRole(),QColor("#3d3d3d"));
   pal2.setColor(QPalette::Text,QColor("#000000"));
   ui->butRegister->setPalette(pal2);

}

WinAuth::~WinAuth()
{
    delete ui;
}

QString WinAuth::LogAuth()
{
    QString Log = ui->lineLog->text();
    return Log;
}

QString WinAuth::PasAuth()
{
    QString Pas = ui->linePas->text();
    return Pas;
}

void WinAuth::on_butLogin_clicked()
{

}

QWidget* WinAuth::getSW(){
    return ui->butLogin;
}
