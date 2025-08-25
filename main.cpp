#include <iostream>
#include <SDL2/SDL.h>
#include "cpu.h"
#include "ppu.h"
#include "cartridge.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("NES Emulator", 
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        256 * 3, 240 * 3, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create texture for rendering
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
                                           SDL_TEXTUREACCESS_STREAMING, 256, 240);
    if (!texture) {
        std::cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Load ROM
    Cartridge cart;
    if (!cart.loadINES(argv[1])) {
        std::cout << "Failed to load ROM: " << argv[1] << std::endl;
        return 1;
    }

    // Initialize components
    CPU6502 cpu;
    PPU2C02 ppu;
    cpu.reset();
    ppu.reset();

    std::cout << "NES Emulator initialized successfully" << std::endl;
    std::cout << "ROM loaded: " << argv[1] << std::endl;

    // Main loop
    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Emulation loop - run one frame worth of cycles
        for (int i = 0; i < 29780; i++) { // ~29780 cycles per frame
            cpu.executor();
            ppu.clock();
        }

        // Render frame
        void* pixels;
        int pitch;
        SDL_LockTexture(texture, nullptr, &pixels, &pitch);
        memcpy(pixels, ppu.frame.data(), 256 * 240 * 4);
        SDL_UnlockTexture(texture);

        // Clear screen and render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        // Frame rate control
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTime < 16) { // ~60 FPS
            SDL_Delay(16 - (currentTime - lastTime));
        }
        lastTime = currentTime;
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
