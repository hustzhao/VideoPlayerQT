#include "videoplayerdialog.h"
#include "ui_videoplayerdialog.h"

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
