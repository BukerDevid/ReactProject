#ifndef WINAUTH_H
#define WINAUTH_H

#include <QWidget>
#include <QBrush>
#include <QPalette>
#include "netip.h"
class netip;
namespace Ui {
class WinAuth;
}

class WinAuth : public QWidget
{
    Q_OBJECT

public:
    explicit WinAuth(QWidget *parent = 0);
    ~WinAuth();

    QString LogAuth();
    QString PasAuth();
    netip *NP;
    QWidget* getSW();

signals:
    void clicked();
public slots:
    void on_butLogin_clicked();
private:
    Ui::WinAuth *ui;
};

#endif // WINAUTH_H
