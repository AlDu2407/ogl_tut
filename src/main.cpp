#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"
#include "program.hpp"
#include "buffer_layout.hpp"
#include <vertex_buffer.hpp>
#include <vertex_array.hpp>
#include <index_buffer.hpp>
#include <renderer.hpp>

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << " <vertex_shader_path> <fragment_shader_path>\n";
    return -1;
  }

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
      glfwCreateWindow(800, 600, "OpenGL Tutorial", nullptr, nullptr);
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

  const char* vertex_path = argv[1];
  const char* fragment_path = argv[2];
  Program program(vertex_path, fragment_path);

  float positions[] = {-0.5f, -0.5f, 0.5f, -0.5, 0.5f, 0.5f, -0.5f, 0.5f};

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  unsigned int size = 4 * 2 * sizeof(float);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  VertexArray vertex_array;
  VertexBuffer vertex_buffer(positions, size);

  VertexBufferLayout buffer_layout;
  buffer_layout.push<float>(2);
  vertex_array.add_buffer(vertex_buffer, buffer_layout);
  IndexBuffer index_buffer(indices, sizeof(indices) / sizeof(unsigned int));
  program.use();
  
  vertex_array.suspend();
  program.suspend();
  vertex_buffer.suspend();
  index_buffer.suspend();
  Renderer renderer;

  // float vertices[] = {
  //   -0.5f, -0.5f, 0.0f, // Position
  //   1.0f, 0.0f, 0.0f, // Color
  //   0.5f, -0.5f, 0.0f, //
  //   0.0f, 1.0f, 0.0f, //
  //   0.0f, 0.5f, 0.0f, //
  //   0.0f, 0.0f, 1.0f  //
  // };

  // unsigned int vao, vbo;
  // glCreateVertexArrays(1, &vao);
  // glCreateBuffers(1, &vbo);
  // glBindVertexArray(vao);

  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  // (void*)0); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 *
  // sizeof(float), (void*)(3 * sizeof(float))); glEnableVertexAttribArray(0);
  // glEnableVertexAttribArray(1);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // program.use();
    // glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);
    // program.suspend();

    renderer.clear();

    renderer.draw(vertex_array, index_buffer, program);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
