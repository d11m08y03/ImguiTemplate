cmake_minimum_required(VERSION 3.5)
project(Joeler)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES src/main.cpp)
set(IMGUI_SOURCES
  ./imgui/imgui.cpp
  ./imgui/imgui_demo.cpp
  ./imgui/imgui_draw.cpp
  ./imgui/imgui_widgets.cpp
  ./imgui/imgui_tables.cpp
  ./imgui/imgui_impl_sdlrenderer2.cpp
  ./imgui/imgui_impl_sdl2.cpp
)
include_directories(imgui)
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2)
