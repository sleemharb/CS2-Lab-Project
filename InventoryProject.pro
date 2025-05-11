QT       += core gui
QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additem.cpp \
    adminwindow.cpp \
    employeewindow.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    managerwindow.cpp \
    search.cpp \
    signup.cpp \
    stock.cpp \
    user.cpp

HEADERS += \
    additem.h \
    adminwindow.h \
    employeewindow.h \
    login.h \
    mainwindow.h \
    managerwindow.h \
    search.h \
    signup.h \
    stock.h \
    user.h

FORMS += \
    additem.ui \
    adminwindow.ui \
    employeewindow.ui \
    login.ui \
    mainwindow.ui \
    managerwindow.ui \
    search.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
