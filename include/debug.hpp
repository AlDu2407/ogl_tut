#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <glad/gl.h>

void gl_debug_output(GLenum source, GLenum type, unsigned int id,
                     GLenum severity, GLsizei length, const char* message,
                     const void* user_param);

#endif  // DEBUG_HPP