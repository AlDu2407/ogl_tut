#include <texture2d.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Texture2D::Texture2D(std::string path, unsigned int index)
    : m_path(std::move(path)), m_index(index) {
  if (m_path.find(".png") != std::string::npos) {
    load_texture_from_file(TextureFormat::RGBA);
  } else {
    load_texture_from_file(TextureFormat::RGB);
  }
}

Texture2D::~Texture2D() { 
  std::cout << "Deleting texture ID: " << m_id << " at path: " << m_path << std::endl;
  glDeleteTextures(1, &m_id); 
}

Texture2D::Texture2D(Texture2D&& other) noexcept
    : m_path(std::move(other.m_path)),
      m_id(other.m_id),
      m_index(other.m_index) {
  other.m_id = 0;
  other.m_index = 0;
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
  if (this != &other) {
    glDeleteTextures(1, &m_id);
    m_path = std::move(other.m_path);
    m_id = other.m_id;
    m_index = other.m_index;
    other.m_id = 0;
    other.m_index = 0;
  }
  return *this;
}

void Texture2D::use() const {
  glActiveTexture(GL_TEXTURE0 + m_index);
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::suspend() const {
  glActiveTexture(GL_TEXTURE0 + m_index);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::load_texture_from_file(const TextureFormat& format) {
  int width, height, nr_channels;
  stbi_set_flip_vertically_on_load(1);
  unsigned char* data =
      stbi_load(m_path.c_str(), &width, &height, &nr_channels, 0);
  if (!data) {
    std::cerr << "Failed to load texture at path: " << m_path << std::endl;
    return;
  }
  glGenTextures(1, &m_id);
  use();
  GLenum gl_format = (format == TextureFormat::RGBA) ? GL_RGBA : GL_RGB;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  suspend();
  stbi_image_free(data);
}