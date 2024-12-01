#include <gl/opengl.h>

float vertices[] = {
        0.5f, 0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,// bottom left
        -0.5f, 0.5f, 0.0f  // top left
};
unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3,// first Triangle
        1, 2, 3 // second Triangle
};

int main() {
    gl::window window = gl::new_window(800, 500, "Fever");

    gl::program prog;
    prog.attach(gl::e_vertex_shader, "../assets/vertex.glsl");
    prog.attach(gl::e_fragmt_shader, "../assets/frag.glsl");
    prog.link();

    gl::vertex_array vao;
    vao.bind();

    gl::buffer vbo(gl::e_vertex_buffer);
    vbo.write(sizeof(vertices), vertices, gl::e_static_draw);

    gl::buffer ebo(gl::e_element_buffer);
    ebo.write(sizeof(indices), indices,  gl::e_static_draw);

    vao.set_attribute(0, 3, gl::e_float);
    vao.wrap();

    gl::set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.should_close()) {
        gl::clear(gl::c_color_buffer);

        prog.use();
        vao.bind();

        gl::draw_elements(gl::e_triangles, 6, gl::e_uint, 0);


        window.swap_buffers();
        window.poll_events();
    }

    return 0;
}
