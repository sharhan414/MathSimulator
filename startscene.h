#ifndef STARTSCENE_H
#define STARTSCENE_H
#include <QGraphicsView>
#include <vector>
#include <QLabel>
#include "simulator.h"
#include "alldates.h"

class ItemNum;
class ItemArithSign;
class QPushButton;
class QGraphicsTextItem;

class StartScene: public QGraphicsView
{
    Q_OBJECT
public:
    StartScene(QWidget *parent = nullptr);

private slots:
    void slotClickedValuesQ(QString text);
signals:
    void signalDates(vector<AllDates> d);

protected:
  void drawBackground(QPainter *painter, const QRectF &rect) override;
  void resizeEvent(QResizeEvent *event) override;

private:
    std::vector<ItemNum*> item_nums;
    std::vector<ItemArithSign*> item_values_question;
    std::vector<ItemArithSign*> item_arifs;

    QGraphicsTextItem*for_arifs_text;
    QGraphicsTextItem*for_nums_text;
    QGraphicsTextItem*for_questions_text;

    QPushButton *ButtStartTest;

    QLabel* MainLabel;

    void setGeometryNumItems();
    void setGeometryValuesQuestItem();
    void setGeometryArifItems();

public slots:
    void slotClickedStartTest();

};

#endif // STARTSCENE_H
