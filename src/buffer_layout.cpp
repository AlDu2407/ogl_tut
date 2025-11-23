#include "buffer_layout.hpp"

template <>
void VertexBufferLayout::push<float>(unsigned int count) {
  m_elements.push_back(VertexBufferElement(GL_FLOAT, count));
  m_stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
  m_elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count));
  m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned short>(unsigned int count) {
  m_elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count));
  m_stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
}

const std::vector<VertexBufferElement>& VertexBufferLayout::get_elements()
    const {
  return m_elements;
}

unsigned int VertexBufferLayout::get_stride() const {
  return m_stride;
}