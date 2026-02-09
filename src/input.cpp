#include "input.h"

#include <cstring>

// Static member initialization
GLFWwindow* Input::s_window = nullptr;
glm::vec2 Input::s_mousePos = glm::vec2(0.0f);
glm::vec2 Input::s_lastMousePos = glm::vec2(0.0f);
glm::vec2 Input::s_mouseDelta = glm::vec2(0.0f);
float Input::s_scrollDelta = 0.0f;
bool Input::s_firstMouse = true;
// bool Input::m_mouseMoved = false;
bool Input::s_keyState[GLFW_KEY_LAST] = {false};
bool Input::s_lastKeyState[GLFW_KEY_LAST] = {false};

void Input::init(GLFWwindow* window)
{
  s_window = window;

  // Set GLFW callbacks
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetScrollCallback(window, scrollCallback);

  // Initialize mouse position
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  s_mousePos = glm::vec2((float)xpos, (float)ypos);
  s_lastMousePos = s_mousePos;
}

void Input::update()
{
  // Update keyboard state
  std::memcpy(s_lastKeyState, s_keyState, sizeof(s_keyState));
  for (int key = 0; key < GLFW_KEY_LAST; key++)
  {
    s_keyState[key] = (glfwGetKey(s_window, key) == GLFW_PRESS);
  }

  s_mouseDelta = glm::vec2(0.0f);
  s_scrollDelta = 0.0f;
  // m_mouseMoved = false;
}

bool Input::isKeyPressed(int key)
{
  if (key < 0 || key >= GLFW_KEY_LAST)
    return false;
  return s_keyState[key];
}

bool Input::isKeyDown(int key)
{
  if (key < 0 || key >= GLFW_KEY_LAST)
    return false;
  return s_keyState[key] && !s_lastKeyState[key];
}

bool Input::isKeyReleased(int key)
{
  if (key < 0 || key >= GLFW_KEY_LAST)
    return false;
  return !s_keyState[key] && s_lastKeyState[key];
}

bool Input::isMouseButtonPressed(int button)
{
  return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
}

glm::vec2 Input::getMousePosition()
{
  return s_mousePos;
}

glm::vec2 Input::getMouseDelta()
{
  return s_mouseDelta;
}

float Input::getScrollDelta()
{
  return s_scrollDelta;
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
  s_mousePos = glm::vec2((float)xpos, (float)ypos);

  if (s_firstMouse)
  {
    s_lastMousePos = s_mousePos;
    s_firstMouse = false;
    return;  // Don't process delta on first mouse movement
  }

  // ACCUMULATE the delta instead of overwriting
  float deltaX = s_mousePos.x - s_lastMousePos.x;
  float deltaY = s_mousePos.y - s_lastMousePos.y;  // GLFW y-coordinates go from top to bottom

  s_mouseDelta.x += deltaX;  // += not =
  s_mouseDelta.y += deltaY;  // += not =

  s_lastMousePos = s_mousePos;
  // m_mouseMoved = true;
}

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
  s_scrollDelta = (float)yoffset;
}
