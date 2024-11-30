#include <ogl/opengl.h>

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
};

int main() {
    ogl::context gl = ogl::init();
    ogl::vertex_shader vshader("../assets/vertex.glsl");
    ogl::frag_shader fshader("../assets/frag.glsl");

    ogl::shader_program sp;
    sp.add(vshader);
    sp.add(fshader);
    sp.build();
    sp.use();

    ogl::set_clear_color(0.2f, 0.3f, 0.45f);

    while (gl.should_continue()) {
        ogl::clear(ogl::color_buffer);

        gl.poll_events();
        gl.swap_buffers();
    }

    ogl::terminate();
    return 0;
}
