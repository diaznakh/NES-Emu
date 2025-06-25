CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2)
CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I. -I/opt/homebrew/include
LDFLAGS = $(shell pkg-config --libs sdl2)
LDFLAGS_OLC = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework AudioToolbox -L/opt/homebrew/lib -lpng -lglut

# Source files
SOURCES = main.cpp cpu.cpp
SOURCES_OLC = main_olc.cpp cpu.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_OLC = $(SOURCES_OLC:.cpp=.o)
TARGET = nes-emu
TARGET_OLC = nes-emu-olc

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Build the OneLoneCoder version
$(TARGET_OLC): $(OBJECTS_OLC)
	$(CXX) $(OBJECTS_OLC) -o $(TARGET_OLC) $(LDFLAGS_OLC)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile OneLoneCoder source files
main_olc.o: main_olc.cpp
	$(CXX) $(CXXFLAGS_OLC) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(OBJECTS_OLC) $(TARGET) $(TARGET_OLC)

# Install SDL2 (macOS)
install-sdl2-mac:
	brew install sdl2

# Install SDL2 (Ubuntu/Debian)
install-sdl2-ubuntu:
	sudo apt-get update
	sudo apt-get install libsdl2-dev

# Install SDL2 (Fedora)
install-sdl2-fedora:
	sudo dnf install SDL2-devel

# Run with a ROM file (example)
run: $(TARGET)
	@echo "Usage: ./$(TARGET) <path-to-rom.nes>"
	@echo "Example: ./$(TARGET) test.nes"

# Run the OneLoneCoder version
run-olc: $(TARGET_OLC)
	./$(TARGET_OLC)

.PHONY: all clean install-sdl2-mac install-sdl2-ubuntu install-sdl2-fedora run run-olc
