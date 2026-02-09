#pragma once

#include "entity_manager.h"

#include <array>
#include <cassert>
#include <unordered_map>

class IComponentArray
{
  public:
  virtual ~IComponentArray() = default;
  virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
  public:
  void InsertData(Entity entity, T component)
  {
    assert(!m_entityToIndexMap.contains(entity) &&
           "Component added to same entity more than once.");

    const size_t newIndex = m_size;
    m_entityToIndexMap[entity] = newIndex;
    m_indexToEntityMap[newIndex] = entity;
    m_componentArray[newIndex] = std::move(component);
    ++m_size;
  }

  void RemoveData(Entity entity)
  {
    assert(m_entityToIndexMap.contains(entity) && "Removing non-existent component.");

    const size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
    const size_t indexOfLastElement = m_size - 1;

    m_componentArray[indexOfRemovedEntity] = std::move(m_componentArray[indexOfLastElement]);

    const Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
    m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    m_entityToIndexMap.erase(entity);
    m_indexToEntityMap.erase(indexOfLastElement);
    --m_size;
  }

  [[nodiscard]] T& GetData(Entity entity)
  {
    assert(m_entityToIndexMap.contains(entity) && "Retrieving non-existent component.");
    return m_componentArray[m_entityToIndexMap[entity]];
  }

  [[nodiscard]] const T& GetData(Entity entity) const
  {
    assert(m_entityToIndexMap.contains(entity) && "Retrieving non-existent component.");
    return m_componentArray[m_entityToIndexMap.at(entity)];
  }

  void entityDestroyed(Entity entity) override
  {
    if (m_entityToIndexMap.contains(entity))
    {
      RemoveData(entity);
    }
  }

  private:
  std::array<T, MAX_ENTITIES> m_componentArray{};
  std::unordered_map<Entity, size_t> m_entityToIndexMap;
  std::unordered_map<size_t, Entity> m_indexToEntityMap;
  size_t m_size{0};
};
