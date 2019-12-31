#pragma once

#include <string>
#include "ECS.h"
#include "Components.h"
#include "SDL2/SDL.h"

class ColliderComponent : public Component
{
public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent* transform;

  ColliderComponent(const char* tag)
  {
    this->tag = tag;
  }

  void init() override
  {
    if(!entity->has_components<TransformComponent>()) {
      entity->add_component<TransformComponent>();
    }
    transform = &entity->get_component<TransformComponent>();
  }
  void update() override
  {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
  }
};
