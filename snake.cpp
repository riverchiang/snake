#include "snake.h"
#include "box.h"
#include <QKeyEvent>
#include <QTimer>

Snake::Snake(QWidget *parent) : QGraphicsView(parent)
{
    setMinimumSize(460, 480);
    setMaximumSize(460, 480);
    snakeScene = new QGraphicsScene;
    snakeScene->setSceneRect(0, 0, 400, 400);
    setScene(snakeScene);

    scoreLCDNumber = new QLCDNumber;
    scoreLCDNumber->setPalette(Qt::black);
    scoreLCDNumber->setDigitCount(6);
    scoreLCDNumber->display(scored);
    scoreLCDNumber->setGeometry(0,410,80,30);
    snakeScene->addWidget(scoreLCDNumber);

    topLine = snakeScene->addLine(0, 0, 400, 0);
    bottomLine = snakeScene->addLine(0, 400, 400, 400);
    rightLine = snakeScene->addLine(400, 0, 400, 400);
    leftLine = snakeScene->addLine(0, 0, 0, 400);

    onebox *box1 = new onebox(Qt::black);
    snakeScene->addItem(box1);
    box1->point.setX(20);
    box1->point.setY(20);
    box1->setPos(box1->point);

    boxlist << box1;
    snakeHead = 0;

    oneSecondTimer = new QTimer(this);
    oneSecondTimer->setInterval(1000);
    if(!oneSecondTimer->isActive())
        oneSecondTimer->start();
    connect(oneSecondTimer, SIGNAL(timeout()), this, SLOT(moveOneRound()));

    addPoint();
 }

struct location {
    int x;
    int y;
};

void getLocation(struct location *location_tmp)
{
    int x = qrand() % 18;
    int y = qrand() % 18;

    location_tmp->x = (x + 1) * 20;
    location_tmp->y = (y + 1) * 20;
}

void Snake::addPoint()
{
    struct location tmp;
    onebox *box_tmp;
    bool new_location;

    scored++;
    scoreLCDNumber->display(scored);

    while (1) {
        getLocation(&tmp);
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
        newBox = new onebox(Qt::white);
        color = false;
    }
    else
    {
        newBox = new onebox(Qt::black);
        color = true;
    }

    snakeScene->addItem(newBox);
    newBox->point.setX(tmp.x);
    newBox->point.setY(tmp.y);
    newBox->setPos(newBox->point);
}

void Snake::resetNodePosition()
{
    onebox *tempbox;
    foreach (tempbox, boxlist) {
        tempbox->setPos(tempbox->point);
    }
}

void Snake::moveOneStep()
{
    QPointF nextpoint, temppoint;
    nextpoint = boxlist[snakeHead]->point;

    for(int i = (snakeHead - 1) ; i > -1; i--) {
        temppoint = boxlist[i]->point;
        boxlist[i]->point = nextpoint;
        nextpoint = temppoint;
    }

}

int Snake::checkCollideCondtion()
{
    if ((boxlist[snakeHead]->point.x() == newBox->point.x()) && (boxlist[snakeHead]->point.y() == newBox->point.y()))
    {
        return hitNewNode;
    }

    if ((boxlist[snakeHead]->point.x() > 399) || (boxlist[snakeHead]->point.x() < 1) || (boxlist[snakeHead]->point.y() > 399) || (boxlist[snakeHead]->point.y() < 1))
    {
        return hitBound;
    }

    bool iscollide = false;
    for (int i = 0; i < (boxlist.count() - 1); i++) {
        if ((boxlist[snakeHead]->point.x() == boxlist[i]->point.x()) && (boxlist[snakeHead]->point.y() == boxlist[i]->point.y()))
            iscollide = true;
    }
    if (iscollide)
    {
        return hitSelf;
    }
    return hitNone;
}

void Snake::setSnakeHead()
{
    if (direction == right)
    {
        boxlist[snakeHead]->point.setX(boxlist[snakeHead]->point.x() + 20);
    } else if (direction == left)
    {
        boxlist[snakeHead]->point.setX(boxlist[snakeHead]->point.x() - 20);
    } else if (direction == up)
    {
        boxlist[snakeHead]->point.setY(boxlist[snakeHead]->point.y() - 20);
    } else if (direction == down)
    {
        boxlist[snakeHead]->point.setY(boxlist[snakeHead]->point.y() + 20);
    }

}

void Snake::moveOneRound()
{
    int collide_condition;
    moveOneStep();
    setSnakeHead();

    collide_condition = checkCollideCondtion();
    if (collide_condition == hitNewNode)
    {
        snakeHead++;
        boxlist << newBox;
        setSnakeHead();
        resetNodePosition();
        addPoint();
    }
    else if (collide_condition == hitBound || collide_condition == hitSelf)
    {
        oneSecondTimer->stop();
    }
    else if (collide_condition == hitNone)
    {
        resetNodePosition();
    }

}


bool Snake::checkFirstCoverSecond()
{
    if (snakeHead == 0)
        return false;
    QPointF tempPoint;
    tempPoint = boxlist[snakeHead]->point;

    if (direction == right)
    {
        tempPoint.setX(tempPoint.x() + 20);
    } else if (direction == left)
    {
        tempPoint.setX(tempPoint.x() - 20);
    } else if (direction == up)
    {
        tempPoint.setY(tempPoint.y() - 20);
    } else if (direction == down)
    {
        tempPoint.setY(tempPoint.y() + 20);
    }

    if ((tempPoint.x() == boxlist[snakeHead - 1]->point.x()) && (tempPoint.y() == boxlist[snakeHead - 1]->point.y()))
        return true;
    return false;
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        directionOrigin = direction;
        direction = left;
    }else if (event->key() == Qt::Key_Up)
    {
        directionOrigin = direction;
        direction = up;
    } else if (event->key() == Qt::Key_Right)
    {
        directionOrigin = direction;
        direction = right;
    } else if (event->key() == Qt::Key_Down)
    {
        directionOrigin = direction;
        direction = down;
    }

    if (checkFirstCoverSecond())
    {
        direction = directionOrigin;
        return;
    }

    emit moveOneRound();
}
