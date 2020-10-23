#include "TbatteryCupboard.h"
#include <QApplication>
#define myPrintInfo qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
int main(int argc, char *argv[])
{
    myPrintInfo<<"program is running";
    QApplication a(argc, argv);
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    TbatteryCupboard w;
    w.show();

    return a.exec();
}
