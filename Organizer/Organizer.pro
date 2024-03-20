QT       += core gui \
            sql \
            printsupport
RESOURCES += images.qrc \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    catalogtreeitem.cpp \
    main.cpp \
    catalogtile.cpp \
    globalsearch.cpp \
    notepad.cpp \
    passwordgenerator.cpp \
    mainwindow.cpp

HEADERS += \
    catalogtile.h \
    catalogtreeitem.h \
    globalsearch.h \
    notepad.h \
    passwordgenerator.h \
    mainwindow.h

FORMS += \
    catalogtile.ui \
    globalsearch.ui \
    notepad.ui \
    passwordgenerator.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target