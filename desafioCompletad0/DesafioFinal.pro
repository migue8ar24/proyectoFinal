QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 qobject

SOURCES += \
    Alcalde.cpp \
    Arma.cpp \
    BateDeBeisbol.cpp \
    Cuchillo.cpp \
    GordoTony.cpp \
    Homero.cpp \
    Homero2.cpp \
    Lvl1.cpp \
    Lvl2.cpp \
    Nerd.cpp \
    Personaje.cpp \
    Secuaz.cpp \
    Tenedor.cpp \
    main.cpp \
    puno.cpp

HEADERS += \
    Alcalde.h \
    Arma.h \
    BateDeBeisbol.h \
    Cuchillo.h \
    GordoTony.h \
    Homero.h \
    Homero2.h \
    Lvl1.h \
    Lvl2.h \
    Nerd.h \
    Personaje.h \
    Secuaz.h \
    Tenedor.h \
    puno.h

FORMS += \
    Lvl1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
