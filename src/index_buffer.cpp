#include "index_buffer.hpp"
#include "renderer.hpp"
#include <glad/gl.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count) {
  ASSERT(sizeof(unsigned int) == sizeof(GLuint));

  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &m_id);
}

void IndexBuffer::use() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::suspend() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::get_count() const {
  return m_count;
}