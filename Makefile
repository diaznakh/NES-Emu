CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

# Platform detection for OneLoneCoder version
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS
    CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I. -I/opt/homebrew/include
    LDFLAGS_OLC = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework AudioToolbox -L/opt/homebrew/lib -lpng -lglut
else
    # Linux and other platforms
    CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I.
    LDFLAGS_OLC = -lGL -lGLU -lglut -lpng -lX11 -lpthread -lXrandr -lXinerama -lXcursor -ldl -lrt
endif

# SDL2 Version
TARGET = nes-emu
SOURCES = main.cpp cpu.cpp ppu.cpp cartridge.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# OneLoneCoder Version
TARGET_OLC = nes-emu-olc
SOURCES_OLC = main_olc.cpp cpu.cpp ppu.cpp cartridge.cpp
OBJECTS_OLC = $(SOURCES_OLC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(TARGET_OLC): $(OBJECTS_OLC)
	$(CXX) $(OBJECTS_OLC) -o $(TARGET_OLC) $(LDFLAGS_OLC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main_olc.o: main_olc.cpp
	$(CXX) $(CXXFLAGS_OLC) -c $< -o $@

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

# Install OneLoneCoder dependencies (macOS)
install-olc-mac:
	brew install libpng freeglut

# Install OneLoneCoder dependencies (Ubuntu/Debian)
install-olc-ubuntu:
	sudo apt-get update
	sudo apt-get install libpng-dev freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev

# Install OneLoneCoder dependencies (Fedora)
install-olc-fedora:
	sudo dnf install libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel libXrandr-devel libXinerama-devel libXcursor-devel

# Run with a ROM file (example)
run: $(TARGET)
	@echo "Usage: ./$(TARGET) <path-to-rom.nes>"
	@echo "Example: ./$(TARGET) tetris.nes"

# Run the OneLoneCoder version
run-olc: $(TARGET_OLC)
	./$(TARGET_OLC)

.PHONY: all clean install-sdl2-mac install-sdl2-ubuntu install-sdl2-fedora install-olc-mac install-olc-ubuntu install-olc-fedora run run-olc
