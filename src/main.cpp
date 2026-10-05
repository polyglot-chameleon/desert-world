#include <SDL3/SDL.h>

#include "app.hpp"
#include "player.hpp"
#include "world.hpp"

int main() {
  Application application;

  if (!initialize_application(application)) {
    return 1;
  }

  Player player;
  World world;
  bool running = true;

  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT){
        running = false;
      }
    }

    update_player(player, world);

    world.update(player.rectangle.x, player.rectangle.y);

    constexpr float SCREEN_WIDTH = 1280.0f;
    constexpr float SCREEN_HEIGHT = 720.0f;

    const float camera_x =
        player.rectangle.x + player.rectangle.w / 2.0f - (SCREEN_WIDTH / 2);

    const float camera_y =
        player.rectangle.y + player.rectangle.h / 2.0f - (SCREEN_HEIGHT / 2);


    world.draw(application.renderer, camera_x, camera_y);
    draw_player(application.renderer, player, camera_x, camera_y);

    SDL_RenderPresent(application.renderer);

    SDL_Delay(16);
  }

  shutdown_application(application);

  return 0;
}
