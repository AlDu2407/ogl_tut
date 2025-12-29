#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <unordered_map>
#include <string>
#include <glad/gl.h>

class Program {
 public:
  Program(const std::string& vertex_path, const std::string& fragment_path);
  ~Program();

  Program(const Program&) = delete;
  Program& operator=(const Program&) = delete;

  Program(Program&&) noexcept = default;
  Program& operator=(Program&&) noexcept = default;

  void use() const;
  void suspend() const;
  [[nodiscard]] unsigned int get_id() const { return m_id; }

  void set_uniform_1i(const std::string& name, int value);
  void set_uniform_1f(const std::string& name, float value);
  void set_uniform_4f(const std::string& name, float x, float y, float z,
                      float w);
  void set_uniform_matrix4fv(const std::string& name, const float* value);

 private:
  unsigned int m_id;
  std::unordered_map<std::string, int> m_location_cache;

  void compile_program(const std::string& vertex_code,
                       const std::string& fragment_code);

  [[nodiscard]] int get_uniform_location(const std::string& name);
};

#endif  // PROGRAM_HPP