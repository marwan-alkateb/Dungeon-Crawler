TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        List.cpp \
        armor.cpp \
        astaralgorithm.cpp \
        attackcontroller.cpp \
        character.cpp \
        consolecontroller.cpp \
        consumable.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        elixir.cpp \
        floor.cpp \
        guardcontroller.cpp \
        level.cpp \
        lever.cpp \
        list.cpp \
        logger.cpp \
        main.cpp \
        node.cpp \
        point.cpp \
        portal.cpp \
        potion.cpp \
        stationarycontroller.cpp \
        switch.cpp \
        tile.cpp \
        trap.cpp \
        userinterface.cpp \
        wall.cpp \
        weapon.cpp

HEADERS += \
    Controller.h \
    List.h \
    active.h \
    armor.h \
    asa.h \
    astaralgorithm.h \
    attackcontroller.h \
    character.h \
    consolecontroller.h \
    consumable.h \
    door.h \
    dungeoncrawler.h \
    elixir.h \
    floor.h \
    guardcontroller.h \
    item.h \
    level.h \
    lever.h \
    logger.h \
    node.h \
    passive.h \
    portal.h \
    potion.h \
    stationarycontroller.h \
    switch.h \
    tile.h \
    trap.h \
    userinterface.h \
    wall.h \
    weapon.h

unix:!macx: LIBS += -lncurses

DISTFILES += \
    3.map
