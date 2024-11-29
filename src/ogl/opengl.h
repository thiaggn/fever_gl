#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace ogl {
    const GLbitfield color_buffer = GL_COLOR_BUFFER_BIT;

    // Buffer apenas para leitura, com alta frequência de leitura
    const GLenum static_draw = GL_STATIC_DRAW;

    // Buffer apenas para leitura, com pouca frequência de leitura
    const GLenum stream_draw = GL_STREAM_DRAW;

    // Buffer de leitura e escrita
    const GLenum dynamic_draw = GL_DYNAMIC_DRAW;

    struct context {
        GLFWwindow *window;

        explicit context(GLFWwindow *w): window(w) {};
        int ShouldContinue() const;
        void PollEvents();
        void SwapBuffers() const;
    };

    struct vertex_buffer {
        GLuint handle;
        explicit vertex_buffer(GLenum mode, std::vector<float> vertex);
    };

    struct vertex_shader {
        GLuint handle;
        explicit vertex_shader(const char* name);
    };

    ogl::context Init();
    void Clear(GLbitfield f);
    void SetClearColor(float r, float g, float b, float a = 1.0f);
    void Terminate();
}