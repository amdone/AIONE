#ifndef JIGSAW_H
#define JIGSAW_H
#include <random>
#include <chrono>
#include <tuple>
#include <algorithm>
#include <QObject>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QRect>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QVector>
#include <QQmlApplicationEngine>
//#include <opencv2/opencv.hpp>

struct imageInfo {
    //int index;
    int width;
    int height;
    int filesize;
    bool choosen;
    QString filepath;
};

class jigsaw : public QObject
{
    Q_OBJECT
private:
    int nums;  //当前图库的图片数量
    //unsigned seed;  //随机数引擎需要的种子
    int arg_height = 1080;
    int arg_width = 1920;
    int arg_nums;
    double arg_offset;
    QString save_filepath;
    QString folderPath;
    QVector<imageInfo> imagesInfos;
    QVector<QRect> rects;  //用于拼图的矩形数组
    QQmlApplicationEngine *m_engine;

public:
    using QObject::QObject;
    jigsaw(QQmlApplicationEngine& engine);
    QString generate();
    void RectsInit();
    int GetMaxRectIndex();
    int GetRondomIndexFromRects();
    QImage GetHImage(QVector<imageInfo>& images);
    QImage GetWImage(QVector<imageInfo>& images);
    QImage GetMImage(QVector<imageInfo>& images);
    void splitImages(QVector<imageInfo> &HImages, QVector<imageInfo> &WImages, QVector<imageInfo> &MImages) const noexcept;
public slots:
    void openFolder(QString);
    void popImage(int);
    void pushImage(int);
    void requestImageInfo(int);
    void generateFinalImage();
signals:
    void imagesNumsCall(int) const;
    void imageHasRemoved(int) const;
    void returnImageInfo(int index, int width, int height, int filesize,bool choosen,QString filepath) const;
};

#endif // JIGSAW_H
