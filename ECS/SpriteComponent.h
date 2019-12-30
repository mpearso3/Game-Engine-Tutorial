#pragma once

#include "Components.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class SpriteComponent : public Component
{
private:
  PositionComponent* position;
  SDL_Texture* texture;
  SDL_Rect source_rectangle, destination_rectangle;

public:
  SpriteComponent() = default;
  SpriteComponent(const char* path)
  {
    set_texture(path);
  }
  void set_texture(const char* path)
  {
    texture = TextureManager::LoadTexture(path);
  }
  void init() override
  {
    position = &entity->get_component<PositionComponent>();

    source_rectangle.x = source_rectangle.y = 0;
    source_rectangle.w = source_rectangle.h = 32;
    
    destination_rectangle.x = destination_rectangle.y = 0;
    destination_rectangle.w = destination_rectangle.h = 64;
  }
  void update() override
  {
    destination_rectangle.x = position->x();
    destination_rectangle.y = position->y();
  }
  void draw() override
  {
    TextureManager::Draw(texture, source_rectangle, destination_rectangle);
  }
};
