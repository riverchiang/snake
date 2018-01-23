#include <QApplication>
#include <QTime>
#include "snake.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Snake snake;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    snake.show();

    return a.exec();
}
