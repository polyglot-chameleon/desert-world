#include "world.hpp"
#include "cactus.hpp"

#include <random>

constexpr int CHUNK_SIZE = 400;

void World::update(float player_x, float player_y)
{
    const int chunk_x =
        static_cast<int>(player_x / CHUNK_SIZE);

    const int chunk_y =
        static_cast<int>(player_y / CHUNK_SIZE);

    if (chunk_x == loaded_chunk_x && chunk_y == loaded_chunk_y)
        return;

    loaded_chunk_x = chunk_x;
    loaded_chunk_y = chunk_y;

    cacti.clear();

    // Keep the current area plus one chunk of padding.
    for (int y = chunk_y - 2; y <= chunk_y + 2; ++y) {
        for (int x = chunk_x - 2; x <= chunk_x + 2; ++x) {
            generate_area(x, y);
        }
    }
}

void World::generate_area(int chunk_x, int chunk_y)
{
    // Same chunk coordinates produce the same cacti.
    std::mt19937 random(
        static_cast<unsigned>(chunk_x * 92837111 + chunk_y * 689287499)
    );

    std::uniform_int_distribution<int> amount(2, 5);
    std::uniform_real_distribution<float> position(40.0f, CHUNK_SIZE - 40.0f);
    std::uniform_real_distribution<float> scale(0.6f, 1.2f);

    for (int i = 0; i < amount(random); ++i) {
        cacti.push_back({
            chunk_x * CHUNK_SIZE + position(random),
            chunk_y * CHUNK_SIZE + position(random),
            scale(random)
        });
    }
}

void World::draw(
    SDL_Renderer* renderer,
    float camera_x,
    float camera_y
) {
    SDL_SetRenderDrawColor(renderer, 220, 170, 95, 255);
    SDL_RenderClear(renderer);

    for (const CactusPosition& cactus : cacti) {
        draw_cactus(
            renderer,
            cactus.x - camera_x,
            cactus.y - camera_y,
            cactus.scale
        );
    }
}
