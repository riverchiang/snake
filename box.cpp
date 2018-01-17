#include "box.h"
#include <QPainter>

onebox::onebox(const QColor &color) :  brushColor(color)
{

}


QRectF onebox::boundingRect() const {
    qreal pen_width = 1;
    return QRectF(-10-pen_width/2, -10-pen_width/2, 20+pen_width, 20+pen_width);
}


void onebox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){


    //painter->drawPixmap(-10, -10, 20, 20, QPixmap(":/images/box.gif"));
    painter->setBrush(brushColor);
    QColor penColor = brushColor;
    penColor.setAlpha(20);
    painter->setPen(Qt::black/*penColor*/);
    painter->drawRect(-10, -10, 20, 20);
}

/*
QPainterPath onebox::shape() const{

    QPainterPath path;
    path.addRect(-9.5, -9.5, 19, 19);
    return path;
}
*/
