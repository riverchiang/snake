#include "myview.h"
#include "box.h"
#include <QKeyEvent>
#include <QTimer>

myview::myview(QWidget *parent) : QGraphicsView(parent)
{
    setMinimumSize(410, 410);
    setMaximumSize(410, 410);
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 400, 400);
    setScene(scene);

    topline = scene->addLine(0, 0, 400, 0);
    bottomline = scene->addLine(0, 400, 400, 400);
    rightline = scene->addLine(400, 0, 400, 400);
    leftline = scene->addLine(0, 0, 0, 400);

    onebox *box1 = new onebox(Qt::black);
    scene->addItem(box1);
    box1->point.setX(20);
    box1->point.setY(20);
    box1->setPos(box1->point);

    boxlist << box1;
    snakehead = 0;

    //qDebug("test1");
    //qDebug(str.toLatin1());


    mytimer = new QTimer(this);
    mytimer->setInterval(1000);
    if(!mytimer->isActive())
        mytimer->start();
    connect(mytimer, SIGNAL(timeout()), this, SLOT(timertimeout()));

    addpoint();
 }

struct location {
    int x;
    int y;
};

void getlocation(struct location *location_tmp)
{
    int x = qrand() % 18;
    int y = qrand() % 18;

    location_tmp->x = (x + 1) * 20;
    location_tmp->y = (y + 1) * 20;
}

void myview::addpoint()
{
    struct location tmp;
    onebox *box_tmp;
    bool new_location;

    while (1) {
        getlocation(&tmp);
        new_location = true;
        foreach (box_tmp, boxlist) {
            if ((box_tmp->point.x() == tmp.x)  && (box_tmp->point.y() == tmp.y))
                new_location = false;
        }
        if (new_location == true)
            break;
    }

    if (color == true)
    {
        box_new = new onebox(Qt::white);
        color = false;
    }
    else
    {
        box_new = new onebox(Qt::black);
        color = true;
    }

    scene->addItem(box_new);
    box_new->point.setX(tmp.x);
    box_new->point.setY(tmp.y);
    box_new->setPos(box_new->point);
}

void myview::makemove()
{
    onebox *tempbox;
    foreach (tempbox, boxlist) {
        tempbox->setPos(tempbox->point);
    }
}

void myview::arrangepoint()
{
    QPointF nextpoint, temppoint;
    nextpoint = boxlist[snakehead]->point;

    for(int i = (snakehead - 1) ; i > -1; i--) {
        temppoint = boxlist[i]->point;
        boxlist[i]->point = nextpoint;
        nextpoint = temppoint;
    }

}

int myview::checkcollide()
{
    if ((boxlist[snakehead]->point.x() == box_new->point.x()) && (boxlist[snakehead]->point.y() == box_new->point.y()))
    {
        return 0;
    }

    if ((boxlist[snakehead]->point.x() > 399) || (boxlist[snakehead]->point.x() < 1) || (boxlist[snakehead]->point.y() > 399) || (boxlist[snakehead]->point.y() < 1))
    {
        return 1;
    }

    bool iscollide = false;
    for (int i = 0; i < (boxlist.count() - 1); i++) {
        if ((boxlist[snakehead]->point.x() == boxlist[i]->point.x()) && (boxlist[snakehead]->point.y() == boxlist[i]->point.y()))
            iscollide = true;
    }
    if (iscollide)
    {
        return 2;
    }
    return 3;
}

void myview::setpoint(int location)
{
    if (direction == 0)
    {
        boxlist[location]->point.setX(boxlist[location]->point.x() + 20);
    } else if (direction == 1)
    {
        boxlist[location]->point.setX(boxlist[location]->point.x() - 20);
    } else if (direction == 2)
    {
        boxlist[location]->point.setY(boxlist[location]->point.y() - 20);
    } else if (direction == 3)
    {
        boxlist[location]->point.setY(boxlist[location]->point.y() + 20);
    }

}

void myview::timertimeout()
{
    int collide_condition;
    arrangepoint();
    setpoint(snakehead);

    collide_condition = checkcollide();
    if (collide_condition == 0)
    {
        snakehead++;
        boxlist << box_new;
        setpoint(snakehead);
        makemove();
        addpoint();
    }
    else if (collide_condition == 1 || checkcollide() == 2)
    {
        mytimer->stop();
    }
    else if (collide_condition == 3)
    {
        makemove();
    }

}


bool myview::checkFirstCoverSecond()
{
    if (snakehead == 0)
        return false;
    QPointF tempPoint;
    tempPoint = boxlist[snakehead]->point;

    if (direction == 0)
    {
        tempPoint.setX(tempPoint.x() + 20);
    } else if (direction == 1)
    {
        tempPoint.setX(tempPoint.x() - 20);
    } else if (direction == 2)
    {
        tempPoint.setY(tempPoint.y() - 20);
    } else if (direction == 3)
    {
        tempPoint.setY(tempPoint.y() + 20);
    }

    if ((tempPoint.x() == boxlist[snakehead - 1]->point.x()) && (tempPoint.y() == boxlist[snakehead - 1]->point.y()))
        return true;
    return false;
}

void myview::keyPressEvent(QKeyEvent *event)
{
    int collide_condition;


    if (event->key() == Qt::Key_Left)
    {
        directionOrigin = direction;
        direction = 1;
    }else if (event->key() == Qt::Key_Up)
    {
        directionOrigin = direction;
        direction = 2;
    } else if (event->key() == Qt::Key_Right)
    {
        directionOrigin = direction;
        direction = 0;
    } else if (event->key() == Qt::Key_Down)
    {
        directionOrigin = direction;
        direction = 3;
    }

    if (checkFirstCoverSecond())
    {
        direction = directionOrigin;
        return;
    }

    arrangepoint();
    setpoint(snakehead);

    collide_condition = checkcollide();

    if (collide_condition == 0)
    {
        snakehead++;
        boxlist << box_new;
        setpoint(snakehead);
        makemove();
        addpoint();
    }
    else if (collide_condition == 1 || checkcollide() == 2)
    {
        mytimer->stop();
    }
    else if (collide_condition == 3)
    {
        makemove();
    }

}

