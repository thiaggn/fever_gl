#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <vector>



namespace gl {
    enum shader_type {
        e_vertexShader = GL_VERTEX_SHADER,
        e_fragShader = GL_FRAGMENT_SHADER
    };

    enum buffer_type {
        e_vertexBuffer = GL_ARRAY_BUFFER,
        e_elementBuffer = GL_ELEMENT_ARRAY_BUFFER,
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

    const GLuint c_colorBuffer = GL_COLOR_BUFFER_BIT;

}

namespace gl {
    struct window {
        GLFWwindow *handle;

        int shouldClose() const;
        void pollEvents();
        void swapBuffers() const;
    };

    struct program {
        unsigned int handle;
        std::vector<unsigned int> sh_handles;

        program();
        void attach(shader_type t, const char *path);
        void link() const;
        void use() const;
    };

    struct vertexArray {
    private:
        int m_offset;

    public:
        unsigned int handle;

        vertexArray();
        void bind() const;
        void wrap() const;
        void setAttribute(int location, int length, data_type type);
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
    window newWindow(int width, int height, const char *title);
    void setClearColor(float r, float g, float b, float a);
    void clear(GLuint mask);

    void drawElements(draw_mode mode, int count, data_type type, int indices);

}
