QT -= gui

TEMPLATE = lib
DEFINES += SHARED_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    unocard.cpp \
    unocardbase.cpp \
    unospecialcard.cpp

HEADERS += \
    Shared_global.h \
    clientaction.h \
    serveraction.h \
    unocard.h \
    unocardbase.h \
    unocardcolor.h \
    unospecialcard.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
