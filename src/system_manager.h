#pragma once

#include "entity_manager.h"

#include <memory>
#include <set>
#include <unordered_map>

class System
{
  public:
  std::set<Entity> m_entities;
};

class SystemManager
{
  public:
  template <typename T>
  std::shared_ptr<T> RegisterSystem()
  {
    const char* typeName = typeid(T).name();
    assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

    // Create a pointer to the system and return it so it can be used externally
    auto system = std::make_shared<T>();
    mSystems.insert({typeName, system});
    return system;
  }

  template <typename T>
  void SetSignature(Signature signature)
  {
    const char* typeName = typeid(T).name();

    assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

    // Set the signature for this system
    mSignatures.insert({typeName, signature});
  }

  void EntityDestroyed(Entity entity)
  {
    // Erase a destroyed entity from all system lists
    // mEntities is a set so no check needed
    for (auto const& pair : mSystems)
    {
      auto const& system = pair.second;

      system->m_entities.erase(entity);
    }
  }

  void EntitySignatureChanged(Entity entity, Signature entitySignature)
  {
    // Notify each system that an entity's signature changed
    for (auto const& pair : mSystems)
    {
      auto const& type = pair.first;
      auto const& system = pair.second;
      auto const& systemSignature = mSignatures[type];

      // Entity signature matches system signature - insert into set
      if ((entitySignature & systemSignature) == systemSignature)
      {
        system->m_entities.insert(entity);
      }
      // Entity signature does not match system signature - erase from set
      else
      {
        system->m_entities.erase(entity);
      }
    }
  }

  private:
  // Map from system type string pointer to a signature
  std::unordered_map<const char*, Signature> mSignatures{};

  // Map from system type string pointer to a system pointer
  std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
