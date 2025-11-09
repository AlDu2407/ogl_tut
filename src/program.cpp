#include "program.hpp"
#include "utils.hpp"

Program::Program(const char* vertex_path, const char* fragment_path) {
  auto vertex_shader_str = Utils::read_file(vertex_path);
  auto vertex_code = vertex_shader_str.c_str();
  auto fragment_shader_str = Utils::read_file(fragment_path);
  auto fragment_code = fragment_shader_str.c_str();
  compile_program(vertex_code, fragment_code);
}

Program::~Program() {
  glDeleteProgram(m_id);
}

void Program::use() { glUseProgram(m_id); }

void Program::suspend() { glUseProgram(0); }

void Program::compile_program(const char* vertex_code,
                              const char* fragment_code) {
  unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader_id, 1, &vertex_code, nullptr);
  glCompileShader(vertex_shader_id);
  Utils::check_compile_errors(vertex_shader_id, "VERTEX");
  unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_id, 1, &fragment_code, nullptr);
  glCompileShader(fragment_shader_id);
  Utils::check_compile_errors(fragment_shader_id, "FRAGMENT");
  m_id = glCreateProgram();
  glAttachShader(m_id, vertex_shader_id);
  glAttachShader(m_id, fragment_shader_id);
  glLinkProgram(m_id);
  Utils::check_compile_errors(m_id, "PROGRAM");

  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);
}
