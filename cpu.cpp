#include "cpu.h"
#include <iostream>

void CPU6502::reset() {
    A = 0x00;
    X = 0x00;
    Y = 0x00;
    SP = 0xFD;
    STATUS = 0x24; // Set U and I flags
    PC = 0xFFFC; // Reset vector location
    cycles = 8;
}

void CPU6502::nmi() {
    // Non-maskable interrupt
    cycles = 8;
}

void CPU6502::irq() {
    // Interrupt request
    if (!(STATUS & I)) {
        cycles = 7;
    }
}

int CPU6502::executor() {
    // Basic instruction execution
    if (cycles == 0) {
        // Fetch next instruction
        cycles = 1; // Basic cycle count
    }
    
    cycles--;
    return 0;
}
