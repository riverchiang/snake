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
    QPointF point;
    QPainterPath shape() const;

private:
    QColor brushColor;
};

#endif // BOX_H
