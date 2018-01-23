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
    void resetNodePosition();       // set graphicsitem position based on boxlist
    void moveOneStep();             // move node to its anicent node except head
    void addPoint();                // create a new point, old one has been eaten
    void setSnakeHead();            // set head position by pre-direction or keyboard
    bool checkFirstCoverSecond();   // if head set postion to its pre-position
    int checkCollideCondtion();     // check node collide condition
    enum collideCondition {hitNewNode, hitBound, hitSelf, hitNone};
    QList<onebox *> boxlist;        // record all node's postion
    int direction = right;          // head node's next move target
    enum boxDirection {right, left, up, down};
    int directionOrigin;            // record the keyborad direction
    bool color = true;              // record the color of snake
    int snakeHead;
    int scored = 0;
    QTimer *oneSecondTimer;
    QGraphicsScene *snakeScene;
    QGraphicsLineItem *topLine;
    QGraphicsLineItem *bottomLine;
    QGraphicsLineItem *leftLine;
    QGraphicsLineItem *rightLine;
    onebox *newBox;
    QLCDNumber *scoreLCDNumber;


private slots:
    void moveOneRound();
};


#endif // SNAKE_H
