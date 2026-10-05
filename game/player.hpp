#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include "world.hpp"

class Player {
public:
  SDL_FPoint position() const {
    return {
        rectangle.x,
        rectangle.y,
    };
  }
    SDL_FRect rectangle{
        600.0f,
        320.0f,
        40.0f,
        40.0f
    };

};

void update_player(Player& player, const World& world);
void draw_player(SDL_Renderer* renderer, const Player& player, const SDL_FPoint& camera);
