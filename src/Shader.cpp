#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

Shader::Shader(const std::string& filepath) : m_filepath(filepath), m_rendererID(0)
{
  
  ShaderProgramSource source = parseShader(filepath);
  m_rendererID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
  glDeleteProgram(m_rendererID);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  GLint success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    GLint logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> infoLog(logLength);
    glGetShaderInfoLog(id, logLength, nullptr, infoLog.data());

    const char* shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
    std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n"
              << infoLog.data() << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
  std::ifstream stream(filepath);

  enum class ShaderType
  {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  };

  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line))
  {
    if (line.find("#shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos)
        type = ShaderType::FRAGMENT;
    }
    else
    {
      ss[(int)type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::createShader(const std::string& vertexShaderSource,
                                  const std::string& fragmentShaderSource)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  GLchar infoLog[1024];
  int success;

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n" << infoLog << '\n' << std::endl;
  }

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

void Shader::bind() const
{
  glUseProgram(m_rendererID);
}
void Shader::unbind() const
{
  glUseProgram(0);
}

unsigned int Shader::getUniformLocation(const std::string& name) {}

void Shader::setUniform(const std::string& name, bool value) const {}

void Shader::setUniform(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const {}

void Shader::setUniform(const std::string& name, const glm::vec2& value) const {}

void Shader::setUniform(const std::string& name, float x, float y) const {}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {}

void Shader::setUniform(const std::string& name, float x, float y, float z) const {}

void Shader::setUniform(const std::string& name, const glm::vec4& value) const {}

void Shader::setUniform(const std::string& name, float x, float y, float z, float w) const {}

void Shader::setUniform(const std::string& name, const glm::mat2& mat) const {}

void Shader::setUniform(const std::string& name, const glm::mat3& mat) const {}

void Shader::setUniform(const std::string& name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
