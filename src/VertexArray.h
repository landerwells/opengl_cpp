#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
  public:
  VertexArray();

  ~VertexArray();

  void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

  void bind() const;

  void unbind() const;

  private:
  unsigned int m_rendererID;
};

#endif
