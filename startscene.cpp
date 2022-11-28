#include "startscene.h"
#include "itemarithsign.h"
#include "itemnum.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QDebug>
#include <vector>
StartScene::StartScene(QWidget *parent): QGraphicsView(parent)
{
    setScene(new QGraphicsScene);
    scene()->setSceneRect(0,0,width()-2,height()-2);

    setRenderHint(QPainter::Antialiasing);
    scene()->setItemIndexMethod(QGraphicsScene::NoIndex);
    for_arifs_text=new QGraphicsTextItem("Арифметическое действие");
    scene()->addItem(for_arifs_text);
    for_arifs_text->setHtml(
    "<font size=\"4\" color=\"white\" face=\"Arial\"><b>Арифметическое действие</b></font>");

    ItemArithSign* item_sign=new ItemArithSign("×",50);
    scene()->addItem(item_sign);
    QFont f;
    f.setPixelSize(item_sign->getHeightItem()*0.6);
    item_sign->setFont(f);

    ItemArithSign* item_sign_del=new ItemArithSign("÷",50);
    scene()->addItem(item_sign_del);
    item_sign_del->setFont(f);

    item_arifs.push_back(item_sign);
    item_arifs.push_back(item_sign_del);

    for_nums_text=new QGraphicsTextItem("Множитель");
    scene()->addItem(for_nums_text);
    for_nums_text->setHtml(
    "<font size=\"4\" color=\"white\" face=\"Arial\"><b>Множитель</b></font>"
    );

    int num_item_w=40,num_item_h=30;
    for (int i=2;i<10;++i)
    {
        ItemNum* num_item=new ItemNum(QString::number(i),num_item_w,num_item_h);

        scene()->addItem(num_item);
        item_nums.push_back(num_item);
    }

    for_questions_text=new QGraphicsTextItem("Количество вопросов в тесте");
    scene()->addItem(for_questions_text);
    for_questions_text->setHtml(
    "<font size=\"4\" color=\"white\" face=\"Arial\"><b>Количество вопросов в тесте</b></font>"
    );

auto set_geometry=[&](QString sign,int by_x,int by_y){

    ItemArithSign* values_question=new ItemArithSign(sign,50);

    values_question->setPos(by_x,by_y);
    scene()->addItem(values_question);
    item_values_question.push_back(values_question);
    connect(values_question,SIGNAL(signalClicked(QString)),this,SLOT(slotClickedValuesQ(QString)));
};

    set_geometry("5",40,250);
    set_geometry("10",100,250);
    set_geometry("15",160,250);
    set_geometry("20",220,250);
    item_values_question[0]->setCheck(true);
    QString  StyleButtStartTest=" "
    "QPushButton  {"
    "background-color: rgb(210, 210, 210);"
    "border: 2px outset rgb(200,200, 200);"
    "border-radius: %1px;"
    "font: "+QString::number((height()*0.1)*0.5)+"px;"
    "color: rgb(10, 10, 10);"
    "font: bold;"
    "width:"+QString::number(width()*0.3)+"px;"
    "height:" +QString::number(height()*0.1)+"px;"
    "}"

#ifndef Q_OS_ANDROID//Для Андрода отключаем "hover" т.к. мешает
    "QPushButton:hover {"
    "background-color: rgb(240, 240, 240);"
    //"color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(42, 226, 30, 255), stop:1 rgba(40, 148, 40, 255));"
    "}"
#endif
                                                     "   }"
    "QPushButton:pressed  {"
    "background-color: rgb(200,200, 200);"
    "border-style: inset;"
    //"color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(255, 223, 40, 255), stop:1 rgba(167, 122, 30, 255))"
    "}";

    ButtStartTest=new QPushButton("Начать тест",this);
    ButtStartTest->setGeometry(width()*0.3,height()*0.1,width()*0.35,height()*0.9);
    connect(ButtStartTest,SIGNAL(clicked()),this,SLOT(slotClickedStartTest()));
    ButtStartTest->setStyleSheet(StyleButtStartTest.arg(width()*0.01));
    setGeometryArifItems();
    setGeometryNumItems();
    setGeometryValuesQuestItem();

    MainLabel=new QLabel(this);
    QString l_text="<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"7\"> <strong><center>Тренажёр</strong></center></font>"
               "<strong><font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"6\"><center>таблицы умножения</center>"
               "<center>и деления</center></font></strong>";
    MainLabel->setText(l_text);
}

