TEMPLATE = app
CONFIG += c++17
QT += core gui widgets network

# Headers
HEADERS += \
    ../../inc/client_TCP.hpp \
    ../../inc/client.hpp \
    ../../inc/ui.hpp \
    ../../inc/ui_main_window.hpp \
    ../../inc/ui_room_bt.hpp

# Sources
SOURCES += \
    ./main.cpp \
    ../../src/client_TCP.cpp \
    ../../src/client.cpp \
    ../../src/ui.cpp \
    ../../src/ui_main_window.cpp \
    ../../src/ui_room_bt.cpp

# Libraries
LIBS += -L/usr/lib/x86_64-linux-gnu/
INCLUDEPATH += ../../inc /usr/include/x86_64-linux-gnu/qt5/

# Additional flags
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wno-deprecated-copy
DEFINES += DEBUG
