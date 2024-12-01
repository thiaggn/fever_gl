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
    gl::window window = gl::newWindow(800, 500, "Fever");

    gl::program prog;
    prog.attach(gl::e_vertexShader, "../assets/vertex.glsl");
    prog.attach(gl::e_fragShader, "../assets/frag.glsl");
    prog.link();

    gl::vertexArray vao;
    vao.bind();

    gl::buffer vbo(gl::e_vertexBuffer);
    vbo.write(sizeof(vertices), vertices, gl::e_static_draw);

    gl::buffer ebo(gl::e_elementBuffer);
    ebo.write(sizeof(indices), indices,  gl::e_static_draw);

    vao.setAttribute(0, 3, gl::e_float);
    vao.wrap();

    gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose()) {
        gl::clear(gl::c_colorBuffer);

        prog.use();
        vao.bind();

        gl::drawElements(gl::e_triangles, 6, gl::e_uint, 0);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
