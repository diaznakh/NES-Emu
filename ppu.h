#pragma once
#include <cstdint>
#include <vector>

class PPU2C02 {
public:
    // PPU registers
    uint8_t control = 0x00;
    uint8_t mask = 0x00;
    uint8_t status = 0x00;
    uint8_t oam_addr = 0x00;
    uint8_t oam_data = 0x00;
    uint8_t scroll = 0x00;
    uint8_t ppu_addr = 0x00;
    uint8_t ppu_data = 0x00;
    
    // Internal state
    uint16_t v = 0x0000;  // Current VRAM address
    uint16_t t = 0x0000;  // Temporary VRAM address
    uint8_t x = 0x00;     // Fine X scroll
    bool w = false;       // Write toggle
    
    // Frame buffer
    std::vector<uint32_t> frame;
    
    // Methods
    void clock();
    void reset();
    bool pollNMI();
    
    // Register access
    uint8_t cpuReadReg(uint16_t addr);
    void cpuWriteReg(uint16_t addr, uint8_t data);
};
