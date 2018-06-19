#ifndef VIDEPLAYERTHREAD_H
#define VIDEPLAYERTHREAD_H

#include <QThread>
#include <QImage>

#define SDL_MAIN_HANDLED

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include <libavutil/time.h>
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
    #include "libswresample/swresample.h"

    #include <SDL.h>
    #include <SDL_audio.h>
    #include <SDL_types.h>
    #include <SDL_name.h>
    #include <SDL_main.h>
    #include <SDL_config.h>
}


class VidePlayerThread : public QThread
{
    Q_OBJECT
public:
    VidePlayerThread();
    void setFileName(QString file_name);

protected:
    void run();
private:
    QString file_name_;
    void disPlayVideo(QImage img);
signals:
    void sig_GetOneFrame(QImage);
};

#endif // VIDEPLAYERTHREAD_H
