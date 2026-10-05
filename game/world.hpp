#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct CactusPosition {
    float x;
    float y;
    float scale;
};

class World {
public:
    void update(const SDL_FPoint& player_position);
    void draw(SDL_Renderer* renderer, const SDL_FPoint& camera);
    bool collides(const SDL_FRect& rectangle) const;

private:
    std::vector<CactusPosition> cacti;

    int loaded_chunk_x = 999999;
    int loaded_chunk_y = 999999;

    void generate_area(int chunk_x, int chunk_y);
};
