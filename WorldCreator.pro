#-------------------------------------------------
#
# Project created by QtCreator 2015-05-07T16:17:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    frame.cpp \
    game.cpp \
    inputmodule.cpp \
    sprite.cpp \
    state.cpp \
    bullet/bullet.cpp \
    character/character.cpp \
    character/player.cpp \
    effect/effect.cpp \
    manager/bulletmanager.cpp \
    manager/charactermanager.cpp \
    manager/effectmanager.cpp \
    manager/terrainmanager.cpp \
    skill/dead.cpp \
    skill/jump.cpp \
    skill/move.cpp \
    skill/restore.cpp \
    skill/shoot.cpp \
    skill/sit.cpp \
    skill/skill.cpp \
    terrain/terrain.cpp \
    world.cpp \
    decoration/decoration.cpp \
    manager/decorationmanager.cpp \
    manager/missionmanager.cpp \
    mission.cpp \
    manager/manager.cpp \
    spritepanel.cpp \
    worlddescriptiondialog.cpp \
    charactersettingdialog.cpp \
    terrainsettingdialog.cpp \
    decorationsettingdialog.cpp

HEADERS  += mainwindow.h \
    frame.h \
    game.h \
    inputmodule.h \
    singleton.h \
    sprite.h \
    state.h \
    bullet/bullet.h \
    character/character.h \
    character/player.h \
    effect/effect.h \
    manager/bulletmanager.h \
    manager/charactermanager.h \
    manager/effectmanager.h \
    manager/terrainmanager.h \
    skill/dead.h \
    skill/jump.h \
    skill/move.h \
    skill/restore.h \
    skill/shoot.h \
    skill/sit.h \
    skill/skill.h \
    terrain/terrain.h \
    world.h \
    decoration/decoration.h \
    manager/decorationmanager.h \
    manager/missionmanager.h \
    mission.h \
    manager/manager.h \
    spritepanel.h \
    worlddescriptiondialog.h \
    charactersettingdialog.h \
    terrainsettingdialog.h \
    decorationsettingdialog.h

FORMS    += mainwindow.ui \
    worlddescriptiondialog.ui \
    charactersettingdialog.ui \
    terrainsettingdialog.ui \
    decorationsettingdialog.ui

RESOURCES += \
    resource.qrc
