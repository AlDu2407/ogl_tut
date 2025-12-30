#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
  public:
    Camera(glm::vec3 start_position, glm::vec3 start_up, glm::vec3 start_front);
    ~Camera();

    void update_position(const glm::vec3& new_position);
    void update_front(const glm::vec3& new_front);
    void update_up(const glm::vec3& new_up);
    glm::mat4 get_view_matrix() const;
    glm::vec3 get_position() const {
      return position;
    }
    glm::vec3 get_front() const {
      return front;
    }
    glm::vec3 get_up() const {
      return up;
    }

  private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
};

#endif // CAMERA_HPP