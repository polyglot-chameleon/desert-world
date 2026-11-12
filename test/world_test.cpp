
#include "world.hpp"

#include <SDL3/SDL.h>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <vector>

namespace {

constexpr float CHUNK_SIZE = 400.0f;
constexpr int LOADED_CHUNK_RADIUS = 2;
constexpr int MIN_CACTI_PER_CHUNK = 2;
constexpr int MAX_CACTI_PER_CHUNK = 5;
constexpr int CHUNKS_LOADED = 5 * 5;

constexpr int MIN_TOTAL_CACTI = CHUNKS_LOADED * MIN_CACTI_PER_CHUNK;

constexpr int MAX_TOTAL_CACTI = CHUNKS_LOADED * MAX_CACTI_PER_CHUNK;

} // namespace

TEST_CASE("World loads cacti for the player's chunk", "[World][update]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});

  REQUIRE(world.get_loaded_chunk_x() == 0);
  REQUIRE(world.get_loaded_chunk_y() == 0);

  REQUIRE(world.get_cacti().size() >= MIN_TOTAL_CACTI);
  REQUIRE(world.get_cacti().size() <= MAX_TOTAL_CACTI);
}

TEST_CASE("World loads a 5 by 5 chunk area", "[World][update]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});

  REQUIRE(world.get_cacti().size() >= 25 * 2);
  REQUIRE(world.get_cacti().size() <= 25 * 5);

  for (const CactusPosition &cactus : world.get_cacti()) {
    REQUIRE(cactus.scale >= 0.6f);
    REQUIRE(cactus.scale <= 1.2f);
  }
}

TEST_CASE("Cacti are generated inside their chunk boundaries",
          "[World][generation]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});

  // The loaded chunks range from -2 through 2 on both axes.
  for (const CactusPosition &cactus : world.get_cacti()) {
    const int chunk_x = static_cast<int>(std::floor(cactus.x / CHUNK_SIZE));
    const int chunk_y = static_cast<int>(std::floor(cactus.y / CHUNK_SIZE));

    REQUIRE(chunk_x >= -2);
    REQUIRE(chunk_x <= 2);
    REQUIRE(chunk_y >= -2);
    REQUIRE(chunk_y <= 2);

    const float local_x = cactus.x - chunk_x * CHUNK_SIZE;
    const float local_y = cactus.y - chunk_y * CHUNK_SIZE;

    REQUIRE(local_x >= 40.0f);
    REQUIRE(local_x <= 360.0f);
    REQUIRE(local_y >= 40.0f);
    REQUIRE(local_y <= 360.0f);
  }
}

TEST_CASE("World does not regenerate inside the same chunk",
          "[World][update]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});
  const auto first_generation = world.get_cacti();

  world.update(SDL_FPoint{200.0f, 300.0f});

  REQUIRE(world.get_loaded_chunk_x() == 0);
  REQUIRE(world.get_loaded_chunk_y() == 0);
  REQUIRE(world.get_cacti() == first_generation);
}

TEST_CASE("World regenerates when entering another chunk", "[World][update]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});
  const auto first_generation = world.get_cacti();

  world.update(SDL_FPoint{CHUNK_SIZE + 1.0f, 100.0f});

  REQUIRE(world.get_loaded_chunk_x() == 1);
  REQUIRE(world.get_loaded_chunk_y() == 0);
  REQUIRE(world.get_cacti().size() >= MIN_TOTAL_CACTI);
  REQUIRE(world.get_cacti().size() <= MAX_TOTAL_CACTI);

  // The generated area includes different chunks, so this should normally
  // produce a different layout.
  REQUIRE(world.get_cacti() != first_generation);
}

