#include "Map.hpp"
#include "TextureManager.hpp"

int level_1[20][25] = {
  {1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {1,1,1,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
  dirt = TextureManager::LoadTexture("assets/dirt.png");
  grass = TextureManager::LoadTexture("assets/grass.png");
  water = TextureManager::LoadTexture("assets/water.png");

  load_map(level_1);

  source.x = destination.x = 0;
  source.y = destination.y = 0;
  source.w = destination.w = 32;
  source.h = destination.h = 32;
}
Map::~Map()
{
  SDL_DestroyTexture(grass);
  SDL_DestroyTexture(water);
  SDL_DestroyTexture(dirt);
}

void Map::load_map(int arr[20][25])
{
  for(size_t row = 0; row < 20; row++)
  {
    for(size_t column = 0; column < 25; column++)
    {
      map[row][column] = arr[row][column];
    }
  }
}
void Map::draw_map()
{
  int type = 0;
  for(size_t row = 0; row < 20; row++)
  {
    for(size_t column = 0; column < 25; column++)
    {
      type = map[row][column];

      destination.x = column * 32;
      destination.y = row * 32;

      switch(type) {
        case 0:
          TextureManager::Draw(water, source, destination);
          break;
        case 1:
          TextureManager::Draw(grass, source, destination);
          break;
        case 2:
          TextureManager::Draw(dirt, source, destination);
          break;
        default:
          std::cout << "ERROR, used a Map::draw_map type that does not exist... type == " << type << std::endl;
          break;
      }
    }
  }
}
