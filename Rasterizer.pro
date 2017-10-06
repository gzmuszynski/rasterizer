TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/buffer.cpp \
    src/scanline.cpp \
    src/triangle.cpp \
    src/serializer.cpp

HEADERS += \
    src/buffer.h \
    src/scanline.h \
    src/triangle.h \
    src/serializer.h
