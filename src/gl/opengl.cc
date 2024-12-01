#include <gl/opengl.h>
#include <panic/gl.h>
#include <util/file.h>
#include <map>

static std::map<gl::data_type, int> type_to_size_map = {
        {gl::data_type::e_float, static_cast<int>(sizeof(float))},
        {gl::data_type::e_uint, static_cast<int>(sizeof(unsigned int))}
};


// ==-==-== window array ==-==--==-==-==-==-==-==

struct gl::window gl::new_window(int width, int height, const char *title) {
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

int gl::window::should_close() const {
    return glfwWindowShouldClose(this->handle);
}

void gl::window::poll_events() {
    glfwPollEvents();
}

void gl::window::swap_buffers() const {
    glfwSwapBuffers(this->handle);
}

// ==-==-== program array ==-==--==-==-==-==-==-==

gl::program::program() {
    this->handle = glCreateProgram();
}

void gl::program::attach(gl::shader_type t, const char *path) {
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

gl::vertex_array::vertex_array() : handle(0), m_offset(0) {
    glGenVertexArrays(1, &(this->handle));
}

void gl::vertex_array::bind() const {
    glBindVertexArray(this->handle);
}

void gl::vertex_array::set_attribute(int location, int length, data_type type) {
    int total_size = length * type_to_size_map[type];
    void* offset = reinterpret_cast<void*>(this->m_offset);

    glVertexAttribPointer(location, length, type, false, total_size, offset);
    glEnableVertexAttribArray(location);
    this->m_offset += total_size;
}
void gl::vertex_array::wrap() const {
    glBindBuffer(gl::buffer_type::e_vertex_buffer, 0);
    glBindVertexArray(0);
}

// ==-==-== buffer ==-==--==-==-==-==-==-==-==-==

gl::buffer::buffer(gl::buffer_type btype) : handle(0) {
    this->btype = btype;
    glGenBuffers(1, &this->handle);
}

void gl::buffer::write(GLsizeiptr size, void *data, gl::buffer_usage usage) const {
    glBindBuffer(btype, this->handle);     // Associa o buffer ao alvo
    glBufferData(btype, size, data, usage);// Usa o alvo (btype), não o handle
}

template<typename T>
void gl::buffer::write(std::vector<T> data, gl::buffer_usage usage) {
    glBindBuffer(btype, this->handle);                               // Associa o buffer ao alvo
    glBufferData(btype, data.size() * sizeof(T), data.data(), usage);// Usa o alvo (btype)
}

// ==-==-== functions ==-==--==-==-==-==-==-==

void gl::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void gl::clear(GLuint mask) {
    glClear(mask);
}

void gl::draw_elements(draw_mode mode, int count, data_type type, int indices) {
    glDrawElements(mode, count, type, reinterpret_cast<void*>(indices));
}