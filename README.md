# NES Emulator - 6502 CPU (WIP)

A work-in-progress NES emulator written in C++, focused on building the MOS 6502 CPU from scratch. Currently, the CPU core is mostly implemented, with the executor logic under development.

![Project Status](https://img.shields.io/badge/status-in%20progress-yellow)
![Language](https://img.shields.io/badge/language-C++-blue.svg)

---

## 🧠 About the Project

This project is an NES (Nintendo Entertainment System) emulator with a primary focus on building the 6502 CPU component from the ground up. It is developed in modern C++ and is intended to closely emulate the behavior of the original hardware, starting with the CPU.

---

## ✅ Completed

- [x] Basic CPU architecture (MOS 6502)
- [x] Instruction decoding
- [x] Addressing modes
- [x] Register and flag setup

---

## ⚙️ In Progress

- [ ] Executor for opcode execution
- [ ] PPU (Picture Processing Unit)
- [ ] APU (Audio Processing Unit)
- [ ] Memory mapper support
- [ ] ROM loading and parsing
- [ ] UI or frontend for visualization

---

## 📁 Project Structure
/src
  ├── cpu/
  │     ├── instruction_set.cpp
  │     ├── registers.cpp
  │     └── addressing_modes.cpp
  ├── main.cpp
  └── ...


---

## 🚀 Getting Started

> ⚠️ This project is currently under development and not runnable as a complete emulator yet.

### 🛠️ Build Instructions

Make sure you have a C++17 compatible compiler. To build the project:

```bash
g++ -std=c++17 -o nes_emulator src/*.cpp

Zaid Khan
GitHub: @diaznakh
