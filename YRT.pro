QT       += core gui uitools sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/databasemanager.cpp \
    src/login.cpp \
    src/main.cpp \
    src/mainmenu.cpp \
    src/register.cpp

HEADERS += \
    src/databasemanager.hpp \
    src/login.h \
    src/mainmenu.h \
    src/register.h

FORMS += \
    forms/login.ui \
    forms/mainmenu.ui \
    forms/register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
