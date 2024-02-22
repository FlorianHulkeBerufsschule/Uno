QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamefield.cpp \
    main.cpp \
    server.cpp

HEADERS += \
    gamefield.h \
    server.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Shared/release/ -lShared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Shared/debug/ -lShared
else:unix: LIBS += -L$$OUT_PWD/../Shared/ -lShared

INCLUDEPATH += $$PWD/../Shared
DEPENDPATH += $$PWD/../Shared
