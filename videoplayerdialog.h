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

private:
    Ui::VideoPlayerDialog *ui;
};

#endif // VIDEOPLAYERDIALOG_H
