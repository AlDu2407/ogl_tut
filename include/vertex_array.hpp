#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "vertex_buffer.hpp"
#include "buffer_layout.hpp"

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void add_buffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& buffer_layout);
  void use() const;
  void suspend() const;

 private:
  unsigned int m_id;
};

#endif  // VERTEX_ARRAY_HPP