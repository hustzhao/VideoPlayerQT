#ifndef VIDEOPLAYERDIALOG_H
#define VIDEOPLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class VideoPlayerDialog;
}

class VideoPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoPlayerDialog(QWidget *parent = 0);
    ~VideoPlayerDialog();
public slots:
    void slotGetOneFrame(QImage);
private:
    Ui::VideoPlayerDialog *ui;
    QImage image_;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VIDEOPLAYERDIALOG_H
