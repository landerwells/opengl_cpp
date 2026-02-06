#include "Transform.h"

Transform::Transform()
    : m_translation({0.0, 0.0, 0.0}), m_rotation({1.0, 0.0, 0.0, 0.0}), m_scale(1.0)
{
}

Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : m_translation(position), m_rotation(rotation), m_scale(scale)
{
}

Transform::Transform(Transform& other) = default;

void Transform::setPosition(glm::vec3 position)
{
  m_translation = position;
}

void Transform::setRotation(glm::quat rotation)
{
  m_rotation = rotation;
}

void Transform::setScale(glm::vec3 scale)
{
  m_scale = scale;
}

void Transform::translate(glm::vec3 translation)
{
  m_translation += translation;
}
