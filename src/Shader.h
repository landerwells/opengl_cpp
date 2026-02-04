#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader
{
  public:
  Shader(const std::string& filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  // Instead of having all of these function, we could just have a template?
  void setUniform(const std::string& name, bool value) const;
  void setUniform(const std::string& name, int value) const;
  void setUniform(const std::string& name, float value) const;
  void setUniform(const std::string& name, const glm::vec2& value) const;
  void setUniform(const std::string& name, float x, float y) const;
  void setUniform(const std::string& name, const glm::vec3& value) const;
  void setUniform(const std::string& name, float x, float y, float z) const;
  void setUniform(const std::string& name, const glm::vec4& value) const;
  void setUniform(const std::string& name, float x, float y, float z, float w) const;
  void setUniform(const std::string& name, const glm::mat2& mat) const;
  void setUniform(const std::string& name, const glm::mat3& mat) const;
  void setUniform(const std::string& name, const glm::mat4& mat) const;

  private:
  mutable std::unordered_map<std::string, int> m_uniformLocationCache;
  unsigned int compileShader(unsigned int type, const std::string& source);
  ShaderProgramSource parseShader(const std::string& filepath);
  unsigned int createShader(const std::string& vertexShaderSource,
                            const std::string& fragmentShaderSource);
  unsigned int getUniformLocation(const std::string& name);

  std::string m_filepath;
  unsigned int m_rendererID;
};

#endif
