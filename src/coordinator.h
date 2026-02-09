#pragma once

#include "component_manager.h"
#include "entity_manager.h"
#include "event.h"
#include "event_manager.h"
#include "system_manager.h"

#include <functional>

class Coordinator
{
  public:
  Coordinator()
      : m_componentManager{std::make_unique<ComponentManager>()},
        m_entityManager{std::make_unique<EntityManager>()},
        m_systemManager{std::make_unique<SystemManager>()}
  {
  }

  Entity createEntity() { return m_entityManager->createEntity(); }

  void DestroyEntity(Entity entity)
  {
    m_entityManager->destroyEntity(entity);
    m_componentManager->EntityDestroyed(entity);
    m_systemManager->EntityDestroyed(entity);
  }

  // Component methods
  template <typename T>
  void RegisterComponent()
  {
    m_componentManager->RegisterComponent<T>();
  }

  template <typename T>
  void AddComponent(Entity entity, T component)
  {
    m_componentManager->AddComponent<T>(entity, component);

    auto signature = m_entityManager->getSignature(entity);
    signature.set(m_componentManager->GetComponentType<T>(), true);
    m_entityManager->setSignature(entity, signature);

    m_systemManager->EntitySignatureChanged(entity, signature);
  }

  template <typename T>
  void RemoveComponent(Entity entity)
  {
    m_componentManager->RemoveComponent<T>(entity);

    auto signature = m_entityManager->getSignature(entity);
    signature.set(m_componentManager->GetComponentType<T>(), false);
    m_entityManager->setSignature(entity, signature);

    m_systemManager->EntitySignatureChanged(entity, signature);
  }

  template <typename T>
  T& GetComponent(Entity entity)
  {
    return m_componentManager->GetComponent<T>(entity);
  }

  template <typename T>
  ComponentType GetComponentType()
  {
    return m_componentManager->GetComponentType<T>();
  }

  // System methods
  template <typename T>
  std::shared_ptr<T> registerSystem()
  {
    return m_systemManager->RegisterSystem<T>();
  }

  template <typename T>
  void SetSystemSignature(Signature signature)
  {
    m_systemManager->SetSignature<T>(signature);
  }

  // Event methods
  void AddEventListener(EventId eventId, std::function<void(Event&)> const& listener)
  {
    m_eventManager->AddListener(eventId, listener);
  }

  void SendEvent(Event& event) { m_eventManager->SendEvent(event); }

  void SendEvent(EventId eventId) { m_eventManager->SendEvent(eventId); }

  private:
  std::unique_ptr<ComponentManager> m_componentManager;
  std::unique_ptr<EntityManager> m_entityManager;
  std::unique_ptr<SystemManager> m_systemManager;
  std::unique_ptr<EventManager> m_eventManager;
};
