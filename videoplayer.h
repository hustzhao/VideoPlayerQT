#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
#include "videplayerthread.h"

class VideoPlayer
{
public:
    VideoPlayer();
    ~VideoPlayer();
    void Init();
    void Play();
    void setFileName(const QString file_name);

};

#endif // VIDEOPLAYER_H
