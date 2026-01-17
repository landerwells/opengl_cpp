#ifndef REDNERER_H
#define RENDERER_H

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
  public:
  void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void clear();

  private:
};

#endif
