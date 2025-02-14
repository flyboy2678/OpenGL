cmake_minimum_required(VERSION 3.31)
project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Link directories
link_directories(${PROJECT_SOURCE_DIR}/libs)

# Add source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add glm as a header-only library
add_subdirectory(include/glm)

# Add executable
add_executable(OpenGLProject ${SOURCES})

# Link GLEW
# Always link glew first before anyother openGL libaries
target_compile_definitions(OpenGLProject PRIVATE GLEW_STATIC)
target_link_libraries(OpenGLProject glew32s)

# Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLProject OpenGL::GL)

# Link GLFW
target_link_libraries(OpenGLProject ${PROJECT_SOURCE_DIR}/libs/libglfw3.a)

# Link glm
target_link_libraries(OpenGLProject glm::glm)

# Link Windows system libraries
target_link_libraries(OpenGLProject User32 Shell32 Gdi32)