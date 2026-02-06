#include "renderer.h"
#include "vertex_buffer_layout.h"

void Renderer::clear() const
{
  glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
  shader.bind();
  va.bind();
  ib.bind();
  glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(const VertexArray& va, const Shader& shader, int vertexCount) const
{
  shader.bind();
  va.bind();
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
