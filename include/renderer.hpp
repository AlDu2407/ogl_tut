#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "vertex_array.hpp"
#include "program.hpp"
#include "index_buffer.hpp"

#define ASSERT(X) \
  if (!(X)) __builtin_trap();

class Renderer {
 public:
  void clear() const;
  void draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer,
            const Program& program) const;
};

#endif  // RENDERER_HPP