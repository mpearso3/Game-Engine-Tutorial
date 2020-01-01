#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

auto& player(manager.add_entity());
auto& wall(manager.add_entity());
auto& tile_0(manager.add_entity());
auto& tile_1(manager.add_entity());
auto& tile_2(manager.add_entity());

std::vector<ColliderComponent*> Game::colliders;
SDL_Event Game::event;
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

  player.add_component<TransformComponent>(2);
  player.add_component<SpriteComponent>("assets/player.png");
  player.add_component<KeyboardController>();
  player.add_component<ColliderComponent>("player");

  wall.add_component<TransformComponent>(300.0, 300.0, 300, 20, 1);
  wall.add_component<SpriteComponent>("assets/dirt.png");
  wall.add_component<ColliderComponent>("wall");

  tile_0.add_component<TileComponent>(200, 200, 32, 32, 0);

  tile_1.add_component<TileComponent>(250, 250, 32, 32, 1);
  tile_1.add_component<ColliderComponent>("dirt");

  tile_2.add_component<TileComponent>(150, 150, 32, 32, 2);
  tile_2.add_component<ColliderComponent>("grass");
}

void Game::handle_events()
{
  SDL_PollEvent(&event);
  switch (event.type)
  {
    case SDL_QUIT:
      is_running = false;
      break;
    default:
      break;
  }

  if(event.type == SDL_KEYDOWN) 
  {
    switch(event.key.keysym.sym)
    {
      case SDLK_ESCAPE:
        is_running = false;
        break;
      default:
        break;
    }
  }
}

void Game::update()
{
  manager.refresh();
  manager.update();

  for(auto& collider_component : colliders)
  {
    Collision::AABB(player.get_component<ColliderComponent>(), *collider_component);
    //if(Collision::AABB(player.get_component<ColliderComponent>().collider, wall.get_component<ColliderComponent>().collider)) {
      //player.get_component<TransformComponent>().scale = 1;
      //player.get_component<TransformComponent>().velocity * -1;
    //}
  }
}

void Game::render()
{
  SDL_RenderClear(renderer);
  //map->draw_map();
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
