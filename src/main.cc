#include <iostream>
#include <ogl/opengl.h>
#include <vector>

int main() {
    ogl::context gl = ogl::Init();

    std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };

    ogl::vertex_buffer vbo(ogl::static_draw, vertices);

    ogl::SetClearColor(0.2f, 0.3f, 0.45f);
    while (gl.ShouldContinue()) {

        ogl::Clear(ogl::color_buffer);

        gl.PollEvents();
        gl.SwapBuffers();
    }

    ogl::Terminate();
    return 0;
}
