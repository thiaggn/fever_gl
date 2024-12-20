#include <gl/opengl.h>
#include <panic/gl.h>
#include <util/file.h>
#include <map>

static std::map<gl::dataType, int> type_to_size_map = {
        {gl::dataType::e_float, static_cast<int>(sizeof(float))},
        {gl::dataType::e_uint, static_cast<int>(sizeof(unsigned int))}
};

// ==-==-== window array ==-==--==-==-==-==-==-==

struct gl::window gl::newWindow(int width, int height, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (handle == nullptr) {
        panic::failed_to_create_window();
    }
    glfwMakeContextCurrent(handle);

    glfwSetFramebufferSizeCallback(handle, [](GLFWwindow *window, int w, int h) -> void {
        glViewport(0, 0, w, h);
    });

    if (!gladLoadGL()) {
        panic::failed_to_init_glad();
    }

    struct gl::window window {
        .handle = handle
    };

    return window;
}

int gl::window::shouldClose() const {
    return glfwWindowShouldClose(this->handle);
}

void gl::window::pollEvents() {
    glfwPollEvents();
}

void gl::window::swapBuffers() const {
    glfwSwapBuffers(this->handle);
}

// ==-==-== program array ==-==--==-==-==-==-==-==

gl::program::program() {
    this->handle = glCreateProgram();
}

void gl::program::attach(shaderType t, const char *path) {
    util::file source(path);

    unsigned int sh_handle = glCreateShader(t);
    glShaderSource(sh_handle, 1, &source.bytes, nullptr);
    glCompileShader(sh_handle);

    int success;
    char infoLog[512];
    glGetShaderiv(sh_handle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(sh_handle, 512, nullptr, infoLog);
        panic::failed_to_compile_shader(path);
    }

    glAttachShader(this->handle, sh_handle);
    this->sh_handles.push_back(sh_handle);
}

void gl::program::link() const {
    glLinkProgram(this->handle);

    int success = 0;
    char infoLog[512];
    glGetProgramiv(this->handle, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->handle, 512, nullptr, infoLog);
        panic::failed_to_link_shader_program();
    }

    for (unsigned int sh: this->sh_handles) {
        glDeleteShader(sh);
    }
}

void gl::program::use() const {
    glUseProgram(this->handle);
}

// ==-==-== vertex array ==-==--==-==-==-==-==-==

gl::vertexArray::vertexArray() : handle(0), m_offset(0) {
    glGenVertexArrays(1, &(this->handle));
}

void gl::vertexArray::bind() const {
    glBindVertexArray(this->handle);
}

void gl::vertexArray::setAttribute(int location, int length, dataType type) {
    int total_size = length * type_to_size_map[type];
    void* offset = reinterpret_cast<void*>(this->m_offset);

    glVertexAttribPointer(location, length, type, false, total_size, offset);
    glEnableVertexAttribArray(location);
    this->m_offset += total_size;
}
void gl::vertexArray::wrap() const {
    glBindBuffer(gl::bufferType::e_vertexBuffer, 0);
    glBindVertexArray(0);
}

// ==-==-== buffer ==-==--==-==-==-==-==-==-==-==

gl::buffer::buffer(gl::bufferType btype) : handle(0) {
    this->btype = btype;
    glGenBuffers(1, &this->handle);
}

void gl::buffer::write(GLsizeiptr size, void *data, gl::bufferUsage usage) const {
    glBindBuffer(btype, this->handle);     // Associa o buffer ao alvo
    glBufferData(btype, size, data, usage);// Usa o alvo (btype), não o handle
}

template<typename T>
void gl::buffer::write(std::vector<T> data, gl::bufferUsage usage) {
    glBindBuffer(btype, this->handle);                               // Associa o buffer ao alvo
    glBufferData(btype, data.size() * sizeof(T), data.data(), usage);// Usa o alvo (btype)
}

// ==-==-== functions ==-==--==-==-==-==-==-==

void gl::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void gl::clear(GLuint mask) {
    glClear(mask);
}

void gl::drawElements(drawMode mode, int count, dataType type, int indices) {
    glDrawElements(mode, count, type, reinterpret_cast<void*>(indices));
}