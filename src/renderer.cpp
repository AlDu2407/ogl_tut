#include "renderer.hpp"
#include "program.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "texture_manager.hpp"
#include <glad/gl.h>

void Renderer::clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::draw(const VertexArray& vertex_array,
                    const IndexBuffer& index_buffer,
                    const TextureManager& texture_manager,
                    Program& program) const {
  program.use();
  vertex_array.use();
  index_buffer.use();
  texture_manager.use();
  for (unsigned int i = 0; i < texture_manager.get_count(); ++i) {
    program.set_uniform_1i("texture" + std::to_string(i + 1), i);
  }
  glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT,
                 nullptr);
}