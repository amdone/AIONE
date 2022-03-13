#include "jigsaw.h"
#include "opencv_image_opt.h"
using cv::Mat;

QFileInfoList GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks, QDir::Name);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = GetFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}

QVector<QString> GetImagesList(QString path) {
    QFileInfoList allFiles = GetFileList(path);
    QVector<QString> resImagesArr;
    const int theNumbersOfImagesTypes = 3;
    QString imagesTypes[theNumbersOfImagesTypes] = {".jpg",".png",".jpeg"};
    for(auto i : allFiles){
        QString filename = i.absoluteFilePath();
        for(auto j : imagesTypes){
           if(filename.endsWith(j,Qt::CaseInsensitive)){
                resImagesArr.append(filename);
           }
        }
    }
    return resImagesArr;
}

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
    this->images.clear();
    this->choosen.clear();
    this->folderPath = filepath.remove(0,8);

    for(auto i : GetImagesList(this->folderPath)){
        this->images.push_back(i);
        this->choosen.push_back(true);
    }
    this->nums = this->images.size();
    qDebug() << "open folder:"<<this->folderPath<<" nums:"<<this->nums;
    emit imagesNumsCall(this->nums);
}

void jigsaw::popImage(int index) {
    this->choosen[index] = false;
    qDebug() << index << " is poped";
}

void jigsaw::pushImage(int index) {
    this->choosen[index] = true;
}

void jigsaw::requestImagePath(int index){
    emit returnImagePath(index, this->images[index]);
}







