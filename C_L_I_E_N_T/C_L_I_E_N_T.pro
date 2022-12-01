QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accept_file.cpp \
    change_ava.cpp \
    host.cpp \
    images.cpp \
    info.cpp \
    main.cpp \
    mainwindow.cpp \
    nickname.cpp \
    others_info.cpp \
    save_as.cpp \
    status_buttom.cpp

HEADERS += \
    accept_file.h \
    change_ava.h \
    host.h \
    images.h \
    info.h \
    mainwindow.h \
    nickname.h \
    others_info.h \
    save_as.h \
    status_buttom.h

FORMS += \
    accept_file.ui \
    change_ava.ui \
    host.ui \
    images.ui \
    info.ui \
    mainwindow.ui \
    nickname.ui \
    others_info.ui \
    save_as.ui \
    status_buttom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
