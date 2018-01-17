#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QWidget>

class onebox;

class myview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myview(QWidget *parent = 0); 
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
private slots:
    void timertimeout();
};

#endif // MYVIEW_H
