#include "player.hpp"

constexpr float PLAYER_SPEED = 4.0f;

void update_player(Player& player)
{
    const bool* keyboard = SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_LEFT]) {
        player.rectangle.x -= PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_RIGHT]) {
        player.rectangle.x += PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_UP]) {
        player.rectangle.y -= PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_DOWN]) {
        player.rectangle.y += PLAYER_SPEED;
    }
}

void draw_player(SDL_Renderer* renderer, const Player& player)
{
    const SDL_FRect& rectangle = player.rectangle;

    // Shadow.
    SDL_SetRenderDrawColor(renderer, 150, 105, 55, 255);

    SDL_FRect shadow{
        rectangle.x - 6.0f,
        rectangle.y + rectangle.h - 4.0f,
        rectangle.w + 12.0f,
        8.0f
    };

    SDL_RenderFillRect(renderer, &shadow);

    // Body.
    SDL_SetRenderDrawColor(renderer, 55, 65, 75, 255);

    SDL_FRect body{
        rectangle.x + 6.0f,
        rectangle.y + 14.0f,
        rectangle.w - 12.0f,
        rectangle.h - 14.0f
    };

    SDL_RenderFillRect(renderer, &body);

    // Head.
    SDL_SetRenderDrawColor(renderer, 205, 145, 95, 255);

    SDL_FRect head{
        rectangle.x + 10.0f,
        rectangle.y,
        rectangle.w - 20.0f,
        18.0f
    };

    SDL_RenderFillRect(renderer, &head);
}
