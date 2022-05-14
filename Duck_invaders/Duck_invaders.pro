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
        gamewindow.cpp \
        hero.cpp \
        main.cpp

HEADERS += \
    enemy.hpp \
    enemyspawner.hpp \
    gameObject.hpp \
    gamewindow.hpp \
    hero.hpp
