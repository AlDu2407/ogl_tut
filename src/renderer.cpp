#include "renderer.hpp"
#include "program.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include <glad/gl.h>

void Renderer::clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::draw(const VertexArray& vertex_array,
                    const IndexBuffer& index_buffer,
                    const Program& program) const {
  program.use();
  vertex_array.use();
  index_buffer.use();
  glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT, nullptr);
}