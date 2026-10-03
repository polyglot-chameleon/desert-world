#pragma once

#include <SDL3/SDL.h>

struct Application {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

bool initialize_application(Application& application);
void shutdown_application(Application& application);
