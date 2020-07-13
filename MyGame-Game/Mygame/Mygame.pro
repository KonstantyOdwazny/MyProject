TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractwindow.cpp \
        collision.cpp \
        enemies.cpp \
        game.cpp \
        items.cpp \
        main.cpp \
        mapgame.cpp \
        menu.cpp \
        mycharacter.cpp \
        optionswindow.cpp \
        robotsbullet.cpp \
        sterowaniewindow.cpp \
        weapons.cpp \
        winwindow.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    abstractwindow.h \
    collision.h \
    enemies.h \
    game.h \
    items.h \
    mapgame.h \
    menu.h \
    mycharacter.h \
    optionswindow.h \
    robotsbullet.h \
    sterowaniewindow.h \
    weapons.h \
    winwindow.h
