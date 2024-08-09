QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Отключаем оптимизации компилятора
QMAKE_CXXFLAGS += -O0 -DGL_SILENCE_DEPRECATION
QMAKE_CFLAGS += -Wall -Wextra -Werror -std=gnu11
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main_window.cpp \
    transformations/transformations.c \
    parser/memory_manipulation.c \
    parser/parser.c \
    model.cpp \
    main.cpp \
    graphics.cpp

HEADERS += \
    main_window.h \
    transformations/transformations.h \
    parser/parser.h \
    common/common.h \
    model.h \
    graphics.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
