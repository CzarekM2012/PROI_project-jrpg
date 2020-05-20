TEMPLATE = app
TARGET = jrpg_dialogs

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    bglabel.cpp \
    dialog_window.cpp \
    main.cpp \
    maplabel.cpp \
    maptile.cpp

HEADERS += \
    bglabel.h \
    dialog_window.h \
    maplabel.h \
    maptile.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
