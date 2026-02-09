#include "camera.h"
#include "component/transform.h"
#include "coordinator.h"
#include "input.h"
#include "player_controller.h"
#include "renderer.h"
#include "shader.h"
#include "system/camera_system.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/fwd.hpp"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const char* glsl_version = "#version 330";

const glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Global coordinator definition (declared extern in ecs_constants.h)
Coordinator g_coordinator;

int main()
{
  Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL");
  window.captureMouse(true);

  Transform t;
  Input::init(window.getWindow());

  // Camera camera(glm::vec3(0.0f, 2.0f, 5.0f));

  // PlayerController player(glm::vec3(0.0f, 2.0f, 5.0f), &camera);
  // player.setMoveSpeed(5.0f);
  // player.setGroundLevel(0.0f);

  // Could likely abstract this away into a shape file that I could specify what kind
  // of shape that I want to spawn.
  float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
                      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

                      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
                      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
                      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  // world space positions of our cubes
  glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(2.0f, 5.0f, -15.0f),
                               glm::vec3(-1.5f, -2.2f, -2.5f),
                               glm::vec3(-3.8f, -2.0f, -12.3f),
                               glm::vec3(2.4f, -0.4f, -3.5f),
                               glm::vec3(-1.7f, 3.0f, -7.5f),
                               glm::vec3(1.3f, -2.0f, -2.5f),
                               glm::vec3(1.5f, 2.0f, -2.5f),
                               glm::vec3(1.5f, 0.2f, -1.5f),
                               glm::vec3(-1.3f, 1.0f, -1.5f)};

  VertexBuffer vb(vertices, sizeof(vertices));

  // Register ECS components
  g_coordinator.RegisterComponent<Transform>();
  g_coordinator.RegisterComponent<Camera>();

  // Register ECS systems
  auto camera_system = g_coordinator.registerSystem<CameraControlSystem>();
  Signature cameraSig;
  cameraSig.set(g_coordinator.GetComponentType<Transform>());
  cameraSig.set(g_coordinator.GetComponentType<Camera>());
  g_coordinator.SetSystemSignature<CameraControlSystem>(cameraSig);

  VertexArray va;
  VertexBufferLayout layout;
  // Define position attribute (3 floats)
  layout.push<float>(3);
  // Define texture coordinate attribute (2 floats)
  layout.push<float>(2);
  va.addBuffer(vb, layout);

  VertexArray lightVAO;
  lightVAO.addBuffer(vb, layout);

  // Shader
  Shader program("res/shaders/basic.glsl");
  Shader light("res/shaders/lighting.glsl");
  Shader sdf("res/shaders/sdf.glsl");
  program.bind();

  Texture texture1("res/textures/container.jpg", false);
  texture1.bind(0);
  program.setUniform("texture1", 0);

  Texture texture2("res/textures/awesomeface.png", true);
  texture2.bind(1);
  program.setUniform("texture2", 1);

  Renderer renderer(0.1f, 0.1f, 0.1f);
  renderer.enableDepthTest();

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (!window.shouldClose())
  {
    // TODO Abstract this into Time
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input
    if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(window.getWindow(), true);
    }

    player.update(deltaTime);

    Input::update();

    renderer.clear();

    texture1.bind(0);
    texture2.bind(1);

    program.bind();
    light.setUniform("objectColor", 1.0f, 0.5f, 0.31f);
    light.setUniform("lightColor", 1.0f, 1.0f, 1.0f);

    // This should all be handled by the camera system
    // What should the camera component even have?
    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    program.setUniform("projection", projection);

    // camera/view transformation
    glm::mat4 view = camera.GetViewMatrix();
    program.setUniform("view", view);

    // render boxes
    va.bind();

    glm::mat4 model = glm::mat4(1.0f);  // make sure to initialize matrix to identity matrix first
    for (unsigned int i = 0; i < 10; i++)
    {
      // calculate the model matrix for each object and pass it to shader before drawing
      model = glm::mat4(1.0f);  // make sure to initialize matrix to identity matrix first
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      program.setUniform("model", model);

      renderer.draw(va, program, 36);
    }

    light.bind();
    light.setUniform("objectColor", 1.0f, 0.5f, 0.31f);
    light.setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    light.setUniform("projection", projection);
    light.setUniform("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    light.setUniform("model", model);
    lightVAO.bind();
    renderer.draw(lightVAO, light, 36);

    glm::vec3 sdfPos(-1.2f, 1.0f, 2.0f);
    float sdfRadius = 1.0f;  // Sphere radius
    sdf.bind();
    sdf.setUniform("objectColor", 0.0f, 0.0f, 1.0);
    sdf.setUniform("projection", projection);
    sdf.setUniform("view", view);
    // Create bounding box slightly larger than the sphere
    model = glm::mat4(1.0f);
    model = glm::translate(model, sdfPos);
    model = glm::scale(model, glm::vec3(sdfRadius * 2.0f));  // Bounding box size
    sdf.setUniform("model", model);
    // Pass SDF-specific uniforms
    float time = glfwGetTime();
    sdf.setUniform("time", time);
    sdf.setUniform("cameraPos", camera.Position);
    sdf.setUniform("sphereCenter", sdfPos);
    sdf.setUniform("sphereRadius", sdfRadius);

    // Bind the cube VAO (this is the bounding box)
    lightVAO.bind();  // Using cube geometry as bounding box

    // Draw the bounding box (raymarching happens in fragment shader)
    renderer.draw(lightVAO, sdf, 36);

    window.swapBuffers();
    window.pollEvents();
  }
  // TODO Error handling

  return 0;
}
