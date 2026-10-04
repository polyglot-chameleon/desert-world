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
    void update(float player_x, float player_y);
    void draw(SDL_Renderer* renderer, float camera_x, float camera_y);

private:
    std::vector<CactusPosition> cacti;

    int loaded_chunk_x = 999999;
    int loaded_chunk_y = 999999;

    void generate_area(int chunk_x, int chunk_y);
};
