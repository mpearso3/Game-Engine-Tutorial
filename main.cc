#include "Game.hpp"

Game *game = NULL;

int main(int argc, char const** argv)
{
  game = new Game();

  game->init("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

  while(game->running()) 
  {
    game->handle_events();
    game->update();
    game->render();
  }

  game->clean();
  delete game;

  return 0;
}
