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
