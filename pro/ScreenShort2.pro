QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DESTDIR = ../bin
INCLUDEPATH += ../inc\

SOURCES += ../src/main.cpp\
        ../src/mainwindow.cpp\
        ../src/hook.cpp\
        ../src/loadprog.cpp
HEADERS  += ../inc/mainwindow.h\
            ../inc/hook.h\
            ../inc/loadprog.h\

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res/png.qrc

#程序版本
VERSION = 1.0.0
#程序图标
RC_ICONS = ../res/icon.ico
#程序说明
QMAKE_TARGET_DESCRIPTION = "Screen Short Tool"
#版权信息
QMAKE_TARGET_COPYRIGHT = "Copyright(C) 2024-06-16"
#程序名称
QMAKE_TARGET_PRODUCT = "ScreenShort"
#程序语言
#0x0800代表和系统当前语言一致
RC_LANG = 0x0800

