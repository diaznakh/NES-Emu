#pragma once
#include <cstdint>

class Controller {
public:
    uint8_t controller = 0x00;
    
    void cpuWrite4016(uint8_t data) {
        // Controller strobe - not implemented in this simple version
    }
    
    uint8_t cpuRead4016() {
        // Return controller state - not implemented in this simple version
        return 0x40;
    }
};
