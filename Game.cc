#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "ECS.h"
#include "Components.h"

GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = NULL;

Manager manager;
auto& new_player(manager.add_entity());

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

  player = new GameObject("assets/player.png", 0, 0);
  enemy = new GameObject("assets/player.png", 50, 50);
  map = new Map();

  new_player.add_component<PositionComponent>();
  new_player.get_component<PositionComponent>().set_position(500, 500);
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
  player->Update();
  enemy->Update();
  manager.update();
  std::cout << "players position " << new_player.get_component<PositionComponent>().x() << " " << new_player.get_component<PositionComponent>().y() << std::endl;
}

void Game::render()
{
  SDL_RenderClear(renderer);
  map->draw_map();
  player->Render();
  enemy->Render();
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "Game Cleaned" << std::endl;
}
