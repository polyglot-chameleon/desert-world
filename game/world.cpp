#include "world.hpp"
#include "cactus.hpp"

#include <cmath>
#include <cstdint>
#include <random>

namespace {

constexpr float CHUNK_SIZE = 400.0f;
constexpr int LOADED_CHUNK_RADIUS = 2;
constexpr int MAX_CACTI_PER_CHUNK = 5;

}  // namespace

void World::update(const SDL_FPoint& player_position) {
  const int chunk_x = static_cast<int>(
      std::floor(player_position.x / CHUNK_SIZE)
  );

  const int chunk_y = static_cast<int>(
      std::floor(player_position.y / CHUNK_SIZE)
  );

  if (chunk_x == loaded_chunk_x &&
      chunk_y == loaded_chunk_y) {
    return;
  }

  loaded_chunk_x = chunk_x;
  loaded_chunk_y = chunk_y;

  cacti.clear();

  constexpr int diameter = LOADED_CHUNK_RADIUS * 2 + 1;
  cacti.reserve(diameter * diameter * MAX_CACTI_PER_CHUNK);

  for (int y = chunk_y - LOADED_CHUNK_RADIUS;
       y <= chunk_y + LOADED_CHUNK_RADIUS;
       ++y) {
    for (int x = chunk_x - LOADED_CHUNK_RADIUS;
         x <= chunk_x + LOADED_CHUNK_RADIUS;
         ++x) {
      generate_area(x, y);
    }
  }
}

void World::generate_area(int chunk_x, int chunk_y) {
  const auto seed =
      static_cast<std::uint32_t>(chunk_x) * 92837111u ^
      static_cast<std::uint32_t>(chunk_y) * 689287499u;

  std::mt19937 random(seed);

  std::uniform_int_distribution<int> amount(2, 5);
  std::uniform_real_distribution<float> position(
      40.0f,
      CHUNK_SIZE - 40.0f
  );
  std::uniform_real_distribution<float> scale(0.6f, 1.2f);

  const int cactus_count = amount(random);

  for (int i = 0; i < cactus_count; ++i) {
    cacti.push_back({
        chunk_x * CHUNK_SIZE + position(random),
        chunk_y * CHUNK_SIZE + position(random),
        scale(random),
    });
  }
}

void World::draw(
    SDL_Renderer* renderer,
    const SDL_FPoint& camera
) {
  SDL_SetRenderDrawColor(renderer, 220, 170, 95, 255);
  SDL_RenderClear(renderer);

  for (const CactusPosition& cactus : cacti) {
    draw_cactus(
        renderer,
        cactus.x - camera.x,
        cactus.y - camera.y,
        cactus.scale
    );
  }
}

bool World::collides(const SDL_FRect& rectangle) const {
  for (const CactusPosition& cactus : cacti) {
    const SDL_FRect cactus_box{
        cactus.x - 5.0f * cactus.scale,
        cactus.y - 64.0f * cactus.scale,
        10.0f * cactus.scale,
        64.0f * cactus.scale,
    };

    if (SDL_HasRectIntersectionFloat(&rectangle, &cactus_box)) {
      return true;
    }
  }

  return false;
}
