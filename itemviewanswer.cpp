#include "itemviewanswer.h"

#include <QPainter>
#include <cmath>
ItemViewAnswer::ItemViewAnswer(int num1, int num2, int width, int height)
{
    Num_1=num1;
    Num_2=num2;
    item_width=width;
    item_height=height;
}

QRectF ItemViewAnswer::boundingRect() const
{
    return   QRectF(0,0,item_width,item_height);
}

void ItemViewAnswer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setColor(QColor(Qt::red));
    pen.setWidth(4);
    painter->setPen(pen);
//painter->drawRect(0,0,item_width,item_height);

    int elips=std::min(item_width,item_height)/(10.8);

    painter->setPen(Qt::NoPen);
    int p_x=0,p_y=0;
    int dl_elips=elips*0.2;

    int by_x=(item_width-(elips*Num_1+dl_elips*(Num_1-1)))/2;
    int by_y=(item_height-(elips*Num_2+dl_elips*(Num_2-1)))/2;

    for(int i=0;i<Num_2;++i)
    {
       for(int j=0;j<Num_1;++j)
       {
            QRadialGradient gradient(elips*i,elips*j, elips);
            if(i%2==0)
            {
                gradient.setColorAt(0,QColor(Qt::red).light(120));
                gradient.setColorAt(1,QColor( Qt::darkBlue).light(120));
            }
            else
            {
                gradient.setColorAt(0,QColor(Qt::darkRed).light(120));
                gradient.setColorAt(1,QColor( Qt::darkBlue).light(120));
            }
            gradient.setCenter(elips*j+p_x+elips/2+by_x, elips*i+p_y+elips/2+by_y);
            gradient.setFocalPoint(elips*j+p_x+elips/2+by_x, elips*i+p_y+elips/2+by_y);

            QBrush brush( gradient);
            painter->setBrush(brush);

            painter->drawEllipse(elips*j+p_x+by_x,elips*i+p_y+by_y,elips,elips);
            p_x+=dl_elips;
       }
        p_y+=dl_elips;
        p_x=0;
    }
}
