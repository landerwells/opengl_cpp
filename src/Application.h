#ifndef APPLICATION_H
#define APPLICATION_H

#include "Renderer.h"
#include "Window.h"
#include "camera.h"

class Application
{
  public:
  void run() {
    while (!m_window.shouldClose()) {
      processInput();
    }
  }

  private:
  Window m_window;
  Camera m_camera;
  Renderer m_renderer;
};

#endif
