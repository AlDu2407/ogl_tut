#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

class IndexBuffer {
 public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();
  void use() const;
  void suspend() const;
  unsigned int get_count() const;

 private:
  unsigned int m_id, m_count;
};

#endif  // INDEX_BUFFER_HPP