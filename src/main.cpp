#include <SDL3/SDL.h>

#include "app.hpp"
#include "player.hpp"
#include "world.hpp"

int main()
{
    Application application;

    if (!initialize_application(application)) {
        return 1;
    }

    Player player;
    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        update_player(player);

        draw_world(application.renderer);
        draw_player(application.renderer, player);

        SDL_RenderPresent(application.renderer);

        SDL_Delay(16);
    }

    shutdown_application(application);

    return 0;
}
