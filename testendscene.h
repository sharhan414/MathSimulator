#ifndef TESTENDSCENE_H
#define TESTENDSCENE_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>

class TestEndScene : public QWidget
{
    Q_OBJECT
public:
    explicit TestEndScene(QWidget *parent = nullptr);
    void setResult(int ans,int val);
signals:
    void signalNewTest();
private slots:
    void slotNewTest();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    QLabel *label,*lableAboutTest;
    QLabel* MainLabel;

    QPushButton* but_new_test;
    int answers,values;

    QString addesText;
};

#endif // TESTENDSCENE_H
