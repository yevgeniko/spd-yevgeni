CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Wextra -fPIC
CXXFLAGS += -g3
CXXFLAGS += -std=c++17
CXXFLAGS += -Wno-deprecated-copy

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)
CPPFLAGS += -I/usr/include/x86_64-linux-gnu/qt5/
CPPFLAGS += -I/usr/include/x86_64-linux-gnu/qt5/QtCore/
CPPFLAGS += -I/usr/include/x86_64-linux-gnu/qt5/QtNetwork

LDFLAGS = -L/usr/lib/x86_64-linux-gnu/ -lQt5Core -lQt5Gui -lQt5Widgets -lQt5Network

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

SRC = main.cpp device_manager.cpp device.cpp event.cpp sensors.cpp
OBJS = $(SRC:.cpp=.o)
TARGET = qt_app

# Add a rule for moc compilation
MOC_SRC = $(shell find $(INCLUDES_DIR) -name "*.hpp" -print | grep -E 'Q_OBJECT')
MOC_OBJ = $(MOC_SRC:.hpp=.moc.o)

%.moc.cpp: %.hpp
	moc $< -o $@

%.moc.o: %.moc.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile rule
%.o: $(SOURCES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) ./$(TARGET) $(OBJS) $(MOC_OBJ) $(MOC_SRC:.h=.moc.cpp)

$(TARGET): $(OBJS) $(MOC_OBJ)
	$(CXX) $(OBJS) $(MOC_OBJ) $(LDFLAGS) -o $(TARGET)

.PHONY : make clean check
