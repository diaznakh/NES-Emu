#pragma once
#include <cstdint>

class CPU6502 {
public:
    // Registers
    uint8_t A = 0x00;      // Accumulator
    uint8_t X = 0x00;      // X Index
    uint8_t Y = 0x00;      // Y Index
    uint8_t SP = 0x00;     // Stack Pointer
    uint16_t PC = 0x0000;  // Program Counter
    uint8_t STATUS = 0x00; // Status Register

    // Status register flags
    static constexpr uint8_t C = 0x01; // Carry
    static constexpr uint8_t Z = 0x02; // Zero
    static constexpr uint8_t I = 0x04; // Interrupt Disable
    static constexpr uint8_t D = 0x08; // Decimal
    static constexpr uint8_t B = 0x10; // Break
    static constexpr uint8_t V = 0x40; // Overflow
    static constexpr uint8_t N = 0x80; // Negative

    // Methods
    void reset();
    void nmi();
    void irq();
    int executor(); // Execute one instruction

private:
    // Internal state
    uint8_t cycles = 0;
    uint8_t fetched = 0x00;
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x00;
};
