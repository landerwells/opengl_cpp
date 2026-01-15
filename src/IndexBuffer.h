#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

class IndexBuffer {
  public:
  IndexBuffer(const void* data, unsigned int size);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  inline unsigned int getCount() const { return m_count; }

  private:
  unsigned int m_rendererID;
  unsigned int m_count;
};

#endif
