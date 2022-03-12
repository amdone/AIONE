QT += quick gui core

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#        imageslist.cpp \
        jigsaw.cpp \
        main.cpp \
        myimageprovider.cpp \
        opencv_image_opt.cpp \
        person.cpp \
        qmllanguage.cpp

RESOURCES += qml.qrc \
    images.qrc \
    translator.qrc

TRANSLATIONS += \
    zh_CN.ts \
    en_US.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AIONE_zh_CN.qm

HEADERS += \
#    imageslist.h \
    jigsaw.h \
    myimageprovider.h \
    opencv_image_opt.h \
    person.h \
    qmllanguage.h

INCLUDEPATH += F:/OpenCV/openCV_build/install/include \
               F:/OpenCV/openCV_build/install/include/opencv2

LIBS += F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_core420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_highgui420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_imgcodecs420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_imgproc420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_features2d420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_calib3d420.dll.a

