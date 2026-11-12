#include "player.hpp"

#include <SDL3/SDL.h>
#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <cstring>

namespace {

struct RenderFixture {
    SDL_Surface* surface =
        SDL_CreateSurface(120, 120, SDL_PIXELFORMAT_RGBA32);
    SDL_Renderer* renderer =
        surface ? SDL_CreateSoftwareRenderer(surface) : nullptr;

    ~RenderFixture() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (surface) SDL_DestroySurface(surface);
    }

    Uint32 pixel(int x, int y) {
        SDL_RenderPresent(renderer);
        REQUIRE(SDL_LockSurface(surface));

        Uint32 value = 0;
        const auto* row = static_cast<const Uint8*>(surface->pixels)
                        + y * surface->pitch;
        std::memcpy(&value, row + x * sizeof(Uint32), sizeof(value));

        SDL_UnlockSurface(surface);
        return value;
    }

    void check_color(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
	const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(surface->format);
	REQUIRE(details != nullptr);
        Uint8 actual_r, actual_g, actual_b, actual_a;

        SDL_GetRGBA(pixel(x, y), details, SDL_GetSurfacePalette(surface), &actual_r, &actual_g, &actual_b, &actual_a);

        CHECK(actual_r == r);
        CHECK(actual_g == g);
        CHECK(actual_b == b);
        CHECK(actual_a == 255);
    }
};

}  // namespace

TEST_CASE("draw_player draws the body and head", "[player][draw]") {
    RenderFixture fixture;
    REQUIRE(fixture.surface != nullptr);
    REQUIRE(fixture.renderer != nullptr);

    // Set a contrasting background.
    SDL_SetRenderDrawColor(fixture.renderer, 0, 0, 0, 255);
    SDL_RenderClear(fixture.renderer);

    Player player{};
    player.rectangle = SDL_FRect{20.0f, 20.0f, 30.0f, 40.0f};

    draw_player(fixture.renderer, player, SDL_FPoint{0.0f, 0.0f});

    fixture.check_color(30, 45, 55, 65, 75);   // Body
    fixture.check_color(32, 25, 205, 145, 95); // Head
}

TEST_CASE("draw_player applies the camera offset", "[player][draw]") {
    RenderFixture fixture;
    REQUIRE(fixture.surface != nullptr);
    REQUIRE(fixture.renderer != nullptr);

    SDL_SetRenderDrawColor(fixture.renderer, 0, 0, 0, 255);
    SDL_RenderClear(fixture.renderer);

    Player player{};
    player.rectangle = SDL_FRect{20.0f, 20.0f, 30.0f, 40.0f};

    draw_player(fixture.renderer, player, SDL_FPoint{10.0f, 5.0f});

    fixture.check_color(20, 40, 55, 65, 75);   // Shifted body
    fixture.check_color(22, 20, 205, 145, 95); // Shifted head
    fixture.check_color(40, 45, 0, 0, 0);      // Original body location is clear
}

