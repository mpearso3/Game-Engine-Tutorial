#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.h"
#include "Vector2D.h"

Map* map;
Manager manager;

auto& player(manager.add_entity());

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int x_position, int y_position, int width, int height, bool full_screen)
{
  int flags = 0;
  if(full_screen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystem Initialized..." << std::endl;
    window = SDL_CreateWindow(title, x_position, y_position, width, height, flags);
    if(window) {
      std::cout << "Window created!" << std::endl;
    }
    else {
      std::cout << "ERROR, Game::init window not created" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!" << std::endl;
    }
    else {
      std::cout << "ERROR, Game::init renderer not created" << std::endl;
    }

    is_running = true;
  }
  else {
    is_running = false;
  }

  map = new Map();

  player.add_component<TransformComponent>();
  player.add_component<SpriteComponent>("assets/player.png");
}

void Game::handle_events()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
    case SDL_QUIT:
      is_running = false;
      break;

    default:
      break;
  }
}

void Game::update()
{
  manager.refresh();
  manager.update();

  player.get_component<TransformComponent>().position.add(Vector2D(10, 0));

  if(player.get_component<TransformComponent>().position.x > 100) {
    player.get_component<SpriteComponent>().set_texture("assets/dirt.png");
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);
  map->draw_map();
  manager.draw();
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}
