#include "testendscene.h"
#include <QPainter>
#include <QFont>
#include <QPushButton>
TestEndScene::TestEndScene(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPixelSize(height()*0.03);

    MainLabel=new QLabel(this);
    QString l_text="<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"7\"> <strong><center>Тренажёр</strong></center></font>"
               "<strong><font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#FFA500\" size=\"6\"><center>таблицы умножения</center>"
               "<center>и деления</center></font></strong>";
    MainLabel->setText(l_text);

    label=new QLabel("<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#191970\" size=\"4\"><center>Капитан, тест завершён!</center></font>",this);
    label->setFont(font);
    answers=0;
    values=1;
    addesText="<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#000080\" size=\"3\"><center>Тест на тренеровку</center>"
               "<center>устного умножения и деления</center>"
               "<center>пройден. Вы ответили</center>"
               "<center>на %1 из %2 вопросов.</center>"
               "<center>%3</center></font>";

    lableAboutTest=new QLabel(this);
    lableAboutTest->setFont(font);
    lableAboutTest->setText(addesText);

    but_new_test=new QPushButton("Новый тест",this);

    connect(but_new_test,SIGNAL(clicked()),this,SLOT(slotNewTest()));
    int nb_w=width()*0.35,nb_h=height()*0.06;

    QString  StalyNewTestButt=" "
    "QPushButton  {"
    "background-color: rgb(157, 14, 124);"
    "border: 2px outset rgb(190,195, 170);"
    "border-radius: %1px;"
    "font: "+QString::number(nb_h*0.4)+"px;"
    "color: rgb(240, 240, 240);"
    "font: bold;"
    "width:"+QString::number(nb_w)+"px;"
    "height:" +QString::number(nb_h)+"px;"
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
    but_new_test->setStyleSheet(StalyNewTestButt.arg(nb_w*0.01));
}

void TestEndScene::setResult(int ans, int val)
{
    answers=ans;
    values=val;

    if(ans==val)
    {

        lableAboutTest->setText("<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"#000080\" size=\"3\"><center>Тест на тренеровку</center>"
                           "<center>устного умножения и деления</center>"
                           "<center>пройден. Вы ответили</center>"
                           "<center>на все вопросы.</center>"
                           "<center>Идеально!!!</center></font>");
        return;
    }
    double x=double(answers)/values;

    auto str=addesText.arg(ans).arg(val);

    if(x>=0.8)
    {
        str=str.arg("Хорошо)");
    }
    else if(x>=0.6 and x<0.8)
    {
        str=str.arg("Неплохо!");
    }
    else if(x>=0.4 and x<0.6)
    {
        str=str.arg("Слабовато.");
    }
    else
    {
        str=str.arg("Плохо((");
    }
        lableAboutTest->setText(str);

    update();
}

void TestEndScene::slotNewTest()
{
    emit signalNewTest();
}

void TestEndScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QRect(0,0,width(),height()),QImage(":/images/back_round_image.jpeg"));
    painter.drawImage(QRect(width()*0.03,height()*0.2,width()*0.94,height()*0.77),QImage(":/images/white_photo.jpg"));

    QImage imn_cosm(":/images/new_cosmonavt.png");
    int im_w=width()/4;
    double sootn=double(imn_cosm.height())/imn_cosm.width();
    painter.drawImage(QRect(width()-im_w,height()-im_w*sootn,im_w,im_w*sootn),imn_cosm);

    double x=double(answers)/values;

    QImage smyl_im;

    if(x>=0.8)
    {
        smyl_im=  QImage(":/images/Smyl_1.png") ;
    }
    else if(x>=0.6 and x<0.8)
    {
        smyl_im=QImage(":/images/Smyl_2.png") ;
    }
    else if(x>=0.4 and x<0.6)
    {
        smyl_im=QImage(":/images/Smyl_3.png") ;
    }
    else
    {
        smyl_im=QImage(":/images/Smyl_4.png") ;
    }

    int smyl_w=width()*0.3;
    int smyl_h=(double(smyl_im.height())/smyl_im.width())*smyl_w;
    painter.drawImage(QRect((width()-im_w)/2,(height()-smyl_h)*0.75,smyl_w,smyl_h),smyl_im);
}

void TestEndScene::resizeEvent(QResizeEvent *event)
{
    label->setGeometry(0,height()*0.3,width(),height()*0.1);
    lableAboutTest->setGeometry(0,height()*0.32,width(),height()*0.35);
    int nb_w=width()*0.35,nb_h=height()*0.06;
    but_new_test->setGeometry((width()-nb_w)/2,height()*0.95-nb_h,nb_w,nb_h);
    MainLabel->setGeometry(0,height()*0.01,width(),height()*0.2);
}
