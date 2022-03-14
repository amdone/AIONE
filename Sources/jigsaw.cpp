#include "jigsaw.h"
#include "opencv_image_opt.h"
#include "imagewidthheight.cpp"
using cv::Mat;

///
/// \brief GetFileList 得到path指定的目录下的所有文件
/// \param path 文件夹目录
/// \return 文件列表
///
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

///
/// \brief GetImagesList 从给定的目录中获取所有的图片路径
/// \param path 文件夹目录
/// \return 图片文件文件列表
///
//QVector<QString> GetImagesList(QString path) {
//    QFileInfoList allFiles = GetFileList(path);
//    QVector<QString> resImagesArr;
//    const int theNumbersOfImagesTypes = 3;
//    QString imagesTypes[theNumbersOfImagesTypes] = {".jpg",".png",".jpeg"};
//    for(auto i : allFiles){
//        QString filename = i.absoluteFilePath();
//        for(auto j : imagesTypes){
//           if(filename.endsWith(j,Qt::CaseInsensitive)){
//                resImagesArr.append(filename);
//           }
//        }
//    }
//    return resImagesArr;
//}


QFileInfoList GetImagesList(QString path) {
    QFileInfoList allFiles = GetFileList(path);
    QFileInfoList resImagesArr;
    const int theNumbersOfImagesTypes = 3;
    QString imagesTypes[theNumbersOfImagesTypes] = {".jpg",".png",".jpeg"};
    for(auto i : allFiles){
        QString filename = i.absoluteFilePath();
        for(auto j : imagesTypes){
           if(filename.endsWith(j,Qt::CaseInsensitive)){
                resImagesArr.append(i);
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


///
/// \brief jigsaw::jigsaw 构造函数
/// \param engine Qml引擎
///
jigsaw::jigsaw(QQmlApplicationEngine &engine)
{
    this->m_engine = &engine;
}

///
/// \brief jigsaw::openFolder 打开文件夹，然后根据文件夹的内容修改私有成员变量
/// \param filepath 文件夹路径
///
void jigsaw::openFolder(QString filepath){
    imageInfo image;
    this->imagesInfos.clear();
    this->folderPath = filepath.remove(0,8);

    for(auto i : GetImagesList(this->folderPath)){
        QString imagePath = i.absoluteFilePath();
        QImageReader reader(imagePath);
        //qDebug()<<reader.size();
        auto imageSize = reader.size();
        image.width = imageSize.width();
        image.height = imageSize.height();
        image.filepath = imagePath;
        image.choosen = true;
        image.filesize = i.size();
        this->imagesInfos.push_back(image);
    }
    this->nums = this->imagesInfos.size();
    qDebug() << "open folder:"<<this->folderPath<<" nums:"<<this->nums;
    emit imagesNumsCall(this->nums);
}

void jigsaw::popImage(int index) {
    this->imagesInfos[index].choosen = false;
    qDebug() << index << " is poped";
}

void jigsaw::pushImage(int index) {
    this->imagesInfos[index].choosen = true;
}

//void jigsaw::requestImagePath(int index){
//    emit returnImagePath(index, this->imagesInfos[index].filepath);
//}

//void jigsaw::requestImageWH(int index) {
//    auto image = &this->imagesInfos[index];
//    emit returnImageWH(index, image->width, image->height);
//}

void jigsaw::requestImageInfo(int index) {
    auto image = &this->imagesInfos[index];
    emit returnImageInfo(index, image->width, image->height,
                         image->filesize,image->choosen,image->filepath);
}







