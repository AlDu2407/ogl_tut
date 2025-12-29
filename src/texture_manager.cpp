#include <texture_manager.hpp>

#include <algorithm>

TextureManager::TextureManager() : m_count(0) {}

TextureManager::~TextureManager() { m_textures.clear(); }

TextureManager::TextureManager(TextureManager&& other) noexcept
    : m_count(other.m_count), m_textures(std::move(other.m_textures)) {
  other.m_count = 0;
}

TextureManager& TextureManager::operator=(TextureManager&& other) noexcept {
  if (this != &other) {
    m_count = other.m_count;
    m_textures = std::move(other.m_textures);
    other.m_count = 0;
  }
  return *this;
}

void TextureManager::load_texture(std::string texture_path) {
  m_textures.emplace_back(std::move(texture_path), m_count++);
}

void TextureManager::delete_texture(unsigned int index) {
  auto it = std::remove_if(m_textures.begin(), m_textures.end(),
                           [index](const Texture2D& texture) {
                             return texture.get_index() == index;
                           });
  if (it != m_textures.end()) {
    m_textures.erase(it, m_textures.end());
    --m_count;
  }
}

void TextureManager::use() const {
  for (const auto& texture : m_textures) {
    texture.use();
  }
}

void TextureManager::suspend() const {
  for (const auto& texture : m_textures) {
    texture.suspend();
  }
}