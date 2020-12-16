TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt
QT     += core gui
QT     += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS += circuit-logo.ico

SOURCES += \
    capacitor.cpp \
    component.cpp \
    endcomponent.cpp \
    gnd.cpp \
    graphicsview.cpp \
    logicblock.cpp \
    main.cpp \
    mainwindow.cpp \
    netlabel.cpp \
    notgate.cpp \
    resistor.cpp \
    serialcomponent.cpp \
    textdialog.cpp \
    twoinputandgate.cpp \
    twoinputgate.cpp \
    twoinputnandgate.cpp \
    twoinputnorgate.cpp \
    twoinputorgate.cpp \
    twoinputxorgate.cpp

HEADERS += \
    capacitor.h \
    component.h \
    endcomponent.h \
    gnd.h \
    graphicsview.h \
    logicblock.h \
    mainwindow.h \
    netlabel.h \
    notgate.h \
    resistor.h \
    serialcomponent.h \
    textdialog.h \
    twoinputandgate.h \
    twoinputgate.h \
    twoinputnandgate.h \
    twoinputnorgate.h \
    twoinputorgate.h \
    twoinputxorgate.h \
    vector.h

FORMS += \
    mainwindow.ui \
    textdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
