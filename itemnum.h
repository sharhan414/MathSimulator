#ifndef ITEMNUM_H
#define ITEMNUM_H

#include<QGraphicsObject>
#include "itembaseobjects.h"
class ItemNum:public ItemBaseObjects
{
public:
    ItemNum(QString sign,int it_w,int it_h);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // ITEMNUM_H
