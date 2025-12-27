#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

class VertexBuffer {
 public:
  VertexBuffer(const void *data, unsigned int size);
  ~VertexBuffer();

  void use() const;
  void suspend() const;
 private:
  unsigned int m_id;
};

#endif  // VERTEX_BUFFER_HPP