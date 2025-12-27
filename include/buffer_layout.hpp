#ifndef BUFFER_LAYOUT_HPP
#define BUFFER_LAYOUT_HPP

#include <glad/gl.h>
#include <iostream>
#include <vector>

struct VertexBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  VertexBufferElement(unsigned int type, unsigned int count,
                      unsigned char normalized = GL_FALSE)
      : type(type), count(count), normalized(normalized) {}

  static unsigned int get_size_of_type(unsigned int type) {
    switch (type) {
      case GL_FLOAT:
        return 4;
      case GL_UNSIGNED_INT:
        return 4;
      case GL_INT:
        return 4;
      case GL_UNSIGNED_BYTE:
        return 1;
      default:
        std::cerr << "Unknown type in VertexBufferElement get_size_of_type\n";
        return 0;
    }
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const VertexBufferElement& element) {
    return os << "Type: " << element.type << ", Count: " << element.count
              << ", Normalized: " << element.normalized << '\n';
  }
};

class VertexBufferLayout {
 public:
  VertexBufferLayout() : m_stride(0) {}
  ~VertexBufferLayout() = default;

  template <typename GLType>
  void push(unsigned int count);

  const std::vector<VertexBufferElement>& get_elements() const;
  unsigned int get_stride() const;

 private:
  std::vector<VertexBufferElement> m_elements;
  unsigned int m_stride;
};

#endif  // BUFFER_LAYOUT_HPP