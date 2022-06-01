QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lsfml-audio
LIBS += -lsfml-graphics
LIBS += -lsfml-network
LIBS += -lsfml-window
LIBS += -lsfml-system

SOURCES += \
    Game/enemy.cpp \
    Game/gameengine.cpp \
    Game/hero.cpp \
  Game/movement.cpp \
    Game/projectile.cpp \
    Game/texturemanager.cpp \
  Game/utility.cpp \
    characterchoice.cpp \
    creditswindow.cpp \
    displayplayer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Game/Text.hpp \
    Game/enemy.hpp \
    Game/gameObject.hpp \
    Game/gameengine.hpp \
    Game/hero.hpp \
  Game/loader.hpp \
  Game/movement.hpp \
    Game/projectile.hpp \
    Game/texturemanager.h \
    Game/utility.hpp \
    characterchoice.hpp \
    creditswindow.hpp \
    displayplayer.h \
    mainwindow.hpp

FORMS += \
    characterchoice.ui \
    creditswindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
