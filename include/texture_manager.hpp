#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <texture2d.hpp>

#include <vector>

class TextureManager {
public:
  TextureManager();
  ~TextureManager();

  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;

  TextureManager(TextureManager&&) noexcept;
  TextureManager& operator=(TextureManager&&) noexcept;

  void load_texture(std::string texture_path);
  void delete_texture(unsigned int index);

  void use() const;
  void suspend() const;

  [[nodiscard]] unsigned int get_count() const { return m_count; }
  [[nodiscard]] const std::vector<Texture2D>& get_textures() const { return m_textures; }

  private:
  unsigned int m_count;
  std::vector<Texture2D> m_textures;
};

#endif  // TEXTURE_MANAGER_HPP