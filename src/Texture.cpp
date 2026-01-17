#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& filepath, bool has_alpha)
    : m_rendererID(0),
      m_filepath(filepath),
      m_localBuffer(nullptr),
      m_width(0),
      m_height(0),
      m_BPP(0)
{
  stbi_set_flip_vertically_on_load(true);
  m_localBuffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, 0);

  glGenTextures(1, &m_rendererID);
  glBindTexture(GL_TEXTURE_2D, m_rendererID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = has_alpha ? GL_RGBA : GL_RGB;

  glTexImage2D(
      GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_localBuffer);

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (m_localBuffer)
  {
    stbi_image_free(m_localBuffer);
  }
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_rendererID);
}

void Texture::bind(unsigned int slot) const
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
