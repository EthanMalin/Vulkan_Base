cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
cmake_policy(VERSION 3.7)

set(PROJECT_NAME PowerV0.1)
project(${PROJECT_NAME})

add_definitions(-std=c++17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(external)
include_directories(external/glm)
include_directories(external/stb_image)
include_directories(external/tiny_obj_loader)

# find libraries and build project
find_package(Vulkan)
find_package(glfw3 3.3 REQUIRED)
add_subdirectory(src)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/res)
