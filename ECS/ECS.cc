#include "ECS.h"

void Entity::add_group(Group mGroup)
{
  group_bitset[mGroup] = true;
  manager.add_to_group(this, mGroup);
}
