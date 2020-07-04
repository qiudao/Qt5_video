#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMediaPlayer> 
#include <QVideoWidget>
#include <QPushButton>
#include <QMediaPlaylist>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


	QWidget *widget = new QWidget(this);
	widget->resize(400, 300);
	QVBoxLayout *layout = new QVBoxLayout;
	QMediaPlayer *player = new QMediaPlayer;
	QVideoWidget *vw = new QVideoWidget;
	layout->addWidget(vw);
	widget->setLayout(layout);
	player->setVideoOutput(vw);
	//player->setMedia(QUrl::fromLocalFile("D:/10.mp4"));
		QMediaPlaylist *playlist = new QMediaPlaylist;
		playlist->addMedia(QUrl("http://192.168.3.201:443/10.mp4"));
		playlist->addMedia(QUrl("http://192.168.3.201:443/19.mp4"));
		playlist->setCurrentIndex(0);
		player->setPlaylist(playlist);

	player->setVolume(50);
	player->play();
	//widget->show();
	qDebug() << "mediaStatus: " << player->mediaStatus() << "error: " << player->error();


	QPushButton *btn_start = new QPushButton("start");
	QPushButton *btn_stop = new QPushButton("stop");
	QPushButton *btn_prev = new QPushButton("prev");
	QPushButton *btn_next = new QPushButton("next");
	layout->addWidget(btn_start);
	layout->addWidget(btn_stop);
	layout->addWidget(btn_prev);
	layout->addWidget(btn_next);

	connect(btn_start, SIGNAL(clicked()), player, SLOT(play()));
	connect(btn_stop, SIGNAL(clicked()), player, SLOT(pause()));
	connect(player, SIGNAL(positionChanged(quint64)), this, SLOT(OnPlayerPosChanged(quint64)));
	connect(btn_prev, SIGNAL(clicked()), playlist, SLOT(previous()));
	connect(btn_next, SIGNAL(clicked()), playlist, SLOT(next()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OnPlayerPosChanged(quint64 pos)
{
	qDebug() << "pos: " << pos;
}
