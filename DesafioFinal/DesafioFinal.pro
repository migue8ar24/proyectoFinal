QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Alcalde.cpp \
    Arma.cpp \
    BateDeBeisbol.cpp \
    Cuchillo.cpp \
    GordoTony.cpp \
    Homero.cpp \
    Juego.cpp \
    Nerd.cpp \
    Personaje.cpp \
    Piedra.cpp \
    Secuaz.cpp \
    Tenedor.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Alcalde.h \
    Arma.h \
    BateDeBeisbol.h \
    Cuchillo.h \
    GordoTony.h \
    Homero.h \
    Juego.h \
    Nerd.h \
    Personaje.h \
    Piedra.h \
    Secuaz.h \
    Tenedor.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
