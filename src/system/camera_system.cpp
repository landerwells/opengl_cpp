#include "camera_system.h"

#include "../component/transform.h"
#include "../coordinator.h"
#include "../ecs_constants.h"

extern Coordinator g_coordinator;

void CameraControlSystem::Init()
{
  g_coordinator.AddEventListener(
      METHOD_LISTENER(Events::Window::INPUT, CameraControlSystem::InputListener));
}

void CameraControlSystem::Update(float dt)
{
  for (auto& entity : m_entities)
  {
    auto& transform = g_coordinator.GetComponent<Transform>(entity);

    float speed = 20.0f;

    if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
    {
      transform.position.z -= (dt * speed);
    }

    else if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
    {
      transform.position.z += (dt * speed);
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::Q)))
    {
      transform.position.y += (dt * speed);
    }

    else if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))
    {
      transform.position.y -= (dt * speed);
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
    {
      transform.position.x -= (dt * speed);
    }

    else if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
    {
      transform.position.x += (dt * speed);
    }
  }
}

void CameraControlSystem::InputListener(Event& event)
{
  mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}
