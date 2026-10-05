#include <SDL3/SDL.h>

#include "app.hpp"
#include "player.hpp"
#include "world.hpp"


int main() {
  Application application;

  if (!application.initialize()) {
    return 1;
  }

  Player player;
  World world;

  while (process_events()) {
    update_player(player, world);
    world.update(player.position());

    const SDL_FPoint camera = calculate_camera(player);

    world.draw(application.renderer(), camera);
    draw_player(application.renderer(), player, camera);

    SDL_RenderPresent(application.renderer());
    SDL_Delay(16);
  }

  return 0;
}
