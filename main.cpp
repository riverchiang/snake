#include <QApplication>
#include <QTime>
#include "myview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myview view;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    view.show();

    return a.exec();
}
