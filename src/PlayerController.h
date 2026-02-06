#pragma once

#include <glm/glm.hpp>

class Camera;

// First-person player controller with gravity and collision
class PlayerController
{
  public:
  PlayerController(const glm::vec3& position, Camera* camera);

  void update(float deltaTime);

  // Movement settings
  void setMoveSpeed(float speed) { m_moveSpeed = speed; }
  void setMouseSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }
  void setJumpForce(float force) { m_jumpForce = force; }

  // Physics settings
  void setGravity(float gravity) { m_gravity = gravity; }
  void setGroundLevel(float y) { m_groundLevel = y; }
  void setNoclip(bool enabled) { m_noclipMode = enabled; }

  // Getters
  glm::vec3 getPosition() const { return m_position; }
  bool isGrounded() const { return m_isGrounded; }
  bool isNoclip() const { return m_noclipMode; }

  // Collision
  float getPlayerHeight() const { return m_playerHeight; }
  float getPlayerRadius() const { return m_playerRadius; }

  private:
  void processMovement(float deltaTime);
  void processMouseLook();
  void processJump();
  void applyGravity(float deltaTime);
  void resolveCollision();

  Camera* m_camera;

  glm::vec3 m_position;
  glm::vec3 m_velocity;

  // Movement
  float m_moveSpeed;
  float m_mouseSensitivity;
  float m_jumpForce;

  // Physics
  float m_gravity;
  float m_groundLevel;
  bool m_isGrounded;
  bool m_noclipMode;

  // Collision
  float m_playerHeight;  // Eye height
  float m_playerRadius;  // Collision radius
};
