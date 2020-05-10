QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    action.cpp \
    battleinterface.cpp \
    character.cpp \
    character_frame.cpp \
    character_status_panel.cpp \
    enemy_group.cpp \
    enemy_group_view.cpp \
    entity.cpp \
    group_status_panel.cpp \
    group_view.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    npc.cpp \
    party.cpp \
    party_view.cpp \
    pc.cpp \
    skill.cpp \
    switchable_frame.cpp

HEADERS += \
    action.h \
    battleinterface.h \
    character.h \
    character_frame.h \
    character_status_panel.h \
    enemy_group.h \
    enemy_group_view.h \
    entity.h \
    group_status_panel.h \
    group_view.h \
    mainmenu.h \
    mainwindow.h \
    npc.h \
    party.h \
    party_view.h \
    pc.h \
    skill.h \
    switchable_frame.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
