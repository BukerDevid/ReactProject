#include "serverwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWin STCP(19122);/*port*/;
    STCP.show();
    return a.exec();
}
