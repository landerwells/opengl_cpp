#include "Window.h"

#include <iostream>
#include "GLFW/glfw3.h"
#include "camera.h"

Window::Window(int width, int height, const std::string& title)
    : m_width(width),
      m_height(height),
      m_lastX(width / 2.0),
      m_lastY(height / 2.0),
      m_firstMouse(true)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);
  if (!m_window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
  // glfwSetCursorPosCallback(m_window, mouse_callback);
  // glfwSetScrollCallback(m_window, scroll_callback);

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
  glfwTerminate();
}

bool Window::shouldClose()
{
  glfwWindowShouldClose(m_window);
}

void Window::processInput(Camera& camera)
{
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_window, true);

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, m_deltaTime);
  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, m_deltaTime);
  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, m_deltaTime);
  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, m_deltaTime);
  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(UP, m_deltaTime);
}

// This one is fine
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// These two should speak to the inputhandler?
// void Window::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
// {
//   float xpos = static_cast<float>(xposIn);
//   float ypos = static_cast<float>(yposIn);
//
//   if (m_firstMouse)
//   {
//     m_lastX = xpos;
//     m_lastY = ypos;
//     m_firstMouse = false;
//   }
//
//   float xoffset = xpos - lastX;
//   float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top
//
//   lastX = xpos;
//   lastY = ypos;
//
//   camera.ProcessMouseMovement(xoffset, yoffset);
// }

// void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//   camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }

void Window::swapBuffers()
{
  glfwSwapBuffers(m_window);
}

void Window::pollEvents()
{
  glfwPollEvents();
}
