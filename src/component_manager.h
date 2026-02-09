#pragma once

#include "component_array.h"

#include <memory>
#include <string_view>
#include <typeinfo>
#include <unordered_map>

class ComponentManager
{
  public:
  template <typename T>
  void RegisterComponent()
  {
    const char* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) == m_componentTypes.end() &&
           "Registering component type more than once.");

    // Add this component type to the component type map
    m_componentTypes.insert({typeName, m_nextComponentType});

    // Create a ComponentArray pointer and add it to the component arrays map
    m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    ++m_nextComponentType;
  }

  template <typename T>
  ComponentType GetComponentType()
  {
    const char* typeName = typeid(T).name();

    assert(m_componentTypes.find(typeName) != m_componentTypes.end() &&
           "Component not registered before use.");

    // Return this component's type - used for creating signatures
    return m_componentTypes[typeName];
  }

  template <typename T>
  void AddComponent(Entity entity, T component)
  {
    // Add a component to the array for an entity
    getComponentArray<T>()->InsertData(entity, component);
  }

  template <typename T>
  void RemoveComponent(Entity entity)
  {
    // Remove a component from the array for an entity
    getComponentArray<T>()->RemoveData(entity);
  }

  template <typename T>
  T& GetComponent(Entity entity)
  {
    // Get a reference to a component from the array for an entity
    return getComponentArray<T>()->GetData(entity);
  }

  void EntityDestroyed(Entity entity)
  {
    // Notify each component array that an entity has been destroyed
    // If it has a component for that entity, it will remove it
    for (auto const& pair : m_componentArrays)
    {
      auto const& component = pair.second;

      component->entityDestroyed(entity);
    }
  }

  private:
  std::unordered_map<std::string_view, ComponentType> m_componentTypes{};
  std::unordered_map<std::string_view, std::shared_ptr<IComponentArray>> m_componentArrays{};

  ComponentType m_nextComponentType{};

  template <typename T>
  std::shared_ptr<ComponentArray<T>> getComponentArray()
  {
    std::string_view typeName = typeid(T).name();
    assert(m_componentTypes.contains(typeName) && "Component not registered before use.");
    return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
  }
};
