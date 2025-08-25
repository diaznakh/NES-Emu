#include <iostream>
#include <sstream>
#include <deque>
#include <cassert>

#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Demo_olcNES : public olc::PixelGameEngine
{
public:
    Demo_olcNES() { sAppName = "NES Emulator with OneLoneCoder Engine"; }

private: 
    // The NES components
    CPU6502 cpu;
    PPU2C02 ppu;
    Cartridge cart;
    
    bool bEmulationRun = false;
    float fResidualTime = 0.0f;
    uint8_t nSelectedPalette = 0x00;

private: 
    // Support Utilities
    std::map<uint16_t, std::string> mapAsm;

    std::string hex(uint32_t n, uint8_t d)
    {
        std::string s(d, '0');
        for (int i = d - 1; i >= 0; i--, n >>= 4)
            s[i] = "0123456789ABCDEF"[n & 0xF];
        return s;
    };

    void DrawCpu(int x, int y)
    {
        DrawString(x, y, "STATUS:", olc::WHITE);
        DrawString(x + 64, y, "N", cpu.STATUS & 0x80 ? olc::GREEN : olc::RED);
        DrawString(x + 80, y, "V", cpu.STATUS & 0x40 ? olc::GREEN : olc::RED);
        DrawString(x + 96, y, "-", cpu.STATUS & 0x20 ? olc::GREEN : olc::RED);
        DrawString(x + 112, y, "B", cpu.STATUS & 0x10 ? olc::GREEN : olc::RED);
        DrawString(x + 128, y, "D", cpu.STATUS & 0x08 ? olc::GREEN : olc::RED);
        DrawString(x + 144, y, "I", cpu.STATUS & 0x04 ? olc::GREEN : olc::RED);
        DrawString(x + 160, y, "Z", cpu.STATUS & 0x02 ? olc::GREEN : olc::RED);
        DrawString(x + 178, y, "C", cpu.STATUS & 0x01 ? olc::GREEN : olc::RED);
        DrawString(x, y + 10, "PC: $" + hex(cpu.PC, 4));
        DrawString(x, y + 20, "A: $" + hex(cpu.A, 2) + "  [" + std::to_string(cpu.A) + "]");
        DrawString(x, y + 30, "X: $" + hex(cpu.X, 2) + "  [" + std::to_string(cpu.X) + "]");
        DrawString(x, y + 40, "Y: $" + hex(cpu.Y, 2) + "  [" + std::to_string(cpu.Y) + "]");
        DrawString(x, y + 50, "Stack P: $" + hex(cpu.SP, 4));
    }

    bool OnUserCreate() override
    {
        // Load the cartridge
        if (!cart.loadINES("tetris.nes"))
        {
            std::cout << "Failed to load tetris.nes" << std::endl;
            return false;
        }
        
        // Reset NES
        cpu.reset();
        ppu.reset();

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::DARK_BLUE);

        // Handle input
        if (GetKey(olc::Key::R).bPressed) {
            cpu.reset();
            ppu.reset();
        }
        if (GetKey(olc::Key::P).bPressed) (++nSelectedPalette) &= 0x07;
        if (GetKey(olc::Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;

        // Run emulation
        if (bEmulationRun)
        {
            if (fResidualTime > 0.0f)
                fResidualTime -= fElapsedTime;
            else
            {
                fResidualTime += (1.0f / 60.0f) - fElapsedTime;
                
                // Run one frame
                for (int i = 0; i < 29780; i++) // One frame worth of cycles
                {
                    cpu.executor();
                    ppu.clock();
                }
            }
        }
        else
        {
            // Step by step
            if (GetKey(olc::Key::C).bPressed)
            {
                cpu.executor();
            }

            if (GetKey(olc::Key::F).bPressed)
            {
                // Run one frame
                for (int i = 0; i < 29780; i++)
                {
                    cpu.executor();
                    ppu.clock();
                }
            }
        }

        // Draw CPU status
        DrawCpu(516, 2);

        // Draw Palettes
        const int nSwatchSize = 6;
        for (int p = 0; p < 8; p++) // For each palette
            for(int s = 0; s < 4; s++) // For each index
                FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340, 
                    nSwatchSize, nSwatchSize, olc::Pixel(s * 64, s * 64, s * 64));
        
        // Draw selection reticule around selected palette
        DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, olc::WHITE);

        // Draw the game screen
        olc::Sprite gameScreen(256, 240);
        for (int y = 0; y < 240; y++)
        {
            for (int x = 0; x < 256; x++)
            {
                uint32_t pixel = ppu.frame[y * 256 + x];
                uint8_t r = (pixel >> 16) & 0xFF;
                uint8_t g = (pixel >> 8) & 0xFF;
                uint8_t b = pixel & 0xFF;
                gameScreen.SetPixel(x, y, olc::Pixel(r, g, b));
            }
        }
        
        DrawSprite(0, 0, &gameScreen, 2);
        return true;
    }
};
 
int main()
{
    Demo_olcNES demo;
    demo.Construct(780, 480, 2, 2);
    demo.Start();
    return 0;
}
