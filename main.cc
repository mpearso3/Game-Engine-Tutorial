#include "Game.hpp"

Game *game = NULL;

int main(int argc, char const** argv)
{
  const uint16_t frames_per_second = 60;
  const uint16_t frame_delay = 1000 / frames_per_second; // max time between frames
  uint32_t frame_start;
  uint16_t frame_time;

  game = new Game();

  game->init("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

  while(game->running()) 
  {
    frame_start = SDL_GetTicks();

    game->handle_events();
    game->update();
    game->render();

    frame_time = SDL_GetTicks() - frame_start;
    if(frame_delay > frame_time) {
      SDL_Delay(frame_delay - frame_time);
    }
  }

  game->clean();
  delete game;

  return 0;
}
