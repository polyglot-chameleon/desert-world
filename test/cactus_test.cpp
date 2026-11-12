#include "cactus.hpp"

#include <SDL3/SDL.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("draw_cactus sets the cactus color", "[cactus][draw]") {
  SDL_Surface* surface =
      SDL_CreateSurface(200, 200, SDL_PIXELFORMAT_RGBA32);
  REQUIRE(surface != nullptr);

  SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);
  REQUIRE(renderer != nullptr);

  draw_cactus(renderer, 50.0f, 150.0f, 1.0f);

  Uint8 red = 0;
  Uint8 green = 0;
  Uint8 blue = 0;
  Uint8 alpha = 0;

  REQUIRE(SDL_GetRenderDrawColor(
      renderer, &red, &green, &blue, &alpha));

  CHECK(red == 48);
  CHECK(green == 105);
  CHECK(blue == 55);
  CHECK(alpha == 255);

  SDL_DestroyRenderer(renderer);
  SDL_DestroySurface(surface);
}

TEST_CASE("draw_cactus accepts a different position and scale",
          "[cactus][draw]") {
  SDL_Surface* surface =
      SDL_CreateSurface(400, 300, SDL_PIXELFORMAT_RGBA32);
  REQUIRE(surface != nullptr);

  SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);
  REQUIRE(renderer != nullptr);

  // This is a smoke test: it verifies the draw call works with
  // non-default coordinates and a non-unit scale.
  draw_cactus(renderer, 100.0f, 220.0f, 1.5f);

  CHECK(SDL_GetError()[0] == '\0');

  SDL_DestroyRenderer(renderer);
  SDL_DestroySurface(surface);
}

