#include "ppu.h"
#include <cstring>

void PPU2C02::reset() {
    control = 0x00;
    mask = 0x00;
    status = 0x00;
    oam_addr = 0x00;
    oam_data = 0x00;
    scroll = 0x00;
    ppu_addr = 0x00;
    ppu_data = 0x00;
    
    v = 0x0000;
    t = 0x0000;
    x = 0x00;
    w = false;
    
    // Initialize frame buffer
    frame.resize(256 * 240);
    std::fill(frame.begin(), frame.end(), 0xFF000000); // Black background
}

void PPU2C02::clock() {
    // Basic PPU clock implementation
    // This is a simplified version - in a real emulator, this would be much more complex
    
    static int scanline = 0;
    static int cycle = 0;
    
    cycle++;
    if (cycle >= 341) {
        cycle = 0;
        scanline++;
        if (scanline >= 262) {
            scanline = 0;
            // Frame complete
        }
    }
    
    // Simple pattern generation for testing
    if (scanline < 240 && cycle < 256) {
        int pixelIndex = scanline * 256 + cycle;
        uint8_t pattern = (cycle / 8) ^ (scanline / 8);
        frame[pixelIndex] = 0xFF000000 | (pattern << 16) | (pattern << 8) | pattern;
    }
}

bool PPU2C02::pollNMI() {
    // Check if NMI should be generated
    return false; // Simplified
}

uint8_t PPU2C02::cpuReadReg(uint16_t addr) {
    switch (addr & 0x0007) {
        case 0x0002: // PPUSTATUS
            w = false;
            return status;
        case 0x0004: // OAMDATA
            return oam_data;
        case 0x0007: // PPUDATA
            return ppu_data;
        default:
            return 0x00;
    }
}

void PPU2C02::cpuWriteReg(uint16_t addr, uint8_t data) {
    switch (addr & 0x0007) {
        case 0x0000: // PPUCTRL
            control = data;
            break;
        case 0x0001: // PPUMASK
            mask = data;
            break;
        case 0x0003: // OAMADDR
            oam_addr = data;
            break;
        case 0x0004: // OAMDATA
            oam_data = data;
            break;
        case 0x0005: // PPUSCROLL
            if (!w) {
                scroll = data;
            } else {
                // Fine X scroll
                x = data & 0x07;
            }
            w = !w;
            break;
        case 0x0006: // PPUADDR
            if (!w) {
                t = (t & 0x00FF) | ((data & 0x3F) << 8);
            } else {
                t = (t & 0xFF00) | data;
                v = t;
            }
            w = !w;
            break;
        case 0x0007: // PPUDATA
            ppu_data = data;
            break;
    }
}
