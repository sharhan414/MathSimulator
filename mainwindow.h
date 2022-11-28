#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "startscene.h"
#include <QStackedWidget>
#include "testendscene.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>
class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void slotPrinDates(vector<AllDates> d);
    void slotTestEnd(int ans,int val);
    void slotTestAborted();
    void slotCorrectAnswer();
    void slotNotCorrectAnswer();


    void slotNewTest();
private:
    Scene* scene;
    StartScene* st_scene;
    TestEndScene* end_scene;
    QStackedWidget* stackedWidget;

    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист
    QThread *PlayerThread;
};
#endif // MAINWINDOW_H
