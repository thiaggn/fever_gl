#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <vector>



namespace gl {
    enum shader_type {
        e_vertex_shader = GL_VERTEX_SHADER,
        e_fragmt_shader = GL_FRAGMENT_SHADER
    };

    enum buffer_type {
        e_vertex_buffer = GL_ARRAY_BUFFER,
        e_element_buffer = GL_ELEMENT_ARRAY_BUFFER,
    };

    enum buffer_usage {
        e_static_draw = GL_STATIC_DRAW
    };

    enum data_type {
        e_float = GL_FLOAT,
        e_uint = GL_UNSIGNED_INT
    };

    enum draw_mode {
        e_triangles = GL_TRIANGLES
    };

    const GLuint c_color_buffer = GL_COLOR_BUFFER_BIT;

}

namespace gl {
    struct window {
        GLFWwindow *handle;

        int should_close() const;
        void poll_events();
        void swap_buffers() const;
    };

    struct program {
        unsigned int handle;
        std::vector<unsigned int> sh_handles;

        program();
        void attach(shader_type t, const char *path);
        void link() const;
        void use() const;
    };

    struct vertex_array {
    private:
        int m_offset;

    public:
        unsigned int handle;

        vertex_array();
        void bind() const;
        void wrap() const;
        void set_attribute(int location, int length, data_type type);
    };

    struct buffer {
        unsigned int handle;
        buffer_type btype;

        explicit buffer(gl::buffer_type btype);
        void write(GLsizeiptr size, void *data, gl::buffer_usage usage) const;
        template<typename T>
        void write(std::vector<T> data, gl::buffer_usage usage);
    };

}

namespace gl {
    window new_window(int width, int height, const char *title);
    void set_clear_color(float r, float g, float b, float a);
    void clear(GLuint mask);

    void draw_elements(draw_mode mode, int count, data_type type, int indices);

}
