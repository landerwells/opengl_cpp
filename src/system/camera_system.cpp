#include "camera_system.h"

#include "../component/transform.h"
#include "../coordinator.h"
#include "../ecs_constants.h"
#include "../input.h"

#include <glm/gtc/quaternion.hpp>

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

    float speed = 5.0f;

    // Movement relative to camera orientation
    if (mButtons.test(static_cast<std::size_t>(InputButtons::W)))
    {
      transform.position += transform.forward() * speed * dt;
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::S)))
    {
      transform.position -= transform.forward() * speed * dt;
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::A)))
    {
      transform.position -= transform.right() * speed * dt;
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::D)))
    {
      transform.position += transform.right() * speed * dt;
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::Q)))
    {
      transform.position += glm::vec3(0, 1, 0) * speed * dt;  // World up
    }

    if (mButtons.test(static_cast<std::size_t>(InputButtons::E)))
    {
      transform.position -= glm::vec3(0, 1, 0) * speed * dt;  // World down
    }

    // Mouse look
    glm::vec2 mouseDelta = Input::getMouseDelta();
    float sensitivity = 0.1f;

    if (glm::length(mouseDelta) > 0.0f)
    {
      float yaw = mouseDelta.x * sensitivity;
      float pitch = mouseDelta.y * sensitivity;

      // Rotate around world up axis for yaw (applied to current rotation)
      glm::quat yawRotation = glm::angleAxis(glm::radians(-yaw), glm::vec3(0, 1, 0));
      transform.rotation = glm::normalize(yawRotation * transform.rotation);

      // Rotate around the NEW camera's right axis for pitch
      glm::quat pitchRotation = glm::angleAxis(glm::radians(-pitch), transform.right());
      transform.rotation = glm::normalize(pitchRotation * transform.rotation);
    }
  }
}

void CameraControlSystem::InputListener(Event& event)
{
  mButtons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}
