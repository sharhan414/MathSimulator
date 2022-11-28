#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QChar>
#include "alldates.h"
#include <QSequentialAnimationGroup>

class Scene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr);
    enum class StateWindow{Test,ViewItemActions,HelpActions,EndTest};
    void setDates(std::vector<AllDates> d);
signals:
    void signalTestEnd(int ans,int val);
    void singalTestAborted();
    void singalCorrectAnswer();
    void singalNotCorrectAnswer();
private slots:
    void slotButtonsClicked();
    void slotButtonsNextClicked();
    void slotClickedDeleteButton();
    void slotClickedTestEndButton();
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    StateWindow state;
    void setStateWindow(StateWindow st);

    void ShowTestEnd();
    void hideButtons(bool h);
    void CreateItemForActions(int m,int n);
    void RemovetemForActions();
    void setTextLabelAction(int m,int n,QString an,QString ch="×");
    void setPassedLabeltext(int m,int n);
    void SceneHelps(QString text);
    void CloseSceneHelps();
    void SettingActionText();
    void SettingPassedText();
    void AnimationReadError();

    QLabel *labelTextPassed,*labelActionText,*HelpLabel;
    QLabel* MainLabel;
    QString TextPassed,ActionText;
    QString  ShetStaly;
    QString StrReadAnswer;

    int butt_size;
    int QuestNumber;

    std::vector<AllDates> dates;
    QPushButton* but_1;
    QPushButton* but_2;
    QPushButton* but_3;
    QPushButton* but_4;
    QPushButton* but_5;
    QPushButton* but_6;
    QPushButton* but_7;
    QPushButton* but_8;
    QPushButton* but_9;
    QPushButton* but_0;
    QPushButton* but_delete;
    QPushButton* but_test_end;
    QPushButton* but_nex;

  QSequentialAnimationGroup*  animationGroup ;
};

#endif // SCENE_H
