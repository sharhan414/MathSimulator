#include "mainwindow.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(350,600);

    st_scene=new StartScene(this);
    setCentralWidget(st_scene);
    connect(st_scene,SIGNAL(signalDates(vector<AllDates>)),this,SLOT(slotPrinDates(vector<AllDates>)));
    scene=new Scene;
    connect(scene,SIGNAL(signalTestEnd(int,int)),this,SLOT(slotTestEnd(int,int)));
    connect(scene,SIGNAL(singalTestAborted()),this,SLOT(slotTestAborted()));
    connect(scene,SIGNAL(singalCorrectAnswer()),this,SLOT(slotCorrectAnswer()));
    connect(scene,SIGNAL(singalNotCorrectAnswer()),this,SLOT(slotNotCorrectAnswer()));

    stackedWidget = new QStackedWidget(this);

    end_scene=new TestEndScene;
    connect(end_scene,SIGNAL(signalNewTest()),this,SLOT(slotNewTest()));

    stackedWidget->addWidget(st_scene);
    stackedWidget->addWidget(scene);
    stackedWidget->addWidget(end_scene);

    setCentralWidget(stackedWidget);
    setWindowTitle("Тест-тренажёр");

    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist();  // Инициализация плейлиста

    m_player->setPlaylist(m_playlist);          // Установка плейлиста в аудио плеер
    m_playlist->addMedia(QUrl("qrc:/Signals/badly.mp3"));
    m_playlist->addMedia(QUrl("qrc:/Signals/error_signal_2.mp3"));  // Добавление трека в плейлист
    m_playlist->addMedia(QUrl("qrc:/Signals/signal_corect_answer.mp3"));  // Добавление трека в плейлист
    m_playlist->addMedia(QUrl("qrc:/Signals/signal_victory.mp3"));  // Добавление трека в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем один раз

    PlayerThread=new QThread(this);

    connect(this,SIGNAL(destroyed()),PlayerThread,SLOT(quit()));
    m_player->moveToThread(PlayerThread);
    PlayerThread->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotPrinDates(vector<AllDates> d)
{
    stackedWidget->setCurrentIndex(1);
    scene->setDates(d);
}

void MainWindow::slotTestEnd(int ans,int val)
{
    end_scene->setResult(ans,val);
    stackedWidget->setCurrentIndex(2);

    if((double(ans)/val) < 0.3)
    {
        m_playlist->setCurrentIndex(0);
        m_player->play();
    }
    else
    {
        m_playlist->setCurrentIndex(3);
        m_player->play();
    }
}

void MainWindow::slotTestAborted()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::slotCorrectAnswer()
{
    m_playlist->setCurrentIndex(2);
    m_player->play();
}

void MainWindow::slotNotCorrectAnswer()
{
    m_playlist->setCurrentIndex(1);
    m_player->play();
}

void MainWindow::slotNewTest()
{
    stackedWidget->setCurrentIndex(0);
}
