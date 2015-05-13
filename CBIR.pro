#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T15:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CBIR
TEMPLATE = app

SOURCES += main.cpp\
        cbir.cpp \
    Similarity.cpp \
    ShapeFeature.cpp \
    Searcher.cpp \
    methods.cpp \
    ImageLib.cpp \
    Image.cpp \
    Histogram.cpp \
    Feature.cpp \
    ColorFeature.cpp

HEADERS  += cbir.h \
    ColorFeature.h \
    Feature.h \
    Histogram.h \
    Image.h \
    ImageLib.h \
    methods.h \
    Searcher.h \
    ShapeFeature.h \
    Similarity.h

FORMS    += cbir.ui

INCLUDEPATH += D:/OpenCV/build/include

win32:CONFIG(debug, debug|release): {
LIBS += -LD:/OpenCV/build/x64/vc11/lib \
-lopencv_core249d \
-lopencv_imgproc249d \
-lopencv_highgui249d \
-lopencv_ml249d \
-lopencv_video249d \
-lopencv_features2d249d \
-lopencv_calib3d249d \
-lopencv_objdetect249d \
-lopencv_contrib249d \
-lopencv_legacy249d \
-lopencv_flann249d
}else:win32:CONFIG(release, debug|release): {
LIBS += -LD:/OpenCV/build/x64/vc11/lib \
-lopencv_core249 \
-lopencv_imgproc249 \
-lopencv_highgui249 \
-lopencv_ml249 \
-lopencv_video249 \
-lopencv_features2d249 \
-lopencv_calib3d249 \
-lopencv_objdetect249 \
-lopencv_contrib249 \
-lopencv_legacy249 \
-lopencv_flann249
}
