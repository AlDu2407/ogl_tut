#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <utils.hpp>
#include <camera.hpp>
#include <program.hpp>
#include <buffer_layout.hpp>
#include <vertex_buffer.hpp>
#include <vertex_array.hpp>
#include <index_buffer.hpp>
#include <renderer.hpp>
#include <texture_manager.hpp>
#include <debug.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 1400
#define HEIGHT 960

static void process_input(GLFWwindow* window, Camera& camera,
                          float delta_time) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  const float camera_speed = 2.0f * delta_time;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.update_position(camera.get_position() +
                           camera_speed * camera.get_front());
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.update_position(camera.get_position() -
                           camera_speed * camera.get_front());
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.update_position(
        camera.get_position() -
        glm::normalize(glm::cross(camera.get_front(), camera.get_up())) *
            camera_speed);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.update_position(
        camera.get_position() +
        glm::normalize(glm::cross(camera.get_front(), camera.get_up())) *
            camera_speed);
  }
}

int main(int argc, char** argv) {
  std::cout << "Hello, OpenGL Tutorial!\n";

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  std::cout << "GLFW initialized successfully!\n";
  std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Tutorial", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cerr << "Failed to initialize GLAD\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  std::cout << "GLAD initialized successfully!\n";
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

  glDebugMessageCallback(gl_debug_output, nullptr);

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow* /*window*/, int width, int height) {
        glViewport(0, 0, width, height);
      });

  std::string vertex_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/shaders/vertex.glsl");
  std::string fragment_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/shaders/fragment.glsl");
  std::string container_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/textures/container.jpg");
  std::string awesomeface_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/textures/awesomeface.png");

  Program program(vertex_path, fragment_path);

  // float first[] = {
  //     // positions        // colors         // texCoords
  //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
  //     0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
  //     -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
  //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top rights
  // };

  // float vertices[] = {
  //     // positions        // colors         // texCoords
  //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
  //     0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  //     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  //     -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

  //     -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  //     0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
  //     -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

  //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  //     0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  //     -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  //     0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

  //     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  //     -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
  //     -0.5f, 0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  // };

  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f, 0.0f,
      0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.5f,  -0.5f,
      0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
      1.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,

      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,
      0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  -0.5f, 0.5f,  0.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,
      -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
      1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f};

  unsigned int indices[] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                            12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                            24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  unsigned int indice_size = sizeof(indices) / sizeof(unsigned int);
  unsigned int size_bytes = sizeof(vertices);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  VertexArray vertex_array;
  VertexBuffer vertex_buffer(vertices, size_bytes);
  VertexBufferLayout buffer_layout;
  buffer_layout.push<float>(3);
  buffer_layout.push<float>(3);
  buffer_layout.push<float>(2);
  vertex_array.add_buffer(vertex_buffer, buffer_layout);
  IndexBuffer index_buffer(indices, indice_size);
  program.use();
  vertex_array.suspend();
  program.suspend();
  vertex_buffer.suspend();
  index_buffer.suspend();

  Renderer renderer;
  TextureManager texture_manager;
  texture_manager.load_texture(container_path);
  texture_manager.load_texture(awesomeface_path);

  auto width = static_cast<float>(WIDTH);
  auto height = static_cast<float>(HEIGHT);

  glm::vec3 cube_positions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  float delta_time = 0.0f;
  float last_frame = 0.0f;
  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, -1.0f));

  while (!glfwWindowShouldClose(window)) {
    renderer.clear();
    auto time = static_cast<float>(glfwGetTime());
    delta_time = time - last_frame;
    last_frame = time;

    process_input(window, camera, delta_time);
    // auto x = static_cast<float>(sin(time));
    // glm::mat4 transform(1.0f);
    // transform = glm::translate(transform, glm::vec3(x, 0.0f, 0.0f));
    // transform = glm::rotate(transform, time, glm::vec3(0.0f, 0.0f, 1.0f));
    // transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
    for (unsigned int i = 0; i < 10; ++i) {
      glm::mat4 model(1.0f);
      model = glm::translate(model, cube_positions[i]);
      float angle = 20.0f * i;
      if (i % 3 == 0) {
        angle = time * 25.0f;
      }
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      glm::mat4 view = camera.get_view_matrix();
      glm::mat4 projection =
          glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
      program.use();
      program.set_uniform_matrix4fv("model", glm::value_ptr(model));
      program.set_uniform_matrix4fv("view", glm::value_ptr(view));
      program.set_uniform_matrix4fv("projection", glm::value_ptr(projection));
      program.suspend();
      renderer.draw_elements(vertex_array, index_buffer, texture_manager,
                             program);
    }
    // glm::mat4 model(1.0f);
    // model = glm::rotate(model, time * glm::radians(55.0f),
    //                     glm::vec3(0.5f, 1.0f, 0.0f));
    // program.use();
    // program.set_uniform_matrix4fv("model", glm::value_ptr(model));
    // program.suspend();

    // renderer.draw_elements(vertex_array, index_buffer, texture_manager,
    //                        program);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
