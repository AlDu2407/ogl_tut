#include <program.hpp>
#include <utils.hpp>

Program::Program(const std::string &vertex_path, const std::string &fragment_path) {
  auto vertex_shader_str = Utils::read_file(vertex_path);
  auto fragment_shader_str = Utils::read_file(fragment_path);
  compile_program(vertex_shader_str, fragment_shader_str);
}

Program::~Program() {
  glDeleteProgram(m_id);
}

void Program::use() const { glUseProgram(m_id); }

void Program::suspend() const { glUseProgram(0); }

void Program::set_uniform_1i(const std::string &name, int value) {
  glUniform1i(get_uniform_location(name), value);
}

void Program::set_uniform_1f(const std::string &name, float value) {
  glUniform1f(get_uniform_location(name), value);
}

void Program::set_uniform_4f(const std::string &name, float x, float y,
                            float z, float w) {
  glUniform4f(get_uniform_location(name), x, y, z, w);
}

void Program::set_uniform_matrix4fv(const std::string &name, const float *value) {
  glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, value);
}


void Program::compile_program(const std::string &vertex_code,
                              const std::string &fragment_code) {
  unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
  const char *vertex_code_c_str = vertex_code.c_str();
  glShaderSource(vertex_shader_id, 1, &vertex_code_c_str, nullptr);
  glCompileShader(vertex_shader_id);
  Utils::check_compile_errors(vertex_shader_id, "VERTEX");
  unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  const char *fragment_code_c_str = fragment_code.c_str();
  glShaderSource(fragment_shader_id, 1, &fragment_code_c_str, nullptr);
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

int Program::get_uniform_location(const std::string &name) {
  if (m_location_cache.find(name) != m_location_cache.end())
    return m_location_cache[name];

  int location = glGetUniformLocation(m_id, name.c_str());
  if (location == -1)
    std::cerr << "Warning: uniform '" << name
              << "' doesn't exist or is not used in the shader!\n";

  m_location_cache[name] = location;
  return location;
}