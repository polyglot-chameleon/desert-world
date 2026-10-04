#pragma once

#include <SDL3/SDL.h>

struct Player {
    SDL_FRect rectangle{
        600.0f,
        320.0f,
        40.0f,
        40.0f
    };
};

void update_player(Player& player);
void draw_player(SDL_Renderer* renderer, const Player& player, float camera_x, float camera_y);
