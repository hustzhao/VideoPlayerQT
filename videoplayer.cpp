#include "videoplayer.h"
#include <QDebug>

VideoPlayer::VideoPlayer()
{
    qDebug()<<"VideoPlayer";
}

VideoPlayer::~VideoPlayer()
{
    delete videoplayerthread_;
}

void VideoPlayer::Init() {
    av_register_all();
    avformat_network_init();

    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr,"Could not initialize SDL - %s. \n", SDL_GetError());
        exit(1);
    }

    videoplayerthread_ = new VidePlayerThread();
    return;
}

void VideoPlayer::Play() {
    videoplayerthread_->start();
}

void VideoPlayer::setFileName(const QString file_name) {
    qDebug()<<file_name;

    videoplayerthread_->setFileName(file_name);
}
