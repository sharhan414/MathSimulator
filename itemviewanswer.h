#ifndef ITEMVIEWANSWER_H
#define ITEMVIEWANSWER_H
#include <QGraphicsItem>

class ItemViewAnswer:public QGraphicsItem
{
public:
    ItemViewAnswer(int num1,int num2,int width,int height);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int Num_1,Num_2,item_width,item_height;
};
#endif // ITEMVIEWANSWER_H
