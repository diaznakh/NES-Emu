#pragma once
#include <cstdint>
#include <vector>
#include <string>

class Cartridge {
public:
    Cartridge() = default;
    ~Cartridge() = default;
    
    // ROM data
    std::vector<uint8_t> prgROM;
    std::vector<uint8_t> chrROM;
    
    // Header information
    uint8_t mapperNumber = 0;
    uint8_t prgBanks = 0;
    uint8_t chrBanks = 0;
    bool mirroringVertical = false;
    bool hasTrainer = false;
    
    // Methods
    bool loadINES(const std::string& filename);
    uint8_t cpuRead(uint16_t addr);
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t ppuRead(uint16_t addr);
    void ppuWrite(uint16_t addr, uint8_t data);
};
