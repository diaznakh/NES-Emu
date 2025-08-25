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
    # Linux - detect distribution
    ifeq ($(shell which dnf 2>/dev/null),/usr/bin/dnf)
        # Fedora/RHEL/CentOS
        CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I.
        LDFLAGS_OLC = -lGL -lGLU -lglut -lpng -lX11 -lpthread -lXrandr -lXinerama -lXcursor -ldl -lrt
    else ifeq ($(shell which apt-get 2>/dev/null),/usr/bin/apt-get)
        # Ubuntu/Debian
        CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I.
        LDFLAGS_OLC = -lGL -lGLU -lglut -lpng -lX11 -lpthread -lXrandr -lXinerama -lXcursor -ldl -lrt
    else
        # Generic Linux
        CXXFLAGS_OLC = -std=c++17 -Wall -Wextra -O2 -I.
        LDFLAGS_OLC = -lGL -lGLU -lglut -lpng -lX11 -lpthread -lXrandr -lXinerama -lXcursor -ldl -lrt
    endif
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
	@echo "Building OneLoneCoder version with flags: $(LDFLAGS_OLC)"
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

# Alternative Fedora packages (if the above doesn't work)
install-olc-fedora-alt:
	sudo dnf install libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel
	sudo dnf install libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel
	sudo dnf install libpng-devel freeglut-devel

# Check dependencies for OneLoneCoder version
check-olc-deps:
	@echo "Checking OneLoneCoder dependencies..."
	@echo "Platform: $(UNAME_S)"
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		echo "macOS detected"; \
	elif [ -f /etc/fedora-release ]; then \
		echo "Fedora detected"; \
		echo "Checking packages..."; \
		rpm -q libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel || echo "Missing packages. Run: make install-olc-fedora"; \
	elif [ -f /etc/debian_version ]; then \
		echo "Debian/Ubuntu detected"; \
		echo "Checking packages..."; \
		dpkg -l | grep -E "(libpng-dev|freeglut3-dev|libgl1-mesa-dev|libglu1-mesa-dev)" || echo "Missing packages. Run: make install-olc-ubuntu"; \
	else \
		echo "Unknown Linux distribution"; \
	fi

# Troubleshooting for Fedora
troubleshoot-fedora:
	@echo "=== Fedora Troubleshooting ==="
	@echo "1. Check if packages are installed:"
	@rpm -q libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel 2>/dev/null || echo "   Some packages missing"
	@echo ""
	@echo "2. Try alternative package names:"
	@echo "   sudo dnf install libpng-devel freeglut-devel mesa-libGL-devel mesa-libGLU-devel"
	@echo "   sudo dnf install libpng-devel freeglut-devel"
	@echo ""
	@echo "3. Check if libraries exist:"
	@ls -la /usr/lib64/libGL.so* 2>/dev/null || echo "   libGL not found"
	@ls -la /usr/lib64/libGLU.so* 2>/dev/null || echo "   libGLU not found"
	@ls -la /usr/lib64/libglut.so* 2>/dev/null || echo "   libglut not found"
	@echo ""
	@echo "4. If libraries exist but linking fails, try:"
	@echo "   export LD_LIBRARY_PATH=/usr/lib64:\$$LD_LIBRARY_PATH"

# Run with a ROM file (example)
run: $(TARGET)
	@echo "Usage: ./$(TARGET) <path-to-rom.nes>"
	@echo "Example: ./$(TARGET) tetris.nes"

# Run the OneLoneCoder version
run-olc: $(TARGET_OLC)
	./$(TARGET_OLC)

.PHONY: all clean install-sdl2-mac install-sdl2-ubuntu install-sdl2-fedora install-olc-mac install-olc-ubuntu install-olc-fedora install-olc-fedora-alt check-olc-deps troubleshoot-fedora run run-olc
