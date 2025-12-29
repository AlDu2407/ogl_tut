#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace Utils {

std::string read_file(const std::string &file_path);
void check_compile_errors(unsigned int shader, const std::string& type);

}  // namespace Utils

#endif  // UTILS_HPP