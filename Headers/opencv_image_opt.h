#ifndef OPENCV_IMAGE_OPT_H
#define OPENCV_IMAGE_OPT_H
#include <QImage>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>



class opencv_image_opt
{
public:
    opencv_image_opt();
    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(QImage image);
};

#endif // OPENCV_IMAGE_OPT_H
