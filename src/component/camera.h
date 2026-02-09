#pragma once

struct Camera
{
  float fov{45.0f};
  // Potentially something in here or somewhere that will make the projection matrix
  float nearPlane{0.1f};
  float farPlane{100.0f};
  bool isActive{true};
};
