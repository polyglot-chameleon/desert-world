#include "player.hpp"
#include <SDL3/SDL_rect.h>

constexpr float PLAYER_SPEED = 2;

void update_player(
    Player& player,
    const World& world
) {
    // 1. Read keyboard.
    float move_x = 0.0f;
    float move_y = 0.0f;

    const bool* keyboard =
        SDL_GetKeyboardState(nullptr);

    if (keyboard[SDL_SCANCODE_LEFT]) {
        move_x -= PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_RIGHT]) {
        move_x += PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_UP]) {
        move_y -= PLAYER_SPEED;
    }

    if (keyboard[SDL_SCANCODE_DOWN]) {
        move_y += PLAYER_SPEED;
    }

    // 2. Test and apply movement.
    SDL_FRect test = player.rectangle;
    test.x += move_x;

    if (!world.collides(test)) {
        player.rectangle.x += move_x;
    }

    test = player.rectangle;
    test.y += move_y;

    if (!world.collides(test)) {
        player.rectangle.y += move_y;
    }
}


void draw_player(SDL_Renderer* renderer, const Player& player, const SDL_FPoint& camera)
{
    const SDL_FRect& rectangle = player.rectangle;

    // Body.
    SDL_SetRenderDrawColor(renderer, 55, 65, 75, 255);

    SDL_FRect body{
        rectangle.x + 6 - camera.x,
        rectangle.y + 14 - camera.y,
        rectangle.w - 12.0f,
        rectangle.h - 14.0f
    };

    SDL_RenderFillRect(renderer, &body);

    // Head.
    SDL_SetRenderDrawColor(renderer, 205, 145, 95, 255);

    SDL_FRect head{
        rectangle.x + 10 - camera.x,
        rectangle.y - camera.y,
        rectangle.w - 20.0f,
        18.0f
    };

    SDL_RenderFillRect(renderer, &head);
}
