QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Publisher.cpp \
    addbook.cpp \
    dboperator.cpp \
    homepage.cpp \
    idmanage.cpp \
    main.cpp \
    mainwindow.cpp \
    readerpage.cpp \
    regist.cpp \
    regist_reader.cpp

HEADERS += \
    Publisher.h \
    addbook.h \
    dboperator.h \
    homepage.h \
    idmanage.h \
    mainwindow.h \
    readerpage.h \
    regist.h \
    regist_reader.h

FORMS += \
    Publisher.ui \
    addbook.ui \
    homepage.ui \
    idmanage.ui \
    mainwindow.ui \
    readerpage.ui \
    regist.ui \
    regist_reader.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc

DISTFILES +=
