#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

std::string Utils::read_file(const std::string &file_path) {
  std::ifstream file(file_path, std::ios::binary | std::ios::ate);
  if (!file) return {};

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::string buffer(size, '\0');
  if (!file.read(buffer.data(), size)) {
    return {};
  }
  return buffer;
}

void Utils::check_compile_errors(unsigned int shader, const std::string& type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- \n";
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- \n";
    }
  }
}
