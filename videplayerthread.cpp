#include "videplayerthread.h"
#include <QDebug>

VidePlayerThread::VidePlayerThread()
{
    qDebug()<<"VidePlayerThread";

}

void VidePlayerThread::setFileName(QString file_name) {
    file_name_ = file_name;
    qDebug()<<file_name_;
}

void VidePlayerThread::run() {
    qDebug()<<"run";

    char file_path[1024 + 1] = {0};;

    strcpy(file_path,file_name_.toUtf8().data());

    AVFormatContext *pFormatCtx = NULL;
    AVCodecContext *pCodecCtx = NULL;
    AVFrame *pFrame = NULL;
    AVFrame *pFrameRGB = NULL;
    AVCodec *pCodec = NULL;

    //AVCodecContext *aCodecCtx = NULL;
    //AVCodec *aCodec = NULL;

    //int audioStream = -1;
    int videoStream = -1;
    unsigned int i = 0;

    AVPacket *packet = NULL;
    uint8_t *out_buffer = NULL;

    static struct SwsContext *img_convert_ctx;

    int numBytes = 0;
    int ret = 0;
    int got_picture = 0;


    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0) {
        //printf("can't open the file. \n");
        qDebug()<<"can't open the file. ";
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        //printf("Could't find stream infomation.\n");
        qDebug()<<"Could't find stream infomation.";
        return;
    }

    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
    }

    if (videoStream == -1) {
        //printf("Didn't find a video stream.\n");
        qDebug()<<"Didn't find a video stream.";
        return;
    }


    ///查找视频解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    if (pCodec == NULL) {
        //printf("PCodec not found.\n");
        qDebug()<<"PCodec not found.";
        return;
    }

    ///打开视频解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        //printf("Could not open video codec.\n");
        qDebug()<<"Could not open video codec.";
        return;
    }

    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
            pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
            PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

    numBytes = avpicture_get_size(PIX_FMT_RGB32, pCodecCtx->width,pCodecCtx->height);

    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, PIX_FMT_RGB32,
            pCodecCtx->width, pCodecCtx->height);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    packet = (AVPacket *) malloc(sizeof(AVPacket));
    av_new_packet(packet, y_size);

    av_dump_format(pFormatCtx, 0, file_path, 0);

    while (1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == videoStream) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);

            if (ret < 0) {
                printf("decode error.");
                return;
            }

            if (got_picture) {
                sws_scale(img_convert_ctx,
                        (uint8_t const * const *) pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);

                //把这个RGB数据 用QImage加载
                QImage tmpImg((uchar *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                this->disPlayVideo(image); //调用激发信号的函数
            }
        }
        av_free_packet(packet);
    }

    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}

void VidePlayerThread::disPlayVideo(QImage img)
{
    //qDebug()<<"disPlayVideo";
    emit sig_GetOneFrame(img);
}
