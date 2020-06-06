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
    consumable.cpp \
    data_processing.cpp \
    enemy_group.cpp \
    enemy_group_view.cpp \
    entity.cpp \
    equipment.cpp \
    equipment_management_interface.cpp \
    full_stats_display.cpp \
    group_status_panel.cpp \
    group_view.cpp \
    item.cpp \
    item_frame.cpp \
    item_storage.cpp \
    items_display.cpp \
    label_with_icon.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    npc.cpp \
    party.cpp \
    party_display.cpp \
    party_view.cpp \
    pc.cpp \
    pc_choice_panel.cpp \
    pc_equipment_display.cpp \
    skill.cpp \
    status_effect.cpp \
    switchable_frame.cpp \
    target_frame.cpp

HEADERS += \
    action.h \
    battleinterface.h \
    character.h \
    character_frame.h \
    character_status_panel.h \
    consumable.h \
    data_processing.h \
    enemy_group.h \
    enemy_group_view.h \
    entity.h \
    equipment.h \
    equipment_management_interface.h \
    full_stats_display.h \
    group_status_panel.h \
    group_view.h \
    item.h \
    item_frame.h \
    item_storage.h \
    items_display.h \
    label_with_icon.h \
    mainmenu.h \
    mainwindow.h \
    npc.h \
    party.h \
    party_display.h \
    party_view.h \
    pc.h \
    pc_choice_panel.h \
    pc_equipment_display.h \
    skill.h \
    status_effect.h \
    switchable_frame.h \
    target_frame.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
