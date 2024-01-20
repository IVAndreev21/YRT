QT       += core gui uitools sql charts widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/addheir.cpp \
    src/calendarpopup.cpp \
    src/calendar.cpp \
    src/mainwindow.cpp \
    src/databasemanager.cpp \
    src/login.cpp \
    src/main.cpp \
    src/mainmenu.cpp \
    src/register.cpp \
    src/resetcredentials.cpp \
    src/termsandconditions.cpp

HEADERS += \
    src/addheir.h \
    src/calendarpopup.h \
    src/calendar.h \
    src/mainwindow.h \
    src/databasemanager.hpp \
    src/login.h \
    src/mainmenu.h \
    src/register.h \
    src/resetcredentials.h \
    src/termsandconditions.h

FORMS += \
    forms/addheir.ui \
    forms/calendarpopup.ui \
    forms/calendar.ui \
    forms/login.ui \
    forms/mainmenu.ui \
    forms/register.ui \
    forms/mainwindow.ui \
    forms/termsandconditions.ui \
    forms/resetcredentials.ui \
    forms/crypto.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
