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
/// \brief GetRectBreak 将一个矩形随机一分为二成两个矩形
/// \param src 源矩形
/// \param drift 控制随机程度
/// \return 一个存有两个QRect的元组
///
std::tuple<QRect, QRect> GetRectBreak(QRect src, double drift){
    int start = 0;
    //TODO: 优化随机生成器的效率
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine random_engine(seed);
    std::bernoulli_distribution u;
    if(u(random_engine)){
        int w = src.width();
        int drift_w = (int)(double(w) * drift / 2.0);
        int drift_s = src.left() + w/2 - drift_w;
        int drift_e = src.right() - w/2 + drift_w;
        if(drift_e - drift_s < 0){
            start = src.left() + src.width()/2;
        }else{
            std::uniform_int_distribution<int> u2(drift_s, drift_e);
            start = src.left() + u2(random_engine);
        }
        QRect left_area(src.topLeft(), QPoint(start,src.bottom()));
        QRect right_area(QPoint(start + 1, src.top()), src.bottomRight());
        if(u(random_engine)){
            left_area.setRight(start + 1);
            right_area.setLeft(start);
        }
        std::tuple<QRect,QRect> ret(left_area, right_area);
        return ret;
    }else{
        int h = src.height();
        int drift_h = (int)(double(h) * drift / 2.0);
        int drift_s = src.top() + h/2 - drift_h;
        int drift_e = src.bottom() - h/2 + drift_h;
        if( drift_e - drift_s < 0){
            start = src.top() + src.height()/2;
        }else{
            std::uniform_int_distribution<int> u2(drift_s, drift_e);
            start = src.top() + u2(random_engine);
        }
        QRect top_rect(src.topLeft(), QPoint(src.right(), start));
        QRect bottom_rect(QPoint(src.left(), start + 1), src.bottomRight());
        if(u(random_engine)){
            top_rect.setBottom(start + 1);
            bottom_rect.setTop(start);
        }
        std::tuple<QRect,QRect> ret(top_rect, bottom_rect);
        return ret;
    }
}
///
/// \brief GetRatio 获得矩形的宽高比
/// \param rect 矩形
/// \return double
///
double GetRatio(QRect& rect) {
    return (double)rect.width() / (double)rect.height();
}
///
/// \brief isDeformedRect 是不是畸形矩形，也就是说这个矩形过于扁，或者过于长
/// \param rect 矩形
/// \return true=>畸形, false=>正常
///
bool isDeformedRect(QRect& rect) {
    return GetRatio(rect) > 2.5 || GetRatio(rect) < 0.2;
}
///
/// \brief jigsaw::GetRondomIndexFromRects 从当前rects中随即返回一个矩形
/// \return
///
int jigsaw::GetRondomIndexFromRects(){
    //TODO: 优化随机生成器的效率
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine random_engine(seed);
    std::uniform_int_distribution<unsigned> u(0, this->rects.size()-1);
    return u(random_engine);
}
///
/// \brief GetHImage 从给定的一组图片中弹出一张竖图
/// \param images
/// \return QImage
///
QImage jigsaw::GetHImage(QVector<imageInfo>& images){
    if(images.size() == 0){
        images = this->imagesInfos;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(images.begin(),images.end(),std::default_random_engine(seed));
    }
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height > 1.2){
            QImage retImage(i->filepath);
            std::swap(*i,*(images.end()-1));
            images.erase(images.end()-1);
            return retImage;
        }
    }
    return this->GetMImage(images);
}
///
/// \brief GetHImage 从给定的一组图片中弹出一张横图
/// \param images
/// \return QImage
///
QImage jigsaw::GetWImage(QVector<imageInfo>& images){
    if(images.size() == 0){
        images = this->imagesInfos;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(images.begin(),images.end(),std::default_random_engine(seed));
    }
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height < 0.8){
            QImage retImage(i->filepath);
            std::swap(*i,*(images.end()-1));
            images.erase(images.end()-1);
            return retImage;
        }
    }
    return this->GetMImage(images);
}
///
/// \brief GetHImage 从给定的一组图片中弹出一张方图
/// \param images
/// \return QImage
///
QImage jigsaw::GetMImage(QVector<imageInfo>& images){
    if(images.size() == 0){
        images = this->imagesInfos;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(images.begin(),images.end(),std::default_random_engine(seed));
    }
    for(auto i=images.begin();i!=images.end();++i){
        if(i->height / (float)i->height >= 0.8
                && i->height / (float)i->height <= 1.2){
            QImage retImage(i->filepath);
            std::swap(*i,*(images.end()-1));
            images.erase(images.end()-1);
            return retImage;
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine random_engine(seed);
    std::bernoulli_distribution u;
    if(u(random_engine)){ //获得随机bool值
        return this->GetHImage(images);
    }else{
        return this->GetWImage(images);
    }

}
///
/// \brief jigsaw::jigsaw 构造函数
/// \param engine Qml引擎
///
jigsaw::jigsaw(QQmlApplicationEngine &engine){
    this->m_engine = &engine;
    //this->seed = std::chrono::system_clock::now().time_since_epoch().count();
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
    if(this->nums<2){
        //TODO: 图片数量太少怎么办
        qDebug()<< "too little images";
    }
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
    RectsInit();
    QPainter painter(&finaImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    for(QRect rect : this->rects){
        if(GetRatio(rect) > 1.2){
            auto image = GetWImage(randomImages);
            painter.drawImage(rect, image);
        }else if(GetRatio(rect) < 0.8){
            auto image = GetHImage(randomImages);
            painter.drawImage(rect, image);
        }else{
            auto image = GetMImage(randomImages);
            painter.drawImage(rect, image);
        }
    }
    finaImage.save(imagePath);
    return imagePath;
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
/// \brief jigsaw::RectsInit 根据当前参数初始化拼图框
///
void jigsaw::RectsInit() {
    this->rects.clear();
    QRect initRect = QRect(0,0,this->arg_width,this->arg_height);
    this->rects.append(initRect);
    int randint;
    int run_count = 0;
    int method = 0;
    while(1){
        ++run_count;
        if(run_count > this->nums*2) {
            return;
        }
        if(this->rects.size() >= this->arg_nums) {
            return;
        } else {
            if(method == 3){
                randint = GetRondomIndexFromRects();
                method = 0;
            } else {
                if(this->rects.size()%3 == 0){
                    randint = this->GetMaxRectIndex();
                    method = 1;
                } else {
                    randint = GetRondomIndexFromRects();
                    method = 0;
                }
            }
            QRect curRect = this->rects[randint];
            std::tuple<QRect, QRect> rectBreak = GetRectBreak(curRect, this->arg_offset);
            QRect l = std::get<0>(rectBreak);
            QRect r = std::get<1>(rectBreak);
            if(isDeformedRect(l) || isDeformedRect(r)){
                if(method == 1){
                    method = 3;
                }
                continue;
            }
            this->rects.erase(this->rects.begin()+randint);
            this->rects.append(l);
            this->rects.append(r);
        }
    }
}
///
/// \brief jigsaw::GetMaxRectIndex
/// \return
///
int jigsaw::GetMaxRectIndex(){
    int index = 0;
    int maxArea = this->rects[0].width() * this->rects[0].height();
    for (int i = 1; i < this->nums; ++i) {
        if(this->rects[i].width()*this->rects[i].height()>maxArea)
            index = i;
    }
    return index;
}
///
/// \brief jigsaw::generateFinalImage 生成最终拼图
///
void jigsaw::generateFinalImage() {
    QString tempimagePath = this->generate();
    qDebug() << tempimagePath;
}







