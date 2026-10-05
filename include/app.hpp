#pragma once

#include "player.hpp"
#include <SDL3/SDL.h>

inline constexpr int WINDOW_WIDTH = 1280;
inline constexpr int WINDOW_HEIGHT = 720;

class Application {
public:
  Application() = default;
  ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

  bool initialize();

  SDL_Window* window() const { return window_; }
  SDL_Renderer* renderer() const { return renderer_; }

private:
  void shutdown();

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
};

bool process_events();
SDL_FPoint calculate_camera(const Player &player);
