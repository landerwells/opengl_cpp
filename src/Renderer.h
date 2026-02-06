#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "glm/fwd.hpp"

class Renderer
{
  public:
  Renderer() : m_clearColor(0.2f, 0.3f, 0.3f, 1.0f) {}
  Renderer(float x, float y, float z) : m_clearColor(x, y, z, 1.0f) {}
  void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void draw(const VertexArray& va, const Shader& shader, int vertexCount) const;
  void clear() const;

  void setClearColor(float r, float g, float b, float a = 1.0f)
  {
    m_clearColor = glm::vec4(r, g, b, a);
  }

  void setClearColor(const glm::vec4& color) { m_clearColor = color; }

  // Enable/disable OpenGL states
  void enableDepthTest() { glEnable(GL_DEPTH_TEST); }
  void disableDepthTest() { glDisable(GL_DEPTH_TEST); }
  void enableBlending() { glEnable(GL_BLEND); }
  void disableBlending() { glDisable(GL_BLEND); }
  void setBlendFunc(GLenum sfactor, GLenum dfactor) { glBlendFunc(sfactor, dfactor); }

  private:
  glm::vec4 m_clearColor;
};
