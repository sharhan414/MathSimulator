#include "scene.h"
#include <QGraphicsScene>
#include "itemviewanswer.h"
#include <QWheelEvent>
#include <cmath>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QDebug>
#include "itemarithsign.h"
#include <QMessageBox>
#include <QPropertyAnimation>

Scene::Scene(QWidget *parent) : QGraphicsView(parent)
{

    MainLabel=new QLabel(this);
    QString l_text="<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"7\"> <strong><center>Тренажёр</strong></center></font>"
                "<strong><font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"6\"><center>таблицы умножения</center>"
                "<center>и деления</center></font></strong>";
    MainLabel->setText(l_text);

    QuestNumber=0;
    ActionText="%1%2%3=%4";
    TextPassed="Вопрос %1 из %2";
    butt_size=50;
    HelpLabel=new QLabel(this);
    CloseSceneHelps();

    resize(350,600);
    setScene(new QGraphicsScene);
    scene()->setSceneRect(this->viewport()->rect());

    setRenderHint(QPainter::Antialiasing);
    scene()->setItemIndexMethod(QGraphicsScene::NoIndex);


    ShetStaly=" "
    "QPushButton  {"
    "background-color: rgb(200, 200, 200);"
    "border: 2px outset rgb(190,195, 170);"
    "border-radius: %1px;"
    "font: "+QString::number(butt_size*0.7)+"px;"
    "color: rgb(220, 60, 190);"
    "font: bold;"
    "width:"+QString::number(butt_size)+"px;"
    "height:" +QString::number(butt_size)+"px;"
      "}"

  #ifndef Q_OS_ANDROID//Для Андрода отключаем "hover" т.к. мешает
  "QPushButton:hover {"
  "background-color: rgb(11, 37, 98);"
  "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(42, 226, 30, 255), stop:1 rgba(40, 148, 40, 255));"
   "}"
  #endif                                                         "   }"
  "QPushButton:pressed  {"
  "background-color: rgb(220,250, 50);"
  "border-style: inset;"
  "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(255, 223, 40, 255), stop:1 rgba(167, 122, 30, 255))"
  "}";


    but_1=new QPushButton("1",this);
    but_2=new QPushButton("2",this);
    but_3=new QPushButton("3",this);

    but_4=new QPushButton("4",this);
    but_5=new QPushButton("5",this);
    but_6=new QPushButton("6",this);

    but_7=new QPushButton("7",this);
    but_8=new QPushButton("8",this);
    but_9=new QPushButton("9",this);

    but_0=new QPushButton("0",this);
    but_delete=new QPushButton("<",this);


    float by_h=0.76;
    int rast=(width()*0.2);

    but_0->setGeometry(width()*0.5-butt_size/2,height()*by_h,butt_size,butt_size);
    but_delete->setGeometry(width()*0.7-butt_size/2,height()*by_h,butt_size,butt_size);


    connect(but_1,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_2,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_3,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_4,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_5,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_6,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_7,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_8,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_9,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));
    connect(but_0,SIGNAL(clicked()),this,SLOT(slotButtonsClicked()));

    connect(but_delete,SIGNAL(clicked()),this,SLOT(slotClickedDeleteButton()));


    but_1->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_2->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_3->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_4->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_5->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_6->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_7->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_8->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_9->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_0->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_delete->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));

    but_nex=new QPushButton("Далее",this);
    int nb_w=width()*0.35,nb_h=height()*0.06;
    but_nex->setGeometry((width()-nb_w)/2,height()*0.95-nb_h,nb_w,nb_h);
    connect(but_nex,SIGNAL(clicked()),this,SLOT(slotButtonsNextClicked()));

    animationGroup = new QSequentialAnimationGroup(this);
    AnimationReadError();

    QString  StalyNextButt=" "
    "QPushButton  {"
    "background-color: rgb(157, 14, 124);"
    "border: 2px outset rgb(190,195, 170);"
    "border-radius: %1px;"
    "font: "+QString::number(nb_h*0.4)+"px;"
    "color: rgb(240, 240, 240);"
    "font: bold;"
    "width:"+QString::number(butt_size)+"px;"
    "height:" +QString::number(butt_size)+"px;"
       "}"

    #ifndef Q_OS_ANDROID//Для Андрода отключаем "hover" т.к. мешает
    "QPushButton:hover {"
    "background-color: rgb(11, 37, 98);"
    "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(42, 226, 30, 255), stop:1 rgba(40, 148, 40, 255));"
    "}"
    #endif
                                                        "   }"
    "QPushButton:pressed  {"
    "background-color: rgb(220,250, 50);"
    "border-style: inset;"
    "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(255, 223, 40, 255), stop:1 rgba(167, 122, 30, 255))"
    "}";

    but_nex->setStyleSheet(StalyNextButt.arg(QString::number(butt_size*0.01)));
    QString  StalyTestEndButt=" "
    "QPushButton  {"
    "background-color: rgb(20, 20, 220);"
    "border: 2px outset rgb(190,195, 170);"
    "border-radius: %1px;"
    "font: "+QString::number(nb_h*0.4)+"px;"
    "color: rgb(240, 240, 240);"
    "font: bold;"
    "width:"+QString::number(butt_size)+"px;"
    "height:" +QString::number(butt_size)+"px;"
    "}"

    #ifndef Q_OS_ANDROID//Для Андрода отключаем "hover" т.к. мешает
    "QPushButton:hover {"
    "background-color: rgb(11, 37, 98);"
    "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(42, 226, 30, 255), stop:1 rgba(40, 148, 40, 255));"
    "}"
   #endif
                                                        "   }"
    "QPushButton:pressed  {"
    "background-color: rgb(220,250, 50);"
    "border-style: inset;"
    "color: qlineargradient(spread:pad, x1:0.318, y1:0.0113636, x2:0.114, y2:0.835, stop:0 rgba(255, 223, 40, 255), stop:1 rgba(167, 122, 30, 255))"
    "}";

    but_test_end=new QPushButton("Закончить",this);
    but_test_end->setGeometry(width()*0.1,height()*0.95-nb_h,width()*0.2,nb_h);
    connect(but_test_end,SIGNAL(clicked()),this,SLOT(slotClickedTestEndButton()));
    but_test_end->setStyleSheet(StalyTestEndButt.arg(QString::number(butt_size*0.01)));

    labelTextPassed=new QLabel(this);
    labelTextPassed->setGeometry(width()*0.04,height()*0.22,width()*0.25,height()*0.08);
    QFont p_font;
    p_font.setFamily("Times New Roman");
    p_font.setBold(true);
    p_font.setPixelSize(height()*0.015);
    labelTextPassed->setFont(p_font);
    setPassedLabeltext(0,0);


    labelActionText=new QLabel(this);
    QFont font;
    font.setPixelSize(width()*0.05);
    labelActionText->setFont(font);
    labelActionText->setGeometry(width()*0.3,height()*0.29,width()*0.4,height()*0.1);
    setTextLabelAction(0,0,0);
}
void Scene::setDates(std::vector<AllDates> d)
{
    dates=d;
    QuestNumber=0;
    StrReadAnswer.clear();
    setTextLabelAction(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2(),StrReadAnswer,dates[QuestNumber].getSign());
    setPassedLabeltext(QuestNumber+1,dates.size());
    hideButtons(false);
    RemovetemForActions();
}

