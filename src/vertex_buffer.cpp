#include "vertex_buffer.hpp"
#include <glad/gl.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_id);
}

void VertexBuffer::use() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::suspend() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}