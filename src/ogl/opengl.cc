#include <ogl/opengl.h>
#include <cstdio>
#include <cstdlib>
#include <util/file.h>

static GLuint create_shader(const char *name, GLenum type) {
    util::file source(name);
    GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, &source.bytes, nullptr);
    glCompileShader(handle);

    int success = 0;
    char infoLog[512];
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(handle, 512, nullptr, infoLog);
        std::fprintf(stderr, "shader compilation failed: file=%s code=%d\n%s\n", name,  success, infoLog);
    }
    else {
        std::printf("shader compilation success: file=%s\n", name);
    }
    return handle;
}

namespace ogl {
    //  Standalone functions
    // ------------------------------------------------------

    ogl::context init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(1080, 607, "Fever", nullptr, nullptr);
        if (window == nullptr) {
            std::fprintf(stderr, "glfw failed to create window\n");
            glfwTerminate();
            std::exit(-1);
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGL()) {
            std::fprintf(stderr, "glad failed to load gl.\n");
            glfwTerminate();
            std::exit(-1);
        }

        context c(window);
        return c;
    }

    void terminate() {
        glfwTerminate();
    }

    void clear(GLbitfield f) {
        glClear(f);
    }

    void set_clear_color(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    int context::should_continue() const {
        return !glfwWindowShouldClose(window);
    }

    void context::poll_events() {
        glfwPollEvents();
    }

    void context::swap_buffers() const {
        glfwSwapBuffers(window);
    }

    vertex_buffer::vertex_buffer(GLenum mode, float data[], GLsizeiptr size) {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ARRAY_BUFFER, handle);
        glBufferData(GL_ARRAY_BUFFER, size, data, mode);
    }


    //  Shader
    // ------------------------------------------------------

    vertex_shader::vertex_shader(const char *name) {
        handle = create_shader(name, GL_VERTEX_SHADER);
    }

    frag_shader::frag_shader(const char *name) {
        handle = create_shader(name, GL_FRAGMENT_SHADER);
    }

    //  Shader Program
    // ------------------------------------------------------

    shader_program::shader_program() {
        handle = glCreateProgram();
    }

    void shader_program::add(vertex_shader shader)  {
        glAttachShader(handle, shader.handle);
        m_shader_handles.push_back(shader.handle);
    }

    void shader_program::add(frag_shader shader)  {
        glAttachShader(handle, shader.handle);
        m_shader_handles.push_back(shader.handle);
    }

    void shader_program::use() const {
        glUseProgram(handle);
    }

    void shader_program::build() const {
        glLinkProgram(handle);

        for(GLuint shader_handle : m_shader_handles) {
            glDeleteShader(shader_handle);

        }
    }

    //  Next thing
    // ------------------------------------------------------

}// namespace ogl