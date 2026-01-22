#include "IndexBuffer.h"

#include "glad/glad.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_count(count) {
  glGenBuffers(1, &m_rendererID);
  glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
