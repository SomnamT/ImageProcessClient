QT       += core gui multimedia widgets multimediawidgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cvkits.cpp \
    main.cpp \
    mainwindow.cpp \
    receivedialog.cpp \
    tempmanager.cpp \

HEADERS += \
    config.h \
    cvkits.h \
    mainwindow.h \
    receivedialog.h \
    tempmanager.h \
    ucsbengine/UCSBEngine_global.h \
    ucsbengine/clientservicemanager.h \
    ucsbengine/clientservicemanagerfactory.h \
    ucsbengine/logger.h

FORMS += \
    mainwindow.ui \
    receivedialog.ui

TRANSLATIONS += \
    image-processing-client_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

win32 {
    # TODO: 添加 Win32 OpenCV 依赖
    INCLUDEPATH += "C:/Program Files/OpenCV/opencv/build/include"
    INCLUDEPATH += "C:/Program Files/OpenCV/opencv/build/include/opencv2"
    LIBS += "C:/Program Files/OpenCV/opencv/build/x64/vc15/lib/opencv_world455d.lib"
}


unix {
    # ARM Homebrew 的安装路径
    INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.5.5_2/include/opencv4/opencv2/
    INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.5.5_2/include/
    INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.5.5_2/include/opencv4/

    LIBS += /opt/homebrew/Cellar/opencv/4.5.5_2/lib/libopencv_*


    # Intel Homebrew 的安装路径
#    INCLUDEPATH += /usr/local/include
#    INCLUDEPATH += /usr/local/include/opencv
#    INCLUDEPATH += /usr/local/include/opencv2

#    LIBS += /usr/local/lib/libopencv_*
}

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ucsbengine/ -lUCSBEngine
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ucsbengine/ -lUCSBEngined
#else:unix: LIBS += -L$$PWD/ucsbengine/ -lUCSBEngine

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ucsbengine/build-ucsbengine-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/release/ -lucsbengine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ucsbengine/build-ucsbengine-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/debug/ -lucsbengine
else:unix: LIBS += -L$$PWD/../../ucsbengine/build-ucsbengine-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/ -lucsbengine

INCLUDEPATH += $$PWD/../../ucsbengine/build-ucsbengine-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/debug
DEPENDPATH += $$PWD/../../ucsbengine/build-ucsbengine-Desktop_Qt_5_9_0_MSVC2017_64bit-Debug/debug

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
