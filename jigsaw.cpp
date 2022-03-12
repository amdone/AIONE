#include "jigsaw.h"
#include "opencv_image_opt.h"
using cv::Mat;

//jigsaw::jigsaw()
//{
//    this->hight = 600;
//    this->weight = 800;
//    m_engine = &engine;
//}

//jigsaw::size jigsaw::getImgaeSize(QString filepath){
//    size resSize = {0,0};
//    QFileInfo aImg(filepath);
//    if (!aImg.isFile()){
//        qDebug() << "this image path is not a file!";
//        return resSize;
//    }
//    QImage thisImage();
//    return resSize;
//}

//int jigsaw::testConvert(){
//    Mat a = cv::imread("C:/Users/Eichi/Desktop/imgs/all.png");
//    opencv_image_opt convert;
//    QImage b = convert.cvMat2QImage(a);
//    qDebug() << b.height();
//    return b.height();
//}

jigsaw::jigsaw(QQmlApplicationEngine &engine)
{
    this->m_engine = &engine;
}

void jigsaw::openFolder(QString filepath){
    qDebug() << "open folder";
    this->nums = 35;
    for(int i=0;i< this->nums;++i){
        this->images.push_back("");
        this->choosen.push_back(true);
    }
    emit imagesNumsCall(this->nums);
}

void jigsaw::popImage(int index) {
    this->choosen[index] = false;
    qDebug() << index << " is poped";
}

void jigsaw::pushImage(int index) {
    this->choosen[index] = true;
}




