cmake_minimum_required(VERSION 3.28)
project(fever_gl)

set(CMAKE_CXX_STANDARD 17)

# ----------------------- fever_gl -----------------------
add_executable(fever_gl
        src/main.cc
        src/util/file.cc
        src/gl/opengl.h
        src/gl/opengl.cc
        src/panic/gl.h
)

target_include_directories(fever_gl PUBLIC "src")

set_target_properties(fever_gl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# --------------------- dependencies ---------------------
add_subdirectory("deps/glfw-3.4")
target_link_libraries(fever_gl glfw)

add_subdirectory("deps/glad-4.2")
target_link_libraries(fever_gl glad)