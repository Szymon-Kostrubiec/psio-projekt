TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio
LIBS += -lsfml-graphics
LIBS += -lsfml-network
LIBS += -lsfml-window
LIBS += -lsfml-system

SOURCES += \
        enemy.cpp \
        gamemaster.cpp \
        hero.cpp \
        main.cpp

HEADERS += \
    Text.hpp \
    enemy.hpp \
    enemybuilder.hpp \
    gameObject.hpp \
    gamemaster.hpp \
    globals.hpp \
    hero.hpp
