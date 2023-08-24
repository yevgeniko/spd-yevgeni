TEMPLATE = app
CONFIG += c++17
QT += core gui widgets network

# Headers
HEADERS += \
    ../../inc/agent_manager.hpp \
    ../../inc/device_config.hpp \
    ../../inc/agent.hpp \
    ../../inc/logger.hpp

# Sources
SOURCES += \
    ./server-utest.cpp \
    ../../src/agent_manager.cpp \
    ../../src/device_config.cpp \
    ../../src/agent.cpp \
    ../../src/logger.cpp

# Libraries
LIBS += -L/usr/lib/x86_64-linux-gnu/
INCLUDEPATH += ../../inc /usr/include/x86_64-linux-gnu/qt5/

# Additional flags
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-deprecated-copy -g3
DEFINES += DEBUG
