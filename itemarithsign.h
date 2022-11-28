#ifndef ITEMARITHSIGN_H
#define ITEMARITHSIGN_H
#include<QGraphicsObject>
#include "itembaseobjects.h"

class ItemArithSign:public ItemBaseObjects
{
    Q_OBJECT
public:
    ItemArithSign(QString sign,int item_s);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    enum { Type = UserType + 1 };

    int type() const override
    {
        return Type;
    }
signals:
    void signalClicked(QString text);

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int item_size;
};

#endif // ITEMARITHSIGN_H
