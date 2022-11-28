#include "itemarithsign.h"
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>
#include <QGraphicsTextItem>
ItemArithSign::ItemArithSign(QString sign,int item_s):ItemBaseObjects(sign,item_s,item_s)
{
     item_size=item_s;
     item_font.setPixelSize(item_size*0.5);
}

QRectF ItemArithSign::boundingRect() const
{
    return   QRectF(0,0,item_size,item_size);
}

void ItemArithSign::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(Qt::NoPen);
    painter->setBrush(back_color);
    painter->drawEllipse(0,0,item_size,item_size);

    painter->setFont(item_font);
    QFontMetrics mtr(item_font);

    QPen pen;
    pen.setColor(text_color);
    painter->setPen(pen);

    painter->drawText(QRectF((item_size-mtr.width(item_sign))/2,(item_size-mtr.height())/2,mtr.width(item_sign),mtr.height()),item_sign);
}

void ItemArithSign::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    back_color=Qt::yellow;
    update();
}

void ItemArithSign::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    addColorsItems();
}

void ItemArithSign::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalClicked(item_sign);

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
