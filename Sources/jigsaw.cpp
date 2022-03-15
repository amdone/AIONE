#include "jigsaw.h"
#include "opencv_image_opt.h"
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
/// \brief GetImagesList 从给定的目录中获取包含所有图片文件信息的列表
/// \param path 文件夹目录
/// \return 图片文件信息列表
///
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
///
/// \brief GetHImage 从给定的一组图片中弹出一张竖图
/// \param images
/// \return QImage
///
QImage GetHImage(QVector<imageInfo>& images){
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height > 1.2){
            QImage retImage(*i);
            std::swap(*i,*(images.end()-1);
            images.erase(images.end()-1);
            return retImage;
        }
    }
    return nullptr_t;
}
///
/// \brief GetHImage 从给定的一组图片中弹出一张横图
/// \param images
/// \return QImage
///
QImage GetWImage(QVector<imageInfo>& images){
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height < 0.8){
            QImage retImage(*i);
            std::swap(*i,*(images.end()-1);
            images.erase(images.end()-1);
            return retImage;
        }
    }
    return nullptr_t;
}
///
/// \brief GetHImage 从给定的一组图片中弹出一张竖图
/// \param images
/// \return QImage
///
QImage GetWImage(QVector<imageInfo>& images){
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height >= 0.8
                && i->height / (float)i->height <= 1.2){
            QImage retImage(*i);
            std::swap(*i,*(images.end()-1);
            images.erase(images.end()-1);
            return retImage;
        }
    }
    return nullptr_t;
}
///
/// \brief jigsaw::jigsaw 构造函数
/// \param engine Qml引擎
///
jigsaw::jigsaw(QQmlApplicationEngine &engine){
    this->m_engine = &engine;
}
///
/// \brief jigsaw::splitImages 根据图像的宽高比例分出竖图、横图、方图，这里的比例为0.8
/// \param HImages 竖图Vector
/// \param WImages 横图Vector
/// \param MImages 方图Vector
///
void jigsaw::splitImages(QVector<imageInfo> &HImages, QVector<imageInfo> &WImages,
                         QVector<imageInfo> &MImages) const noexcept {
    for(auto image = this->imagesInfos.begin();image != this->imagesInfos.end();++image){
        if((float)image->height / (float)image->width < 0.8){
            WImages.append(*image);
        }else if((float)image->height / (float)image->width > 1.2){
            HImages.append(*image);
        }else{
            MImages.append(*image);
        }
    }
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
///
/// \brief jigsaw::popImage取消选择顺序为index的图片
/// \param index 第index张
///
void jigsaw::popImage(int index) {
    this->imagesInfos[index].choosen = false;
    qDebug() << index << " is poped";
}
///
/// \brief jigsaw::pushImage选择顺序为index的图片
/// \param index 第index张
///
void jigsaw::pushImage(int index) {
    this->imagesInfos[index].choosen = true;
}
///
/// \brief jigsaw::requestImageInfo 回应从qml发出的请求，该请求为获得第index张图片的信息
/// \param index 第index张
///
void jigsaw::requestImageInfo(int index) {
    auto image = &this->imagesInfos[index];
    emit returnImageInfo(index, image->width, image->height,
                         image->filesize,image->choosen,image->filepath);
}
///
/// \brief jigsaw::generate 生成最终拼图
/// \return 最终拼图的保存路径
///
QString jigsaw::generate(){
    QString tempPath = QDir::tempPath();
    QString imagePath = tempPath + "/AIONE_output.jpg";
    QImage finaImage(this->arg_width,this->arg_height,QImage::Format_RGB32);
    //根据宽高比分类图片
//    QVector<imageInfo> HImages, WImages, MImages;
//    splitImages(HImages, WImages, MImages);
//    qDebug() << "HImages.size(): " <<HImages.size();
//    qDebug() << "WImages.size(): " <<WImages.size();
//    qDebug() << "MImages.size(): " <<MImages.size();
    QVector<imageInfo> randomImages = this->imagesInfos;
    //随机打乱数组顺序
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(randomImages.begin(),randomImages.end(),std::default_random_engine(seed));





//    //TODO:拼图从下面开始
//    QImage image_a(randomImages[0].filepath);
//    QImage image_b(randomImages[1].filepath);
//    QPainter p(&finaImage);
//    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
//    auto qp = QPoint(0,0);
//    p.drawImage(qp, image_a);
//    p.drawImage(QPoint(600,0), image_b);
//    finaImage.save(imagePath);
    return imagePath;
}
///
/// \brief jigsaw::generateFinalImage 生成最终拼图
///
void jigsaw::generateFinalImage() {
    QString tempimagePath = this->generate();
    qDebug() << tempimagePath;
}







