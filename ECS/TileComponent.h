#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL2/SDL.h"

class TileComponent : public Component
{
public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  SDL_Rect tile_rectangle;
  int tile_id;
  const char* path;

  TileComponent() = default;
  TileComponent(int x, int y, int w, int h, int id)
  {
    tile_rectangle.x = x;
    tile_rectangle.y = y;
    tile_rectangle.w = w;
    tile_rectangle.h = h;

    tile_id = id;

    switch(tile_id)
    {
      case 0:
        path = "assets/water.png";
        break;
      case 1:
        path = "assets/dirt.png";
        break;
      case 2:
        path = "assets/grass.png";
        break;
      default:
        break;
    }
  }

  void init() override
  {
    entity->add_component<TransformComponent>((float)tile_rectangle.x, (float)tile_rectangle.y, (float)tile_rectangle.w, (float)tile_rectangle.h, 1);
    transform = &entity->get_component<TransformComponent>();

    entity->add_component<SpriteComponent>(path);
    sprite = &entity->get_component<SpriteComponent>();
  }
};
