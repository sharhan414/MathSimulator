QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

win32: RC_ICONS = $$PWD/images/Icon_1.ico

TARGET= Test-Simulator

SOURCES += \
    itemarithsign.cpp \
    itembaseobjects.cpp \
    itemnum.cpp \
    itemviewanswer.cpp \
    main.cpp \
    mainwindow.cpp \
    scene.cpp \
    startscene.cpp\
    alldates.cpp\
    simulator.cpp \
    testendscene.cpp

HEADERS += \
    itemarithsign.h \
    itembaseobjects.h \
    itemnum.h \
    itemviewanswer.h \
    mainwindow.h \
    scene.h \
    startscene.h\
    alldates.h\
    simulator.h \
    testendscene.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resurses.qrc
