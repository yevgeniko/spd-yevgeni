TEMPLATE = app
CONFIG += c++17
QT += core gui widgets network

# Headers
HEADERS += \
    ../../inc/device_manager.hpp \
    ../../inc/device.hpp \
    ../../inc/event.hpp \
    ../../inc/sensors.hpp

# Sources
SOURCES += \
    ./main.cpp \
    ../../src/device_manager.cpp \
    ../../src/device.cpp \
    ../../src/event.cpp \
    ../../src/sensors.cpp

# Libraries
LIBS += -L/usr/lib/x86_64-linux-gnu/
INCLUDEPATH += ../../inc /usr/include/x86_64-linux-gnu/qt5/

# Additional flags
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-deprecated-copy
DEFINES += DEBUG