void Scene::slotButtonsClicked()
{

     QString str_val=((QPushButton*)sender())->text();

    if(StrReadAnswer.size()<QString::number(dates[QuestNumber].getAnswer()).size())
    {
        StrReadAnswer+= str_val;
    }
     setTextLabelAction(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2(),StrReadAnswer,dates[QuestNumber].getSign());

     if(StrReadAnswer.size()==QString::number(dates[QuestNumber].getAnswer()).size())
     {
        if(dates[QuestNumber].readAnswers(StrReadAnswer.toInt()))
        {
            emit singalCorrectAnswer();
            hideButtons(true);

            if(dates[QuestNumber].getSign()=="×")
            {
                CreateItemForActions(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2());
            }
            else if(dates[QuestNumber].getSign()=="÷")
            {
                CreateItemForActions(dates[QuestNumber].getAnswer(),dates[QuestNumber].getNum_2());
            }
        }
    }
}

void Scene::slotButtonsNextClicked()
{

    if(dates[QuestNumber].is_error())
    {
        dates[QuestNumber].setError(true);

        emit singalNotCorrectAnswer();
        animationGroup->start();
        QMessageBox ms;
        ms.setWindowTitle("Ошибка!");
        ms.setText(dates[QuestNumber].if_IsError());
        ms.exec();

     }

    hideButtons(false);
    RemovetemForActions();
    CloseSceneHelps();

    StrReadAnswer.clear();
    QuestNumber++;

    if((QuestNumber) == int(dates.size()) )
    {
        ShowTestEnd();
        return ;
    }
    setTextLabelAction(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2(),StrReadAnswer,dates[QuestNumber].getSign());
    setPassedLabeltext(QuestNumber+1,dates.size());
}