void StartScene::slotClickedValuesQ(QString text)
{
    auto it_sig=(ItemArithSign*)sender();

    for(int i=0;i<item_values_question.size();++i)
    {
        if(item_values_question[i]->is_checks() &&  item_values_question[i]!=it_sig)
        {
            item_values_question[i]->setCheck(false);
        }
    }
}

void StartScene::resizeEvent(QResizeEvent *event)
{
    scene()->setSceneRect(this->viewport()->rect());

    setGeometryArifItems();
    setGeometryNumItems();
    setGeometryValuesQuestItem();

    ButtStartTest->setGeometry(width()*0.35,height()*0.9,width()*0.3,height()*0.07);
    MainLabel->setGeometry(0,height()*0.01,width(),height()*0.2);
}
void StartScene::setGeometryArifItems()
{

    QFontMetrics mtr(for_arifs_text->font());
    int text_x=(width()-for_arifs_text->boundingRect().width())/2;

    for_arifs_text->setPos(text_x,height()*0.24);

    int arifs_item_s=50;
    int arif_rast=0;
    int by_x=(width()-item_arifs.size()*arifs_item_s-arifs_item_s*0.2*(item_arifs.size()-1))/2;
    for(int i=0;i<item_arifs.size();++i)
    {
        item_arifs[i]->setPos(by_x+i*arifs_item_s+arif_rast,height()*0.3);
        arif_rast+=arifs_item_s*0.2;
    }
}
void StartScene::setGeometryNumItems()
{
    QFontMetrics mtr(for_nums_text->font());
    int text_x=(width()-for_nums_text->boundingRect().width())/2;

    for_nums_text->setPos(text_x,height()*0.44);
    int item_w=40,num_item_h=30;
    int nums_by_x=(width()-item_w*item_nums.size())/2;

    for (int i=0;i<item_nums.size();++i)
    {
        item_nums[i]->setPos(i*item_w+nums_by_x,height()*0.5);
    }
}

void StartScene::setGeometryValuesQuestItem()
{
    QFontMetrics mtr(for_questions_text->font());
     //  int text_x=(width()-mtr.width(for_questions_text->toPlainText()))/2;
    int text_x=(width()-for_questions_text->boundingRect().width())/2;
    for_questions_text->boundingRect().width();
    for_questions_text->setPos(text_x,height()*0.64);

    int q_item_s=50;
    int question_by_x=(width()-item_values_question.size()*q_item_s-q_item_s*0.2*(item_values_question.size()-1))/2;
    int rest_q_items=0;

    for (int i=0;i<item_values_question.size();++i)
    {
        item_values_question[i]->setPos(i*q_item_s+question_by_x+rest_q_items,height()*0.7);
        rest_q_items+=q_item_s*0.2;
    }
}
void StartScene::slotClickedStartTest()
{
    std::vector<char> arifs;
    for(auto it:item_arifs)
    {
        if(it->is_checks())
        {
            if(it->getItemSign()=="×")
            {
                arifs.push_back('*') ;
            }
            else if(it->getItemSign()=="÷")
            {
                arifs.push_back('/') ;
            }
        }
    }

    std::vector<int> nums;
    for(auto it:item_nums)
    {
        if(it->is_checks())
        {
            nums.push_back(it->getItemSign().toInt());
        }
     }

    int values=0;
    for(auto it:item_values_question)
    {

        if(it->is_checks())
        {
            values=it->getItemSign().toInt();
        }
    }
    if(arifs.empty())
    {
        arifs.push_back('*');
        arifs.push_back('/');
    }

    if(nums.empty())
    {
        for (int i=2;i<10;++i)
        {
            nums.push_back(i);
        }
    }
    if(values==0)
    {
        return;
    }
    Simulator sim(arifs,nums,values);
    emit signalDates(sim.getData());
}
void StartScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawImage(QRect(0,0,width(),height()),QImage(":/images/back_round_image.jpeg"));

    QImage imn_cosm(":/images/new_cosmonavt.png");
    int im_w=width()/4;
    double sootn=double(imn_cosm.height())/imn_cosm.width();
    painter->drawImage(QRect(width()-im_w,height()-im_w*sootn,im_w,im_w*sootn),imn_cosm);

}
