TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        collision.cpp \
        enemies.cpp \
        game.cpp \
        items.cpp \
        main.cpp \
        mapgame.cpp \
        mycharacter.cpp \
        weapons.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    collision.h \
    enemies.h \
    game.h \
    items.h \
    mapgame.h \
    mycharacter.h \
    weapons.h
