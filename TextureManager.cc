#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* renderer)
{
  SDL_Surface* temp_surface = IMG_Load(filename);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  return texture;
}
