#include "vertex_array.hpp"

#include <glad/gl.h>
#include <buffer_layout.hpp>

VertexArray::VertexArray() { glGenVertexArrays(1, &m_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

void VertexArray::add_buffer(const VertexBuffer& vertex_buffer,
                             const VertexBufferLayout& buffer_layout) {
  use();
  vertex_buffer.use();
  const auto& elements = buffer_layout.get_elements();
  size_t offset = 0;
  for (auto i = 0; i < elements.size(); ++i) {
    const auto& element = elements[i];
    std::cout << element << '\n';
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, element.count, element.type, element.normalized,
                          buffer_layout.get_stride(), (const void*)offset);
    offset +=
        element.count * VertexBufferElement::get_size_of_type(element.type);
  }
}

void VertexArray::use() const { glBindVertexArray(m_id); }

void VertexArray::suspend() const { glBindVertexArray(0); }