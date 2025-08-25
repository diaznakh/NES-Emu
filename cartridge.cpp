#include "cartridge.h"
#include <fstream>
#include <iostream>

bool Cartridge::loadINES(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Failed to open ROM file: " << filename << std::endl;
        return false;
    }

    // Read iNES header (16 bytes)
    uint8_t header[16];
    file.read(reinterpret_cast<char*>(header), 16);

    // Check iNES signature
    if (header[0] != 'N' || header[1] != 'E' || header[2] != 'S' || header[3] != 0x1A) {
        std::cout << "Invalid iNES file format" << std::endl;
        return false;
    }

    // Parse header
    prgBanks = header[4];
    chrBanks = header[5];
    mapperNumber = (header[6] >> 4) | (header[7] & 0xF0);
    mirroringVertical = (header[6] & 0x01);
    hasTrainer = (header[6] & 0x04);

    std::cout << "Mapper: " << (int)mapperNumber << std::endl;
    std::cout << "PRG ROM: " << (int)prgBanks << " banks" << std::endl;
    std::cout << "CHR ROM: " << (int)chrBanks << " banks" << std::endl;

    // Skip trainer if present
    if (hasTrainer) {
        file.seekg(512, std::ios::cur);
    }

    // Read PRG ROM
    size_t prgSize = prgBanks * 16384;
    prgROM.resize(prgSize);
    file.read(reinterpret_cast<char*>(prgROM.data()), prgSize);

    // Read CHR ROM
    size_t chrSize = chrBanks * 8192;
    chrROM.resize(chrSize);
    file.read(reinterpret_cast<char*>(chrROM.data()), chrSize);

    file.close();
    return true;
}

uint8_t Cartridge::cpuRead(uint16_t addr) {
    if (addr >= 0x8000 && addr <= 0xFFFF) {
        // PRG ROM access
        uint32_t offset = addr - 0x8000;
        if (prgBanks == 1 && addr >= 0xC000) {
            // Mirror for 16KB PRG ROM
            offset = addr - 0xC000;
        }
        return prgROM[offset % prgROM.size()];
    }
    return 0x00;
}

void Cartridge::cpuWrite(uint16_t addr, uint8_t data) {
    // PRG ROM is read-only
    (void)addr;
    (void)data;
}

uint8_t Cartridge::ppuRead(uint16_t addr) {
    if (addr >= 0x0000 && addr <= 0x1FFF) {
        // CHR ROM access
        return chrROM[addr % chrROM.size()];
    }
    return 0x00;
}

void Cartridge::ppuWrite(uint16_t addr, uint8_t data) {
    // CHR ROM is read-only in most cases
    (void)addr;
    (void)data;
}
