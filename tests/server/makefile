CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Wextra -fPIC
CXXFLAGS += -g3
CXXFLAGS += -std=c++17
CXXFLAGS += -Wno-deprecated-copy

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)
CPPFLAGS += -I/usr/include/x86_64-linux-gnu/qt5/

# Adjust the LDFLAGS
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/ -lQt5Core -lQt5Gui -lQt5Widgets

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = server-utest.o $(SOURCES_DIR)/server.o $(SOURCES_DIR)/device_config.o
TARGET = qt_app

# Add a rule for moc compilation
MOC_SRC = $(shell find $(INCLUDES_DIR) -name "*.h" -print | grep -E 'Q_OBJECT')
MOC_OBJ = $(MOC_SRC:.h=.moc.o)

%.moc.cpp: %.h
	moc $< -o $@

%.moc.o: %.moc.cpp
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
