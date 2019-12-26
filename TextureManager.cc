#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
  SDL_Surface* temp_surface = IMG_Load(filename);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
  SDL_FreeSurface(temp_surface);

  if(texture == NULL) {
    std::cout << "ERROR, TextureManager::LoadTexture failed to load filename " << filename << std::endl;
  }

  return texture;
}
void TextureManager::Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination)
{
  SDL_RenderCopy(Game::renderer, texture, &source, &destination);
}
