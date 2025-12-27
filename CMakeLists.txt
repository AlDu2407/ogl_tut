cmake_minimum_required(VERSION 3.20)
project(ogl_tut VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(deps)

# Include directories
include_directories(includes)

# Collect all source files from src/ directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
# Collect all header files from includes/ directory (optional, for IDE support)
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Create executable with all source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


# Add include directories to target
target_include_directories(${PROJECT_NAME} PRIVATE
    include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenGL
    glad_gl_core_43
    glfw
)
