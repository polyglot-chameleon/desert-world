#include "world.hpp"
#include "cactus.hpp"

void draw_world(SDL_Renderer* renderer)
{
    // Desert sand.
    SDL_SetRenderDrawColor(renderer, 220, 170, 95, 255);
    SDL_RenderClear(renderer);

    // Cacti.
    draw_cactus(renderer, 180.0f, 500.0f, 1.2f);
    draw_cactus(renderer, 1030.0f, 260.0f, 0.7f);
    draw_cactus(renderer, 900.0f, 560.0f, 0.9f);
}
