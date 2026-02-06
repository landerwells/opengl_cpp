#pragma once

#include <GLFW/glfw3.h>

#include <string>

class Window
{
  public:
  Window(int width, int height, const std::string& title);
  ~Window();

  void swapBuffers();
  void pollEvents();
  bool shouldClose();

  GLFWwindow* getWindow() { return m_window; }

  void captureMouse(bool capture);

  private:
  static void framebuffer_size_callback(GLFWwindow* _window, int width, int height);

  GLFWwindow* m_window;
  int m_width;
  int m_height;

  float m_deltaTime = 0.0f;  // time between current frame and last frame
  float m_lastFrame = 0.0f;
};
