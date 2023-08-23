TEMPLATE = app
CONFIG += c++17
QT += core network

# Headers
HEADERS += \
    ../../inc/simple_server.hpp \
    ../../inc/server_manager.hpp

# Sources
SOURCES += \
    ./main.cpp \
    ../../src/simple_server.cpp \
    ../../src/server_manager.cpp

# Libraries
LIBS += -L/usr/lib/x86_64-linux-gnu/
INCLUDEPATH += ../../inc /usr/include/x86_64-linux-gnu/qt5/

# Additional flags
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-deprecated-copy
DEFINES += DEBUG
