#ifndef JIGSAW_H
#define JIGSAW_H
#include <random>
#include <chrono>
#include <QObject>
#include <QImage>
#include <QImageReader>
#include <QPainter>
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
    int nums;
    int arg_height = 1080;
    int arg_width = 1920;
    int arg_nums;
    double arg_offset;
    QString save_filepath;
    QString folderPath;
    QVector<imageInfo> imagesInfos;
    QQmlApplicationEngine *m_engine;

public:
    using QObject::QObject;
    jigsaw(QQmlApplicationEngine& engine);
    QString generate();
    //TODO:合成图像
    //https://stackoverflow.com/questions/18998850/how-to-merge-two-images-into-one-using-qimage-and-qpainter-in-qt
public slots:
    void openFolder(QString);
    void popImage(int);
    void pushImage(int);
    void requestImageInfo(int);
    void generateFinalImage();
signals:
    void imagesNumsCall(int) const;
    void imageHasRemoved(int) const;
    void returnImageInfo(int, int, int, int, bool, QString) const;
};

#endif // JIGSAW_H
