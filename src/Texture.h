#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
  public:
  Texture(const std::string& filepath, bool has_alpha);
  ~Texture();

  // In OpenGL there are multiple texture slots that you can load
  // Optional parameter to pass in a slot
  void bind(unsigned int slot = 0) const;
  void unbind() const;

  inline int getWidth() const { return m_width; }
  inline int getHeight() const { return m_height; }

  private:
  unsigned int m_rendererID;
  std::string m_filepath;
  unsigned char* m_localBuffer;
  int m_width, m_height, m_BPP;
};

#endif
