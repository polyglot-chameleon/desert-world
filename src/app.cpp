#include "app.hpp"

namespace {
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
}

bool initialize_application(Application& application)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    application.window = SDL_CreateWindow(
        "Desert",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (application.window == nullptr) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    application.renderer = SDL_CreateRenderer(
        application.window,
        nullptr
    );

    if (application.renderer == nullptr) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());

        SDL_DestroyWindow(application.window);
        application.window = nullptr;

        SDL_Quit();
        return false;
    }

    return true;
}

void shutdown_application(Application& application)
{
    if (application.renderer != nullptr) {
        SDL_DestroyRenderer(application.renderer);
        application.renderer = nullptr;
    }

    if (application.window != nullptr) {
        SDL_DestroyWindow(application.window);
        application.window = nullptr;
    }

    SDL_Quit();
}
