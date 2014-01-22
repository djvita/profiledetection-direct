#-------------------------------------------------
#
# Project created by QtCreator 2014-01-07T19:38:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = profiledetection-direct
TEMPLATE = app

HEADERS  += mainwindow.h \
    detectobject.h \
    preprocessface.h \
    recognition.h \
    ImageUtils.h

SOURCES += main.cpp\
        mainwindow.cpp \
    detectobject.cpp \
    preprocessface.cpp \
    recognition.cpp \
    ImageUtils_0.7.cpp



FORMS    += mainwindow.ui

# OpenCv Configuration
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree
LIBS += `pkg-config opencv --libs`

#LIBS += /home/vita/Documents/qtcreator3/projects/build-profiledetection-direct-Clone_of_Desktop-Debug/recognition.o

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/release/ -lopencv_photo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/debug/ -lopencv_photo
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lopencv_photo

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/release/ -lopencv_videostab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/debug/ -lopencv_videostab
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lopencv_videostab

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include