TEST_CASE("World handles negative chunk coordinates", "[World][update]") {
  World world;

  world.update(SDL_FPoint{-1.0f, -1.0f});

  REQUIRE(world.get_loaded_chunk_x() == -1);
  REQUIRE(world.get_loaded_chunk_y() == -1);

  REQUIRE(world.get_cacti().size() >= MIN_TOTAL_CACTI);
  REQUIRE(world.get_cacti().size() <= MAX_TOTAL_CACTI);

  for (const CactusPosition &cactus : world.get_cacti()) {
      const int cactus_chunk_x =
          static_cast<int>(std::floor(cactus.x / CHUNK_SIZE));
      const int cactus_chunk_y =
          static_cast<int>(std::floor(cactus.y / CHUNK_SIZE));

      REQUIRE(cactus_chunk_x >= -3);
      REQUIRE(cactus_chunk_x <= 1);
      REQUIRE(cactus_chunk_y >= -3);
      REQUIRE(cactus_chunk_y <= 1);
  }
}

TEST_CASE("Chunk boundaries use floor division", "[World][update]") {
  World world;

  world.update(SDL_FPoint{0.0f, 0.0f});
  REQUIRE(world.get_loaded_chunk_x() == 0);
  REQUIRE(world.get_loaded_chunk_y() == 0);

  world.update(SDL_FPoint{-0.001f, 0.0f});
  REQUIRE(world.get_loaded_chunk_x() == -1);
  REQUIRE(world.get_loaded_chunk_y() == 0);

  world.update(SDL_FPoint{0.0f, -0.001f});
  REQUIRE(world.get_loaded_chunk_x() == 0);
  REQUIRE(world.get_loaded_chunk_y() == -1);

  world.update(SDL_FPoint{CHUNK_SIZE, CHUNK_SIZE});
  REQUIRE(world.get_loaded_chunk_x() == 1);
  REQUIRE(world.get_loaded_chunk_y() == 1);
}

TEST_CASE("World generation is deterministic", "[World][generation]") {
  World first;
  World second;

  first.update(SDL_FPoint{123.0f, 456.0f});
  second.update(SDL_FPoint{123.0f, 456.0f});

  REQUIRE(first.get_cacti() == second.get_cacti());
}

TEST_CASE("World generation depends on the loaded chunk",
          "[World][generation]") {
  World first;
  World second;

  first.update(SDL_FPoint{100.0f, 100.0f});
  second.update(SDL_FPoint{500.0f, 100.0f});

  REQUIRE(first.get_loaded_chunk_x() == 0);
  REQUIRE(second.get_loaded_chunk_x() == 1);
  REQUIRE(first.get_cacti() != second.get_cacti());
}

TEST_CASE("Collision returns false when rectangle misses all cacti",
          "[World][collision]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});

  SDL_FRect rectangle{
      100000.0f,
      100000.0f,
      10.0f,
      10.0f,
  };

  REQUIRE_FALSE(world.collides(rectangle));
}

TEST_CASE("Collision returns true when rectangle overlaps a cactus",
          "[World][collision]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});

  REQUIRE_FALSE(world.get_cacti().empty());

  const CactusPosition &cactus = world.get_cacti().front();

  SDL_FRect rectangle{
      cactus.x - 1.0f,
      cactus.y - 1.0f,
      2.0f,
      2.0f,
  };

  REQUIRE(world.collides(rectangle));
}

TEST_CASE("Collision accounts for cactus scale", "[World][collision]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});
  REQUIRE_FALSE(world.get_cacti().empty());

  const CactusPosition &cactus = world.get_cacti().front();

  const float cactus_left = cactus.x - 5.0f * cactus.scale;

  const float cactus_top = cactus.y - 64.0f * cactus.scale;

  SDL_FRect rectangle{
      cactus_left + 0.1f,
      cactus_top + 0.1f,
      1.0f,
      1.0f,
  };

  REQUIRE(world.collides(rectangle));
}

TEST_CASE("Collision returns false for rectangle just outside cactus",
          "[World][collision]") {
  World world;

  world.update(SDL_FPoint{100.0f, 100.0f});
  REQUIRE_FALSE(world.get_cacti().empty());

  const CactusPosition &cactus = world.get_cacti().front();

  const float cactus_left = cactus.x - 5.0f * cactus.scale;

  SDL_FRect rectangle{
      cactus_left - 11.0f,
      cactus.y - 64.0f * cactus.scale,
      5.0f,
      5.0f,
  };

  REQUIRE_FALSE(world.collides(rectangle));
}
