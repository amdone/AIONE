#ifndef JIGSAW_H
#define JIGSAW_H
#include <QObject>
#include <QImage>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QVector>
#include <QQmlApplicationEngine>
//#include <opencv2/opencv.hpp>

class jigsaw : public QObject
{
    Q_OBJECT
private:
    int hight;
    int weight;
    int nums;
    QVector<QString> images;
    QVector<bool> choosen;
    struct size{
        int w,h;
    };
    QQmlApplicationEngine *m_engine;

public:
    using QObject::QObject;
    jigsaw(QQmlApplicationEngine& engine);
    size getImgaeSize(QString);
    size* getAllImagesSize();
    int saveImage();
    //Q_INVOKABLE int testConvert();
public slots:
    void openFolder(QString);
    void popImage(int);
    void pushImage(int);
signals:
    void imagesNumsCall(int) const;
    void imageHasRemoved(int) const;
};

#endif // JIGSAW_H
