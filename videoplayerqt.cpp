#include "videoplayerqt.h"
#include "ui_videoplayerqt.h"
#include <QDebug>
#include <QFileDialog>

VideoPlayerQT::VideoPlayerQT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPlayerQT)
{
    ui->setupUi(this);

    connect(ui->pushButtonOpen,SIGNAL(clicked()),this,SLOT(slotBtnClick()));
    connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(slotBtnClick()));

    this->setWindowTitle("VideoPlayer QT");

    video_player_dialog_ = new VideoPlayerDialog(this);

    video_player_ = new VideoPlayer();

    video_player_->Init();
}

VideoPlayerQT::~VideoPlayerQT()
{
    delete video_player_dialog_;
    delete ui;
}

void VideoPlayerQT::slotBtnClick()
{
    if (QObject::sender() == ui->pushButtonOpen)
    {
       qDebug()<<"pushButtonOpen";
       QString s = QFileDialog::getOpenFileName(
                  this, "选择要播放的文件",
                   "/",//初始目录
                   "视频文件 (*.flv *.rmvb *.avi *.MP4);; 所有文件 (*.*);; ");
       if (!s.isEmpty())
       {
           s.replace("/","\\");
           file_name_ = s;
       }
       qDebug()<<file_name_;
       video_player_->setFileName(file_name_);

    }
    else if (QObject::sender() == ui->pushButtonPlay)
    {
        ui->horizontalLayout->addWidget(video_player_dialog_);
        video_player_dialog_->show();

        video_player_->Play();
    }

}
