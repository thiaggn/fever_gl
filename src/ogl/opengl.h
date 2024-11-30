#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace ogl {
    const GLbitfield color_buffer = GL_COLOR_BUFFER_BIT;

    const GLenum e_static_draw = GL_STATIC_DRAW;  // read-only, frequent reads
    const GLenum e_stream_draw = GL_STREAM_DRAW;  // read-only, less frequent reads
    const GLenum e_dynamic_draw = GL_DYNAMIC_DRAW;// read and write, frequent reads

    struct context {
    public:
        GLFWwindow *window;
        int should_continue() const;
        void poll_events();
        void swap_buffers() const;

    private:
        explicit context(GLFWwindow *w) : window(w){};
    };

    struct vertex_buffer {
        GLuint handle{};
        explicit vertex_buffer(GLenum mode, float data[], GLsizeiptr size);
    };

    struct vertex_shader {
        GLuint handle;
        explicit vertex_shader(const char *name);
    };

    struct frag_shader {
        GLuint handle;
        explicit frag_shader(const char *name);
    };

    struct shader_program {
    private:
        std::vector<GLuint> m_shader_handles;

    public:
        GLuint handle;
        shader_program();

        void add(vertex_shader shader);
        void add(frag_shader shader);
        void build() const;
        void use() const;
    };

    ogl::context init();
    void clear(GLbitfield f);
    void set_clear_color(float r, float g, float b, float a = 1.0f);
    void terminate();
}// namespace ogl