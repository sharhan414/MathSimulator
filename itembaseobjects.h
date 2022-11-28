#ifndef ITEMBASEOBJECTS_H
#define ITEMBASEOBJECTS_H

#include <QGraphicsObject>
#include <QFont>
class ItemBaseObjects:public QGraphicsObject
{
    Q_OBJECT
public:
    ItemBaseObjects(QString sign,int item_w,int item_h);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool is_checks();
    QString getItemSign();
    int getWidthItem();
    int getHeightItem();

    void setCheck(bool check);

    void setForBackColors(QColor color1,QColor color2);
    void setForTextColors(QColor color1,QColor color2);
    void setForHoverMove(QColor color);
    void setFont(QFont font);
    void setSize(int w,int h);
protected:
    bool is_check;
    int item_width,item_height;
    QString item_sign;
    QColor back_color;
    QColor text_color;
    QColor check_back_color,not_check_back_color;
    QColor check_text_color,not_check_text_color;
    QColor for_hover_move_color;
    QFont item_font;

    void addColorsItems();

};

#endif // ITEMBASEOBJECTS_H
