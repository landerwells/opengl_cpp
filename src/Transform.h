#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform {
  Transform();
  ~Transform();

private:
  glm::vec3 m_translation;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};

#endif // TRANSFORM_H_
