# NES Emulator

A Nintendo Entertainment System (NES) emulator built with modern C++ featuring both SDL2 and OneLoneCoder's PixelGameEngine implementations.

## 🎮 Features

- **Complete NES Emulation**: CPU, PPU, and memory management
- **Dual Graphics Backends**: SDL2 (cross-platform) and OneLoneCoder's PixelGameEngine
- **OneLoneCoder's PPU Implementation**: Accurate background and sprite rendering
- **Advanced Debugging**: Real-time CPU status, palette viewer (OneLoneCoder version)
- **iNES Format Support**: Load and play NES ROM files
- **Multiple Mapper Support**: Mappers 000, 001, 002, 003, 004, 066
- **Clean Architecture**: Modular design with separate CPU, PPU, and Cartridge components

## 🏗️ Architecture

This emulator uses a clean, modular architecture:
- **CPU6502**: 6502 processor emulation
- **PPU2C02**: Picture Processing Unit with OneLoneCoder's rendering approach
- **Cartridge**: ROM loading and mapper support
- **SDL2**: Cross-platform graphics and input handling
- **OneLoneCoder PixelGameEngine**: Advanced graphics and debugging interface

## 📋 Prerequisites

### Required Libraries

#### macOS
```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required libraries
brew install sdl2
brew install libpng freeglut  # For OneLoneCoder version
```

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install libpng-dev freeglut3-dev  # For OneLoneCoder version
```

#### Fedora
```bash
sudo dnf install SDL2-devel
sudo dnf install libpng-devel freeglut-devel  # For OneLoneCoder version
```

#### Windows
- Install [SDL2](https://www.libsdl.org/download-2.0.php)
- Install [libpng](http://www.libpng.org/pub/png/libpng.html) (for OneLoneCoder version)
- Install [freeglut](http://freeglut.sourceforge.net/) (for OneLoneCoder version)

## 🚀 Building

### SDL2 Version (Recommended for all platforms)
```bash
# Build the SDL2 version
make clean
make

# Run with a ROM file
./nes-emu "path/to/your/game.nes"
```

### OneLoneCoder PixelGameEngine Version (Advanced debugging)
```bash
# Install OneLoneCoder dependencies first
make install-olc-mac      # macOS
make install-olc-ubuntu   # Ubuntu/Debian
make install-olc-fedora   # Fedora

# Build the OneLoneCoder version
make clean
make nes-emu-olc

# Run the OneLoneCoder version
./nes-emu-olc
```

## 🎮 Controls

### Game Controls (Both versions)
- **Arrow Keys**: Move/rotate pieces
- **X**: A Button (Jump/Rotate)
- **Z**: B Button (Run/Fire)
- **A**: Select
- **S**: Start
- **R**: Reset NES
- **P**: Cycle through palettes
- **Space**: Pause/Resume emulation

### Debug Controls (OneLoneCoder version only)
- **C**: Step by step execution
- **F**: Step one frame
- **Space**: Toggle continuous emulation

## 📁 Project Structure

```
NES-Emu/
├── cpu.h/cpp          # 6502 CPU implementation
├── ppu.h/cpp          # PPU with OneLoneCoder's approach
├── cartridge.h/cpp    # Cartridge and mapper support
├── main.cpp           # SDL2 version main file
├── main_olc.cpp       # OneLoneCoder version main file
├── Makefile           # Build configuration
├── olcPixelGameEngine.h  # OneLoneCoder's graphics engine
└── *.nes              # NES ROM files
```

## 🎯 Supported Games

The emulator supports games using the following mappers:
- **Mapper 000**: Simple games (Tetris, Super Mario Bros)
- **Mapper 001**: MMC1 (Super Mario Bros 3, Metroid)
- **Mapper 002**: UxROM (Castlevania, Contra)
- **Mapper 003**: CNROM (Donkey Kong Classics)
- **Mapper 004**: MMC3 (Super Mario Bros 2, Mega Man)
- **Mapper 066**: GxROM (Super Mario Bros + Duck Hunt)

## 🔧 Technical Details

### PPU Implementation
The PPU uses OneLoneCoder's exact approach for:
- Background tile fetching and rendering
- Sprite rendering with OAM
- Proper PPU timing (3 CPU cycles per PPU cycle)
- Palette management
- VRAM and nametable handling

### CPU Implementation
- Complete 6502 instruction set
- Proper cycle timing
- Interrupt handling (NMI, IRQ)
- Memory mapping

### Memory Management
- 2KB internal RAM
- 2KB VRAM
- 256-byte OAM
- 32-byte palette RAM
- Cartridge memory mapping

## 🐛 Known Issues

### macOS
- **SDL2 Version**: Works perfectly on all macOS versions
- **OneLoneCoder Version**: May have GLUT compatibility issues on newer macOS versions

### Windows
- Both versions should work correctly

### Linux
- Both versions should work correctly on Ubuntu, Debian, and Fedora

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🙏 Acknowledgments

### OneLoneCoder (David Barr)
This project is heavily inspired by and uses code from OneLoneCoder's NES emulator series:

- **YouTube Series**: [OneLoneCoder NES Emulator](https://www.youtube.com/playlist?list=PLrOv9FMX8xJHqMvSGB_9G9nZZ_4IgteYf)
- **GitHub**: [OneLoneCoder GitHub](https://github.com/OneLoneCoder)
- **Website**: [OneLoneCoder.com](https://www.onelonecoder.com)

**Key Contributions Used:**
- PPU rendering approach and timing
- PixelGameEngine graphics framework
- Debug interface design

### License (OLC-3)
```
Copyright 2018-2019 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions or derivations of source code must retain the above
copyright notice, this list of conditions and the following disclaimer.

2. Redistributions or derivative works in binary form must reproduce
the above copyright notice. This list of conditions and the following
disclaimer must be reproduced in the documentation and/or other
materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

### Other Libraries
- **SDL2**: Simple DirectMedia Layer for cross-platform graphics
- **libpng**: PNG image format support
- **freeglut**: OpenGL Utility Toolkit

## 📞 Support

If you encounter any issues:
1. Check the known issues section
2. Ensure all dependencies are installed
3. Try both SDL2 and OneLoneCoder versions
4. Open an issue on GitHub with detailed information

## 🎯 Roadmap

- [ ] Audio Processing Unit (APU) implementation
- [ ] Save state support
- [ ] More mapper support
- [ ] Network multiplayer
- [ ] GUI configuration
- [ ] Performance optimizations

---

**Note**: This emulator is for educational purposes. Please ensure you own the ROM files you use with this emulator.
