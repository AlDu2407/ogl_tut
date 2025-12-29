#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <utils.hpp>
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
      glfwCreateWindow(1400, 960, "OpenGL Tutorial", nullptr, nullptr);
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

  std::string vertex_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/shaders/vertex.glsl");
  std::string fragment_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/shaders/fragment.glsl");
  std::string container_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/textures/container.jpg");
  std::string awesomeface_path(
      "/home/aldu/projects/cpp/ogl_tut/assets/textures/awesomeface.png");

  Program program(vertex_path, fragment_path);

  float first[] = {
      // positions  // colors         // texCoords
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left
      0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top rights
  };

  unsigned int indices[] = {0, 1, 2, 3, 1, 2};
  // (2 floats for position + 3 floats for color + 2 floats for texture
  // coordinates) * 4 vertices
  unsigned int size = (2 + 3 + 2) * 4 * sizeof(float);
  unsigned int indice_size = sizeof(indices) / sizeof(unsigned int);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  VertexArray vertex_array;
  VertexBuffer vertex_buffer(first, size);
  VertexBufferLayout buffer_layout;
  buffer_layout.push<float>(2);
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

  while (!glfwWindowShouldClose(window)) {
    renderer.clear();
    auto time = static_cast<float>(glfwGetTime());
    auto x = static_cast<float>(sin(time));
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::vec3(x, 0.0f, 0.0f));
    transform = glm::rotate(transform, time, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
    program.use();
    program.set_uniform_matrix4fv("transform", glm::value_ptr(transform));
    program.suspend();

    renderer.draw(vertex_array, index_buffer, texture_manager, program);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
