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

.PHONY: all clean install-sdl2-mac
