#include "PlayerController.h"
#include "Input.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

PlayerController::PlayerController(const glm::vec3& position, Camera* camera)
    : m_camera(camera),
      m_position(position),
      m_velocity(0.0f),
      m_moveSpeed(5.0f),
      m_mouseSensitivity(0.1f),
      m_jumpForce(5.0f),
      m_gravity(9.81f),
      m_groundLevel(0.0f),
      m_isGrounded(false),
      m_noclipMode(false),
      m_playerHeight(1.8f),
      m_playerRadius(0.3f)
{
  // Set initial camera position
  if (m_camera)
  {
    m_camera->Position = m_position;
  }
}

void PlayerController::update(float deltaTime)
{
  // TODO: We only want to 
  processMouseLook();
  processMovement(deltaTime);
  
  if (m_noclipMode)
  {
    // In noclip mode, allow free vertical movement
    if (Input::isKeyPressed(GLFW_KEY_SPACE))
    {
      m_position.y += m_moveSpeed * deltaTime;
    }
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
      m_position.y -= m_moveSpeed * deltaTime;
    }
  }
  else
  {
    // Normal physics mode
    processJump();
    applyGravity(deltaTime);
    resolveCollision();
  }
  
  // Update camera position
  if (m_camera)
  {
    m_camera->Position = m_position;
  }
}

void PlayerController::processMovement(float deltaTime)
{
  if (!m_camera) return;
  
  glm::vec3 movement(0.0f);
  
  // WASD movement
  if (Input::isKeyPressed(GLFW_KEY_W))
  {
    movement += m_camera->Front;
  }
  if (Input::isKeyPressed(GLFW_KEY_S))
  {
    movement -= m_camera->Front;
  }
  if (Input::isKeyPressed(GLFW_KEY_A))
  {
    movement -= m_camera->Right;
  }
  if (Input::isKeyPressed(GLFW_KEY_D))
  {
    movement += m_camera->Right;
  }
  
  // In physics mode, flatten movement to XZ plane (don't fly when looking up/down)
  // In noclip mode, allow full 3D movement
  if (!m_noclipMode)
  {
    movement.y = 0.0f;
  }
  
  // Normalize and apply speed
  if (glm::length(movement) > 0.0f)
  {
    movement = glm::normalize(movement);
    m_position += movement * m_moveSpeed * deltaTime;
  }
}

void PlayerController::processMouseLook()
{
  if (!m_camera) return;
  
  glm::vec2 mouseDelta = Input::getMouseDelta();
  m_camera->ProcessMouseMovement(mouseDelta.x * m_mouseSensitivity, 
                                  mouseDelta.y * m_mouseSensitivity);
}

void PlayerController::processJump()
{
  // Space to jump
  if (Input::isKeyDown(GLFW_KEY_SPACE) && m_isGrounded)
  {
    m_velocity.y = m_jumpForce;
    m_isGrounded = false;
  }
}

void PlayerController::applyGravity(float deltaTime)
{
  if (!m_isGrounded)
  {
    m_velocity.y -= m_gravity * deltaTime;
  }
  
  m_position += m_velocity * deltaTime;
}

void PlayerController::resolveCollision()
{
  // Ground collision
  float groundHeight = m_groundLevel + m_playerHeight;
  if (m_position.y <= groundHeight)
  {
    m_position.y = groundHeight;
    m_velocity.y = 0.0f;
    m_isGrounded = true;
  }
  else
  {
    m_isGrounded = false;
  }
}
