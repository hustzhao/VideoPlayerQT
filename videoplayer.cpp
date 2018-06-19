#include "videoplayer.h"
#include <QDebug>

VideoPlayer::VideoPlayer()
{
    qDebug()<<"VideoPlayer";
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::Init() {
    av_register_all();
    avformat_network_init();

    if (SDL_Init(SDL_INIT_AUDIO)) {
        fprintf(stderr,"Could not initialize SDL - %s. \n", SDL_GetError());
        exit(1);
    }


    return;
}

void VideoPlayer::Play() {

}

void VideoPlayer::setFileName(const QString file_name) {
    qDebug()<<file_name;


}
