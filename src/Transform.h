#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform
{
  public:
  Transform();
  Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
  // TODO: probably should have another constructor here for euler angles

  Transform(Transform& other);

  void setPosition(glm::vec3 position);
  void setRotation(glm::quat rotation);
  void setScale(glm::vec3 scale);

  glm::vec3 position() const { return m_translation; }
  glm::quat rotation() const { return m_rotation; }
  glm::vec3 scale() const { return m_scale; }

  void translate(glm::vec3 translation);

  private:
  glm::vec3 m_translation;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};

#endif  // TRANSFORM_H_
