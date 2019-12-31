#include "Collision.h"

bool Collision::AABB(const SDL_Rect& rectangle_a, const SDL_Rect& rectangle_b)
{
  if(
      rectangle_a.x + rectangle_a.w >= rectangle_b.x &&
      rectangle_b.x + rectangle_b.w >= rectangle_a.x &&
      rectangle_a.y + rectangle_a.h >= rectangle_b.y &&
      rectangle_b.y + rectangle_b.h >= rectangle_a.y
    )
  {
    return true;
  }
  return false;
}
