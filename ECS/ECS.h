#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID get_new_component_type_id()
{
  static ComponentID lastID = 0u;
  return lastID++;
}

template <typename T> 
inline ComponentID get_component_type_id() noexcept
{
  static ComponentID typeID = get_new_component_type_id();
  return typeID;
}

constexpr std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using ComponentBitSet = std::bitset<max_components>;
using GroupBitSet = std::bitset<max_groups>;

using ComponentArray = std::array<Component*, max_components>;

class Component
{
public:
  Entity* entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}

  virtual ~Component() {}
};

class Entity
{
private:
  Manager& manager;
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray component_array;
  ComponentBitSet component_bitset;
  GroupBitSet group_bitset;

public:
  Entity(Manager& mManager) : manager(mManager) {}

  void update()
  {
    for(auto& component : components) {
      component->update();
    }
  }
  void draw()
  {
    for(auto& component : components) {
      component->draw();
    }
  }
  bool is_active() const { return active; }
  void destroy() { active = false; }

  bool has_group(Group mGroup)
  {
    return group_bitset[mGroup];
  }

  void add_group(Group mGroup);
  void delete_group(Group mGroup)
  {
    group_bitset[mGroup] = false;
  }

  template <typename T>
  bool has_components() const
  {
    return component_bitset[get_component_type_id<T>()];
  }

  // DEBUG_MP - used to print out mArgs
  template <typename T, typename... TArgs>
  void print_args(TArgs&&... mArgs)
  {
    std::cout << "mArgs " << std::endl; 
    using expander = int[];
    (void)expander{0, (void(std::cout << ',' << std::forward<TArgs>(mArgs)), 0)...};
    std::cout << std::endl;
  }

  template <typename T, typename... TArgs> 
  T& add_component(TArgs&&... mArgs)
  {
    print_args<T>(std::forward<TArgs>(mArgs)...);

    T* component(new T(std::forward<TArgs>(mArgs)...));
    component->entity = this;
    std::unique_ptr<Component> uPtr(component);
    components.emplace_back(std::move(uPtr));

    component_array[get_component_type_id<T>()] = component;
    component_bitset[get_component_type_id<T>()] = true;

    component->init();
    return *component;
  }

  template<typename T> 
  T& get_component() const
  {
    auto ptr(component_array[get_component_type_id<T>()]);
    return *static_cast<T*>(ptr);
  }
};

class Manager
{
private:
  std::vector<std::unique_ptr<Entity>> entities;
  std::array<std::vector<Entity*>, max_groups> grouped_entities;

public:
  void update()
  {
    for(auto& e: entities) {
      e->update();
    }
  }
  void draw()
  {
    for(auto& e: entities) {
      e->draw();
    }
  }
  void refresh()
  {
    for(auto i(0u); i < max_groups; i++)
    {
      auto& v(grouped_entities[i]);
      v.erase(
        std::remove_if(std::begin(v), std::end(v),
          [i](Entity* mEntity)
        {
          return !mEntity->is_active() || !mEntity->has_group(i);
        }),
          std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
      [](const std::unique_ptr<Entity> &mEntitiy)
    {
      return !mEntitiy->is_active();
    }),
      std::end(entities));
  }
  void add_to_group(Entity* mEntity, Group mGroup)
  {
    grouped_entities[mGroup].emplace_back(mEntity);
  }
  std::vector<Entity*>& get_group(Group mGroup)
  {
    return grouped_entities[mGroup];
  }
  Entity& add_entity()
  {
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr(e);
    entities.emplace_back(std::move(uPtr));
    return *e;
  }
};
