TEMPLATE = app
CONFIG += c++17
QT += core network

# Headers
HEADERS += \
    ../../inc/simple_server.hpp \
    ../../inc/event.hpp \
    ../../inc/logger.hpp \
    ../../inc/server_manager.hpp \
    ../../inc/pulse_event_handler.hpp \
    ../../inc/room_handler.hpp \
    ../../inc/event_handler_base.hpp \
    ../../inc/ai.hpp

# Sources
SOURCES += \
    ./main.cpp \
    ../../src/simple_server.cpp \
    ../../src/event.cpp \
    ../../src/server_manager.cpp \
    ../../src/pulse_event_handler.cpp \
    ../../src/room_handler.cpp \
    ../../src/logger.cpp \
    ../../src/event_handler_base.cpp \
    ../../src/ai.cpp

# Libraries
LIBS += -L/usr/lib/x86_64-linux-gnu/
INCLUDEPATH += ../../inc /usr/include/x86_64-linux-gnu/qt5/

# Python includes and libs
INCLUDEPATH += /usr/include/python3.8
LIBS += -L/usr/lib/python3.8/config-3.8-x86_64-linux-gnu -lpython3.8

# Additional flags
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-deprecated-copy
DEFINES += DEBUG