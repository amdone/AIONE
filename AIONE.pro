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

RC_ICONS = aione.ico

SOURCES += \
        Sources/jigsaw.cpp \
        Sources/main.cpp \
        Sources/myimageprovider.cpp \
        Sources/opencv_image_opt.cpp \
        Sources/person.cpp \
        Sources/qmllanguage.cpp

RESOURCES += qml.qrc \
    images.qrc \
    translator.qrc

TRANSLATIONS += \
    Others/zh_CN.ts \
    Others/en_US.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AIONE_zh_CN.qm \
    Others/en_US.ts \
    Others/zh_CN.ts \
    icons/folderOpen_black.svg \
    icons/folderOpen_gray.svg \
    icons/refresh_black.svg \
    icons/refresh_green.svg \
    qmls/JigsawWindow.qml \
    qmls/LittleImage.qml \
    qmls/SkinDialog.qml \
    qmls/Viewer.qml \
    qmls/main.qml \
    translators/en_US.qm \
    translators/zh_CN.qm

HEADERS += \
    Headers/jigsaw.h \
    Headers/myimageprovider.h \
    Headers/opencv_image_opt.h \
    Headers/person.h \
    Headers/qmllanguage.h \

INCLUDEPATH += F:/OpenCV/openCV_build/install/include \
               F:/OpenCV/openCV_build/install/include/opencv2 \
               Headers \

LIBS += F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_core420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_highgui420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_imgcodecs420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_imgproc420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_features2d420.dll.a \
        F:/OpenCV/openCV_build/install/x64/mingw/lib/libopencv_calib3d420.dll.a

