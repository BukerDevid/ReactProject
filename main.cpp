#include <QApplication>
#include "netip.h"
#include "winauth.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    netip connect_ip("178.208.246.114",19122);
    return a.exec();
}
