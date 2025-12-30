#include <camera.hpp>

Camera::Camera(glm::vec3 start_position, glm::vec3 start_up, glm::vec3 start_front)
    : position(start_position), up(start_up), front(start_front) {}

Camera::~Camera() {}

void Camera::update_position(const glm::vec3& new_position) {
  position = std::move(new_position);
}

void Camera::update_front(const glm::vec3& new_front) {
  front = std::move(new_front);
}

void Camera::update_up(const glm::vec3& new_up) {
  up = std::move(new_up);
}

glm::mat4 Camera::get_view_matrix() const {
  return glm::lookAt(position, position + front, up);
}
