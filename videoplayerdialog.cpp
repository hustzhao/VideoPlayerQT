#include "videoplayerdialog.h"
#include "ui_videoplayerdialog.h"
#include <QDebug>
#include <QPainter>

VideoPlayerDialog::VideoPlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPlayerDialog)
{
    ui->setupUi(this);
}

VideoPlayerDialog::~VideoPlayerDialog()
{
    delete ui;
}

void VideoPlayerDialog::slotGetOneFrame(QImage img) {
    //qDebug()<<"slotGetOneFrame";
    image_ = img;
    update();
}

void VideoPlayerDialog::paintEvent(QPaintEvent *event) {
    //qDebug()<<"paintEvent";
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0,0,this->width(),this->height());

    if(image_.size().width() <= 0) return;

    QImage img = image_.scaled(this->size(),Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x = x / 2;
    y = y / 2;

    painter.drawImage(QPoint(x,y),img);

}
