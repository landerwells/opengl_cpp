#ifndef WINDOW_H
#define WINDOW_H

#include "camera.h"

#include <GLFW/glfw3.h>

#include <string>

class Window
{
  public:
  Window(int width, int height, const std::string& title);
  ~Window();

  // void processInput(GLFWwindow* window);
  void processInput(Camera& camera);

  void swapBuffers();
  void pollEvents();
  bool shouldClose();

  private:
  static void framebuffer_size_callback(GLFWwindow* _window, int width, int height);
  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  static void mouse_callback(GLFWwindow* _window, double xposIn, double yposIn);

  GLFWwindow* m_window;
  int m_width;
  int m_height;

  float m_deltaTime = 0.0f;  // time between current frame and last frame
  float m_lastFrame = 0.0f;

  float m_lastX;
  float m_lastY;
  bool m_firstMouse = true;

};

#endif
