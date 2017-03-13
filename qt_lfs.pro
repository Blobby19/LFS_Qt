#-------------------------------------------------
#
# Project created by QtCreator 2016-03-01T18:20:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_lfs
TEMPLATE = app


SOURCES += main.cpp\
        lfs.cpp \
    udpsocket.cpp \
    joycontrol.cpp

HEADERS  += lfs.h \
    udpsocket.h \
    lfs_track_data.h \
    inc/public.h \
    inc/vjoyinterface.h \
    joycontrol.h \
    InSim.h \
    lfs_data.h

FORMS    += lfs.ui \
    joycontrol.ui

DISTFILES += \
    turn_signal_indicator.png \
    warn_abs.png \

RESOURCES += \
    images.qrc \
    tracks.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lvJoyInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lvJoyInterface

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
