
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/maths.cpp \
    src/buffer.cpp \
    src/scanline.cpp \
    src/triangle.cpp \
    src/serializer.cpp \
    src/color.cpp \
    src/mesh.cpp \
    src/vertexprocessor.cpp \
    src/fragmentprocessor.cpp \
    src/fragmentprocessor.cpp \
    src/light.cpp

HEADERS += \
    src/maths.h \
    src/buffer.h \
    src/scanline.h \
    src/triangle.h \
    src/serializer.h \
    src/color.h \
    src/mesh.h \
    src/vertexprocessor.h \
    src/fragmentprocessor.h \
    src/light.h
