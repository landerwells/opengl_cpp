#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H
#include <glad/glad.h>
#include <cassert>
#include <vector>

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;
  
  static unsigned int getSizeOfType(unsigned int type)
  {
    switch (type)
    {
      case GL_FLOAT:
        return 4;
      case GL_UNSIGNED_INT:
        return 4;
    }
    assert(false);
    return 0;
  }
};

class VertexBufferLayout
{
public:
  VertexBufferLayout() : m_stride(0) {}
  
  template <typename T>
  void push(unsigned int count);
  
  inline const std::vector<VertexBufferElement> getElements() const { return m_elements; }
  inline unsigned int getStride() const { return m_stride; }
  
private:
  std::vector<VertexBufferElement> m_elements;
  unsigned int m_stride;
};

// Primary template definition (for unsupported types)
template <typename T>
void VertexBufferLayout::push(unsigned int)
{
  static_assert(sizeof(T) == 0, "Unsupported vertex buffer type");
}

// Specializations must be at namespace scope
template <>
inline void VertexBufferLayout::push<float>(unsigned int count)
{
  m_elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template <>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
  m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

#endif
