#pragma once

#include "Components.h"
#include "../TextureManager.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class SpriteComponent : public Component
{
private:
  TransformComponent* transform;
  SDL_Texture* texture;
  SDL_Rect source_rectangle, destination_rectangle;

public:
  SpriteComponent() = default;
  SpriteComponent(const char* path)
  {
    set_texture(path);
  }
  ~SpriteComponent()
  {
    SDL_DestroyTexture(texture);
  }

  void set_texture(const char* path)
  {
    texture = TextureManager::LoadTexture(path);
  }
  void init() override
  {
    transform = &entity->get_component<TransformComponent>();

    source_rectangle.x = source_rectangle.y = 0;
    source_rectangle.w = transform->width;
    source_rectangle.h = transform->width;
  }
  void update() override
  {
    destination_rectangle.x = (int)transform->position.x;
    destination_rectangle.y = (int)transform->position.y;
    destination_rectangle.w = transform->width * transform->scale;
    destination_rectangle.h = transform->height * transform->scale;
  }
  void draw() override
  {
    TextureManager::Draw(texture, source_rectangle, destination_rectangle);
  }
};
