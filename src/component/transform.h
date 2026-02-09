#pragma once

#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

struct Transform
{
  glm::vec3 position{0.0f};
  glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
  glm::vec3 scale{1.0f};

  glm::mat4 matrix() const
  {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMat = glm::mat4_cast(rotation);
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    return translation * rotationMat * scaleMat;
  }

  glm::vec3 forward() const { return rotation * glm::vec3(0, 0, -1); }
  glm::vec3 right() const { return rotation * glm::vec3(1, 0, 0); }
  glm::vec3 up() const { return rotation * glm::vec3(0, 1, 0); }
};