void Scene::slotClickedDeleteButton()
{
    if(!StrReadAnswer.isEmpty())
    {
        StrReadAnswer.resize(StrReadAnswer.size()-1);
        setTextLabelAction(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2(),StrReadAnswer,dates[QuestNumber].getSign());
    }
}

void Scene::slotClickedTestEndButton()
{
    QMessageBox msgBox;
                //  msgBox.setText("Запись найдена...");
    msgBox.setInformativeText("Вы действительно хотите закончить тест?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *Yes = msgBox.addButton(tr("Да"), QMessageBox::ActionRole);
    QPushButton *Not = msgBox.addButton(tr("Нет"), QMessageBox::ActionRole);


    msgBox.exec();
    if(msgBox.clickedButton()== Yes)
    {
        emit  singalTestAborted();
    }
}

void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawImage(QRect(0,0,width(),height()),QImage(":/images/back_round_image.jpeg"));//основной задний фон
    painter->drawImage(QRect(width()*0.03,height()*0.2,width()*0.94,height()*0.77),QImage(":/images/white_photo.jpg"));

    QImage imn_cosm(":/images/new_cosmonavt.png");
    int im_w=width()/4;
    double sootn=double(imn_cosm.height())/imn_cosm.width();
    painter->drawImage(QRect(width()-im_w,height()-im_w*sootn,im_w,im_w*sootn),imn_cosm);

}
void Scene::setStateWindow(Scene::StateWindow st)
{
    state=st;
    switch (state)
    {
        case StateWindow::Test:
            RemovetemForActions();
            CloseSceneHelps();
            hideButtons(false);
        break;
        case StateWindow::HelpActions:
            hideButtons(true);
            SceneHelps(dates[QuestNumber].if_IsError());
            RemovetemForActions();
        break;
        case StateWindow::ViewItemActions:
            hideButtons(false);
            CloseSceneHelps();
            CreateItemForActions(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2());
        break;
        case StateWindow::EndTest:
            hideButtons(false);
            CloseSceneHelps();
            RemovetemForActions();
        break;
    }

    setTextLabelAction(dates[QuestNumber].getNum_1(),dates[QuestNumber].getNum_2(),StrReadAnswer,dates[QuestNumber].getSign());
    setPassedLabeltext(QuestNumber+1,dates.size());
}
void Scene::resizeEvent(QResizeEvent *event)
{
    scene()->setSceneRect(this->viewport()->rect());

    float by_h=0.76;
    int rast=(std::min(width(),height())*0.2);

    but_1->setGeometry(width()*0.3-butt_size/2,height()*0.41,butt_size,butt_size);
    but_2->setGeometry(width()*0.5-butt_size/2,height()*0.41,butt_size,butt_size);
    but_3->setGeometry(width()*0.7-butt_size/2,height()*0.41,butt_size,butt_size);

    but_4->setGeometry(width()*0.3-butt_size/2,height()*0.528,butt_size,butt_size);
    but_5->setGeometry(width()*0.5-butt_size/2,height()*0.528,butt_size,butt_size);
    but_6->setGeometry(width()*0.7-butt_size/2,height()*0.528,butt_size,butt_size);

    but_7->setGeometry(width()*0.3-butt_size/2,height()*0.646,butt_size,butt_size);
    but_8->setGeometry(width()*0.5-butt_size/2,height()*0.646,butt_size,butt_size);
    but_9->setGeometry(width()*0.7-butt_size/2,height()*0.646,butt_size,butt_size);

    but_0->setGeometry(width()*0.5-butt_size/2,height()*by_h,butt_size,butt_size);
    but_delete->setGeometry(width()*0.7-butt_size/2,height()*by_h,butt_size,butt_size);

    but_1->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_2->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_3->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_4->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_5->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_6->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_7->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_8->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_9->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));
    but_0->setStyleSheet(ShetStaly.arg(QString::number(butt_size/2)));

    HelpLabel->setGeometry(width()*0.2,height()*0.17,width()*0.6,height()*0.7);
    MainLabel->setGeometry(0,height()*0.01,width(),height()*0.2);

    labelTextPassed->setGeometry(width()*0.04,height()*0.22,width()*0.25,height()*0.08);

    SettingActionText();
    SettingPassedText();

    int nb_w=width()*0.35,nb_h=height()*0.06;
    but_nex->setGeometry((width()-nb_w)/2,height()*0.95-nb_h,nb_w,nb_h);

    but_test_end->setGeometry(width()*0.1,height()*0.95-nb_h,width()*0.2,nb_h);

}
void Scene::ShowTestEnd()
{
    QString ms_text="<center>Внимане вы прошли текст.</center>"
                    "<center>Количество правильных ответов %1 из %2 </center>"
                    "<center> %3 </center>";
    int prav=0;
    for(auto it:dates)
    {
        if(!it.is_error())
        {
            prav++;
        }
    }

    emit signalTestEnd(prav,dates.size());
}
void Scene::hideButtons(bool h)
{
    but_1->setHidden(h);
    but_2->setHidden(h);
    but_3->setHidden(h);
    but_4->setHidden(h);
    but_5->setHidden(h);
    but_6->setHidden(h);
    but_7->setHidden(h);
    but_8->setHidden(h);
    but_9->setHidden(h);
    but_0->setHidden(h);
    but_delete->setHidden(h);
}
void Scene::CreateItemForActions(int m,int n)
{
    ItemViewAnswer* item=new ItemViewAnswer(n,m,width()*0.7,height()*0.45);
    item->setPos(width()*0.143,height()*0.38);
    scene()->addItem(item);
}
void Scene::RemovetemForActions()
{
    scene()->clear();
}
void Scene::setTextLabelAction(int m, int n, QString an, QString ch)
{
    if(an.isEmpty())
    {
        an="?";
    }
    if(an.size()==1 && !dates.empty() &&  QString::number(dates[QuestNumber].getAnswer()).size()==2)
    {
        an+="?";
    }

    labelActionText->setText(QString("<center>%1</center>").arg(ActionText.arg(m).arg(ch).arg(n).arg(an)));
}
void Scene::setPassedLabeltext(int m, int n)
{
    labelTextPassed->setText(TextPassed.arg(m).arg(n));
}
void Scene::SceneHelps(QString text)
{
    HelpLabel->setHidden(false);
    HelpLabel->setText(text);
}
void Scene::CloseSceneHelps()
{
    HelpLabel->setHidden(true);
}
void Scene::SettingActionText()
{
    QFont font;
    int lable_w=width()*0.4,label_h=height()*0.05;
    font.setBold(true);
    font.setPixelSize(label_h);
    labelActionText->setFont(font);
    labelActionText->setGeometry(width()*0.3,height()*0.29,lable_w,height()*0.1);
}
void Scene::SettingPassedText()
{
    labelTextPassed->setGeometry(width()*0.04,height()*0.22,width()*0.25,height()*0.08);
    QFont p_font;
    p_font.setFamily("Times New Roman");
    p_font.setBold(true);
    p_font.setPixelSize(height()*0.02);
    labelTextPassed->setFont(p_font);
}
void Scene::AnimationReadError()
{
     auto cent=but_nex->geometry();
     int by_pixsels=20,time=100;

        // Создадим анимацию свойства передвижения слева-сверху направо-сверху
    QPropertyAnimation* anim_1 = new QPropertyAnimation(but_nex, "geometry");
    anim_1->setDuration(time); // Длительность анимации
    anim_1->setStartValue(cent); // Стартовая позиция и геометрия анимации
    anim_1->setEndValue(cent.translated(by_pixsels,0)); // Конечная позиция и геометрия анимации
    animationGroup->addAnimation(anim_1); // Добавим анимацию в группу

        // Справа-сверху вниз-справа
    QPropertyAnimation* anim_2 = new QPropertyAnimation(but_nex, "geometry");
    anim_2->setDuration(time);
    anim_2->setStartValue(anim_1->endValue());
    anim_2->setEndValue(cent.translated(-by_pixsels, 0));
    animationGroup->addAnimation(anim_2);

        // Снизу-справа налево-вниз
    QPropertyAnimation* anim_3 = new QPropertyAnimation(but_nex, "geometry");
    anim_3->setDuration(time);
    anim_3->setStartValue(anim_2->endValue());
    anim_3->setEndValue(cent.translated(by_pixsels, 0));
    animationGroup->addAnimation(anim_3);

        // Слева-снизу наверх-слева
    QPropertyAnimation* anim_4 = new QPropertyAnimation(but_nex, "geometry");
    anim_4->setDuration(time);
    anim_4->setStartValue(anim_3->endValue());
    anim_4->setEndValue(cent.translated(-by_pixsels, 0));
    animationGroup->addAnimation(anim_4);

    QPropertyAnimation* anim_5 = new QPropertyAnimation(but_nex, "geometry");
    anim_5->setDuration(time);
    anim_5->setStartValue(anim_4->endValue());
    anim_5->setEndValue(cent.translated(by_pixsels, 0));
    animationGroup->addAnimation(anim_5);

    QPropertyAnimation* anim_6 = new QPropertyAnimation(but_nex, "geometry");
    anim_6->setDuration(time);
    anim_6->setStartValue(anim_5->endValue());
    anim_6->setEndValue(cent);
    animationGroup->addAnimation(anim_6);

}
