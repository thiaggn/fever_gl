#pragma once
#include <cstdio>
#include <cstdlib>

namespace panic {

    [[noreturn]]
    void failed_to_create_window() {
        std::fprintf(stderr, "erro: glfw falhou em criar a janela.\n");
        glfwTerminate();
        std::exit(-1);
    }

    [[noreturn]]
    void failed_to_init_glad() {
        std::fprintf(stderr, "erro: glad falhou em ser carregado.\n");
        glfwTerminate();
        std::exit(-1);
    }

    [[noreturn]]
    void failed_to_compile_shader(const char *name) {
        std::fprintf(stderr, "erro: gl falhou em compilar shader no diretorio \"%s\"\n",name);
        glfwTerminate();
        std::exit(-1);
    }

    [[noreturn]]
    void failed_to_link_shader_program() {
        std::fprintf(stderr, "erro: gl falhou em unir shader program\n");
        glfwTerminate();
        std::exit(-1);
    }
}