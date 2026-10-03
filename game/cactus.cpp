#include <SDL3/SDL.h>
#include "cactus.hpp"

void draw_cactus(
    SDL_Renderer* renderer,
    float x,
    float y,
    float scale
)
{
    SDL_SetRenderDrawColor(renderer, 48, 105, 55, 255);

    // Main stem.
    SDL_FRect stem{
        x,
        y - 90.0f * scale,
        18.0f * scale,
        90.0f * scale
    };

    // Left arm.
    SDL_FRect left_arm{
        x - 24.0f * scale,
        y - 62.0f * scale,
        24.0f * scale,
        14.0f * scale
    };

    SDL_FRect left_arm_up{
        x - 24.0f * scale,
        y - 78.0f * scale,
        14.0f * scale,
        30.0f * scale
    };

    // Right arm.
    SDL_FRect right_arm{
        x + 18.0f * scale,
        y - 42.0f * scale,
        25.0f * scale,
        14.0f * scale
    };

    SDL_FRect right_arm_up{
        x + 29.0f * scale,
        y - 61.0f * scale,
        14.0f * scale,
        33.0f * scale
    };

    SDL_RenderFillRect(renderer, &stem);
    SDL_RenderFillRect(renderer, &left_arm);
    SDL_RenderFillRect(renderer, &left_arm_up);
    SDL_RenderFillRect(renderer, &right_arm);
    SDL_RenderFillRect(renderer, &right_arm_up);
}
