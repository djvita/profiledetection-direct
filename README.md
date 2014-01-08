profiledetection-direct
=======================

qt gui project of Profile Detection Project


    #Face Detection Based on Shervin Emami's git:             https://github.com/MasteringOpenCV/code/tree/master/Chapter8_FaceRecognition

    #A qtwidget project 

#install opencv 2.x.x in linux :

Download .zip at opencv.org

    extract and cd to the directory

    mkdir build

    cd build

    sudo apt-get install build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen2-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev

hours later...

    cmake -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..

hours later...

    make

hours later...

    sudo make install

Now you have OpenCV 2.x.x installed in your computer with C, C++, Python, TBB, OpenGL, Video, and Qt support.


then get qt creator...

just download at qt creator page and follow promts.

now download this repo...

in qt creator...

    File/Open File or Project...

open the .pro file

(note for ubuntu it should have these libs in the path:

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

)

You need webcam of course...check that ubuntu recognizes it as CAM0.

NOTE

#YOU NEED TO MODIFY THE DIRECTORY IN THE MAIN.CPP TO LOAD CASCADE FILES!

EXAMPLE

    const char *faceCascadeFilename = "/home/user/Documents/qtcreator-3.0.0/Projects/Profile_Detection_V5-QT/haarcascades/haarcascade_frontalface_alt2.xml";  // Haar face detector.

#change to the correct directory in your computer so that they load properly...


for windows refer to this:
http://docs.opencv.org/doc/tutorials/introduction/windows_install/windows_install.html
