QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libssh-0.10.5/build/lib/release/ -lssh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libssh-0.10.5/build/lib/debug/ -lssh
else:unix: LIBS += -L$$PWD/libssh-0.10.5/build/lib/ -lssh

INCLUDEPATH += $$PWD/libssh-0.10.5/build/include
DEPENDPATH += $$PWD/libssh-0.10.5/build/include
#ssh/libssh-0.10.5/include/libssh

#INCLUDEPATH += $$PWD/libssh-0.10.5/include
#DEPENDPATH += $$PWD/libssh-0.10.5/include
