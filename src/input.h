#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Static input system - decouples input handling from GLFW
class Input
{
  public:
  // Initialize with GLFW window
  static void init(GLFWwindow* window);

  // Update state (call once per frame)
  static void update();

  // Keyboard input
  static bool isKeyPressed(int key);
  static bool isKeyDown(int key);  // True only on first frame pressed
  static bool isKeyReleased(int key);

  // Mouse input
  // static bool m_mouseMoved;
  static bool isMouseButtonPressed(int button);
  static glm::vec2 getMousePosition();
  static glm::vec2 getMouseDelta();
  static float getScrollDelta();

  // Mouse callbacks (called by GLFW)
  static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
  static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

  private:
  static GLFWwindow* s_window;

  // Mouse state
  static glm::vec2 s_mousePos;
  static glm::vec2 s_lastMousePos;
  static glm::vec2 s_mouseDelta;
  static float s_scrollDelta;
  static bool s_firstMouse;

  // Keyboard state (for key down/released detection)
  static bool s_keyState[GLFW_KEY_LAST];
  static bool s_lastKeyState[GLFW_KEY_LAST];
};
