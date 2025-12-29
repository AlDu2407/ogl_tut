#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include <glad/gl.h>

#include <string>

enum class TextureFormat {
  RGB,
  RGBA
};

class Texture2D {
 public:
  Texture2D(std::string path, unsigned int index);
  ~Texture2D();

  Texture2D(const Texture2D&) = delete;
  Texture2D& operator=(const Texture2D&) = delete;

  Texture2D(Texture2D&&) noexcept;
  Texture2D& operator=(Texture2D&&) noexcept;

  void use() const;
  void suspend() const;

  [[nodiscard]] unsigned int get_index() const { return m_index; }
  [[nodiscard]] unsigned int get_id() const { return m_id; }
  [[nodiscard]] const std::string& get_path() const { return m_path; }

 private:
  std::string m_path;
  unsigned int m_id, m_index;

  void load_texture_from_file(const TextureFormat &format);
};

#endif  // TEXTURE_2D_HPP