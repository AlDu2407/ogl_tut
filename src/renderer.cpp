#include "renderer.hpp"
#include "program.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "texture_manager.hpp"
#include <glad/gl.h>

void Renderer::clear() const {
  glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw_elements(const VertexArray& vertex_array,
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
  // glDrawArrays(GL_TRIANGLES, 0, index_buffer.get_count());
  glDrawElements(GL_TRIANGLES, index_buffer.get_count(), GL_UNSIGNED_INT,
                 nullptr);
  texture_manager.suspend();
  index_buffer.suspend();
  vertex_array.suspend();
  program.suspend();
}

void Renderer::draw_arrays(const VertexArray& vertex_array,
                           const TextureManager& texture_manager,
                           Program& program, unsigned int count) const {
  program.use();
  vertex_array.use();
  texture_manager.use();
  for (unsigned int i = 0; i < texture_manager.get_count(); ++i) {
    program.set_uniform_1i("texture" + std::to_string(i + 1), i);
  }
  glDrawArrays(GL_TRIANGLES, 0, count);
  texture_manager.suspend();
  vertex_array.suspend();
  program.suspend();
}