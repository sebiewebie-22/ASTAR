QT       += core gui
 QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AutoPlay.cpp \
    ControlMode.cpp \
    Controller.cpp \
    EnemyView.cpp \
    EnemyViewText.cpp \
    HealthPackView.cpp \
    HealthPackViewText.cpp \
    Initialization.cpp \
    Manual.cpp \
    Model.cpp \
    PathFinder.cpp \
    ProtagonistView.cpp \
    ProtagonistViewText.cpp \
    TextView.cpp \
    GraphicalView.cpp \
    astar.cpp \
    main.cpp \
    Mainwindow.cpp \
    View.cpp \
    XEnemy.cpp \
    node.cpp

HEADERS += \
    AutoPlay.h \
    ControlMode.h \
    Controller.h \
    EnemyView.h \
    EnemyViewText.h \
    HealthPackView.h \
    HealthPackViewText.h \
    Initialization.h \
    Manual.h \
    Model.h \
    PathFinder.h \
    ProtagonistView.h \
    ProtagonistViewText.h \
    TextView.h \
    GraphicalView.h \
    Mainwindow.h \
    View.h \
    XEnemy.h \
    astar.h \
    node.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/libworld/lib/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/libworld/lib/ -lworld
else:unix: LIBS += -L$$PWD/lib/libworld/lib/ -lworld

INCLUDEPATH += $$PWD/lib/libworld/include/
DEPENDPATH += $$PWD/lib/libworld/include/

RESOURCES += \
    worldImages/imageResource.qrc
