#include "app.hpp"
#include "player.hpp"

Application::~Application() { shutdown(); }

// Init
bool Application::initialize() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }

  window_ = SDL_CreateWindow("Desert", WINDOW_WIDTH, WINDOW_HEIGHT,
                             SDL_WINDOW_RESIZABLE);

  if (window_ == nullptr) {
    SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
    shutdown();
    return false;
  }

  renderer_ = SDL_CreateRenderer(window_, nullptr);

  if (renderer_ == nullptr) {
    SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
    shutdown();
    return false;
  }

  return true;
}

// shutdown
void Application::shutdown() {
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }

  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  SDL_Quit();
}


bool process_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
        return false;
        }
    }
    return true;
}

SDL_FPoint calculate_camera(const Player &player) {
    const auto &rectangle = player.rectangle;

    return {
        rectangle.x + rectangle.w * 0.5f - WINDOW_WIDTH * 0.5f,
        rectangle.y + rectangle.h * 0.5f - WINDOW_HEIGHT * 0.5f,
    };
}
