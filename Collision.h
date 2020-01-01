#pragma once
#include "SDL2/SDL.h"

class ColliderComponent;

class Collision
{
public:
  static bool AABB(const SDL_Rect& rectangle_a, const SDL_Rect& rectangle_b); // axis aligned bounding box
  static bool AABB(const ColliderComponent& collider_a, const ColliderComponent& collider_b);
};
