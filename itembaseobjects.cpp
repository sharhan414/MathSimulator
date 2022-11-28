#include "itembaseobjects.h"
#include <QDebug>
ItemBaseObjects::ItemBaseObjects(QString sign, int item_w, int item_h)
{
    check_back_color=Qt::darkRed;
    not_check_back_color=Qt::white;

    check_text_color=Qt::white;
    not_check_text_color=Qt::darkRed;

    for_hover_move_color=Qt::yellow;

    item_width=item_w;
    item_height=item_h;

    is_check=false;
    item_sign=sign;

    setAcceptHoverEvents(true);
    addColorsItems();
    item_font.setPixelSize(int(item_height*0.6));
}

QRectF ItemBaseObjects::boundingRect() const
{
    return  QRectF(0,0,item_width,item_height);
}

void ItemBaseObjects::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

bool ItemBaseObjects::is_checks()
{
    return is_check;
}

QString ItemBaseObjects::getItemSign()
{
    return item_sign;
}

int ItemBaseObjects::getWidthItem()
{
    return item_width;
}

int ItemBaseObjects::getHeightItem()
{
    return item_height;
}

void ItemBaseObjects::setCheck(bool check)
{
    is_check=check;
    addColorsItems();
}

void ItemBaseObjects::setForBackColors(QColor color1,QColor color2)
{
   check_back_color=color1;
   not_check_back_color=color2;
    update();
}

void ItemBaseObjects::setForTextColors(QColor color1,QColor color2)
{
    check_text_color=color1;
    not_check_text_color=color2;
    update();
}

void ItemBaseObjects::setForHoverMove(QColor color)
{
    for_hover_move_color=color;
    update();
}

void ItemBaseObjects::setFont(QFont font)
{
    item_font=font;
}

void ItemBaseObjects::setSize(int w, int h)
{
    item_width=w;
    item_height=h;
    update();
}

void ItemBaseObjects::addColorsItems()
{
    if(is_check)
    {
        back_color=check_back_color;
        text_color=check_text_color;
    }
    else
    {
        back_color=not_check_back_color;
        text_color=not_check_text_color;
    }
    update();
}
