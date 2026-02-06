#include "window.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <stdexcept>

Window::Window(int width, int height, const std::string& title)
    : m_window(nullptr), m_width(width), m_height(height)
{
  // Initialize GLFW
  if (!glfwInit())
  {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_window)
  {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }

  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

Window::~Window()
{
  if (m_window)
  {
    glfwDestroyWindow(m_window);
  }
  glfwTerminate();
}

bool Window::shouldClose()
{
  return glfwWindowShouldClose(m_window);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void Window::swapBuffers()
{
  glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
  glfwPollEvents();
}

void Window::captureMouse(bool capture)
{
  if (capture)
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }
  else
  {
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}
