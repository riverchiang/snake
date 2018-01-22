#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QWidget>
#include <QLCDNumber>

class onebox;

class Snake : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Snake(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *);
private:
    void makemove();
    void arrangepoint();
    void addpoint();
    void setpoint(int location);
    bool checkFirstCoverSecond();
    int checkcollide();
    QList<onebox *> boxlist;
    int direction = 0;
    int directionOrigin;
    bool color = true;
    int snakehead;
    QTimer *mytimer;
    QGraphicsScene *scene;
    QGraphicsLineItem *topline;
    QGraphicsLineItem *bottomline;
    QGraphicsLineItem *leftline;
    QGraphicsLineItem *rightline;
    onebox *box_new;
    QLCDNumber *myLCDNumber;
    int scored = 0;
private slots:
    void timertimeout();
};


#endif // SNAKE_H
