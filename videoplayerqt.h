#ifndef VIDEOPLAYERQT_H
#define VIDEOPLAYERQT_H

#include <QDialog>
#include "videoplayerdialog.h"

namespace Ui {
class VideoPlayerQT;
}

class VideoPlayerQT : public QDialog
{
    Q_OBJECT

public:
    explicit VideoPlayerQT(QWidget *parent = 0);
    ~VideoPlayerQT();

private slots:
    void slotBtnClick();

private:
    Ui::VideoPlayerQT *ui;
    VideoPlayerDialog* video_player_{NULL};
    QString file_name_{};
};

#endif // VIDEOPLAYERQT_H
