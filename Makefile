CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

TARGET = nes-emu
SOURCES = main.cpp cpu.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

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
	@echo "Example: ./$(TARGET) tetris.nes"

.PHONY: all clean install-sdl2-mac install-sdl2-ubuntu install-sdl2-fedora run
