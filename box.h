#ifndef BOX_H
#define BOX_H
#include <QGraphicsObject>
#include <QPointF>

class onebox: public QGraphicsObject
{
public:
    onebox(const QColor &color = Qt::red);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //QPainterPath shape() const;
    QPointF point;
private:
    QColor brushColor;
};

#endif // BOX_H
