#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <vector>

namespace gl {
    enum shaderType {
        e_vertexShader = GL_VERTEX_SHADER,
        e_fragShader = GL_FRAGMENT_SHADER
    };

    enum bufferType {
        e_vertexBuffer = GL_ARRAY_BUFFER,
        e_elementBuffer = GL_ELEMENT_ARRAY_BUFFER,
    };

    enum bufferUsage {
        e_static_draw = GL_STATIC_DRAW
    };

    enum dataType {
        e_float = GL_FLOAT,
        e_uint = GL_UNSIGNED_INT
    };

    enum drawMode {
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
        void attach(shaderType t, const char *path);
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
        void setAttribute(int location, int length, dataType type);
    };

    struct buffer {
        unsigned int handle;
        bufferType btype;

        explicit buffer(bufferType btype);
        void write(GLsizeiptr size, void *data, bufferUsage usage) const;
        template<typename T>
        void write(std::vector<T> data, gl::bufferUsage usage);
    };




}

namespace gl {
    window newWindow(int width, int height, const char *title);
    void setClearColor(float r, float g, float b, float a);
    void clear(GLuint mask);

    void drawElements(drawMode mode, int count, dataType type, int indices);

}
