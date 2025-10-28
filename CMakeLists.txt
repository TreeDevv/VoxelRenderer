cmake_minimum_required(VERSION 3.21)
project(BlockClone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies via vcpkg (imported targets)
find_package(glfw3 CONFIG REQUIRED)               # target: glfw
find_package(glad CONFIG REQUIRED)                # target: glad::glad
find_package(glm CONFIG REQUIRED)                 # target: glm::glm
find_package(imgui CONFIG REQUIRED)               # target: imgui::imgui
find_package(spdlog CONFIG REQUIRED)              # target: spdlog::spdlog_header_only

add_library(NoiseHeader INTERFACE)
target_include_directories(NoiseHeader INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/external/noise")

# App
include_directories('external/noise/noise.hpp')

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    glfw
    glad::glad
    imgui::imgui
    glm::glm
    spdlog::spdlog_header_only
    NoiseHeader
)

# Copy runtime assets (shaders, textures) next to the binary
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/assets/shaders
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/shaders
)
