#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texture_sheet, SDL_Renderer* renderer, int x, int y)
{
  this->renderer = renderer;
  this->object_texture = TextureManager::LoadTexture(texture_sheet, renderer);

  x_position = x;
  y_position = y;
}
GameObject::~GameObject()
{
}
void GameObject::Update()
{
  x_position++;
  y_position++;

  source_rectangle.h = 32;
  source_rectangle.w = 32;
  source_rectangle.x = 0;
  source_rectangle.y = 0;

  destination_rectangle.h = source_rectangle.h * 2;;
  destination_rectangle.w = source_rectangle.w * 2;;
  destination_rectangle.x = x_position;
  destination_rectangle.y = y_position;
}
void GameObject::Render()
{
  SDL_RenderCopy(renderer, object_texture, &source_rectangle, &destination_rectangle);
}
