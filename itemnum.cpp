#include "itemnum.h"
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
ItemNum::ItemNum(QString sign, int it_w, int it_h):ItemBaseObjects(sign,it_w,it_h)
{
    item_font.setPixelSize(item_height*0.7);
}

QRectF ItemNum::boundingRect() const
{
    return  QRectF(0,0,item_width,item_height);
}

void ItemNum::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;

    painter->setBrush(back_color);
    painter->drawRect(0,0,item_width,item_height);

    painter->setFont(item_font);
    QFontMetrics mtr(item_font);

    pen.setColor(text_color);
    painter->setPen(pen);

    painter->drawText((item_width-mtr.width(item_sign))/2,item_font.pixelSize()+2,item_sign);
}

void ItemNum::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    back_color=for_hover_move_color;
    update();
}

void ItemNum::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    addColorsItems();
}

void ItemNum::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_check)
    {
        is_check=false;
    }
    else
    {
        is_check=true;
    }
    addColorsItems();
}

