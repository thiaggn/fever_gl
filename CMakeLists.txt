cmake_minimum_required(VERSION 3.28)
project(fever_gl)

set(CMAKE_CXX_STANDARD 17)

# ----------------------- fever_gl -----------------------
add_executable(fever_gl
        "src/main.cc"
        "src/ogl/opengl.cc"
        "src/util/file.cc"
)

target_include_directories(fever_gl PUBLIC "src")

# --------------------- dependencies ---------------------
add_subdirectory("deps/glfw-3.4")
target_link_libraries(fever_gl glfw)

add_subdirectory("deps/glad-4.2")
target_link_libraries(fever_gl glad)