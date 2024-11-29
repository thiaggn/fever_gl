#include <ogl/opengl.h>
#include <cstdio>
#include <cstdlib>
#include <util/file.h>

namespace ogl {

    context Init() {
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

    void Terminate() {
        glfwTerminate();
    }

    void Clear(GLbitfield f) {
        glClear(f);
    }

    void SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    int context::ShouldContinue() const {
        return !glfwWindowShouldClose(window);
    }

    void context::PollEvents() {
        glfwPollEvents();
    }

    void context::SwapBuffers() const {
        glfwSwapBuffers(window);
    }

    vertex_buffer::vertex_buffer(GLenum mode, std::vector<float> vertex): handle(0) {
        glGenBuffers(1, &handle);
        glBindBuffer(GL_ARRAY_BUFFER, handle);
        glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(vertex.size()), vertex.data(), mode);
    }

    vertex_shader::vertex_shader(const char *name){
        util::file source(name);

        handle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(handle, 1, nullptr, nullptr);
    }
}