#include "file.h"
#include <cstdio>
#include <cstdlib>

namespace util {
    file::file(const char *name) {
        // abre o arquivo e determina o tamanho
        std::FILE *file = std::fopen(name, "rb");

        if (file == nullptr) {
            std::fprintf(stderr, "erro: a abertura do arquivo \'%s\' nao foi realizada.\n", name);
            std::exit(-1);
        }

        std::fseek(file, 0, SEEK_END);// move a agulha até o final do arquivo
        size = std::ftell(file);      // obtém a posição da agulha no arquivo
        std::rewind(file);            // repositiona a agulha para o início

        // copia os dados para o buffer
        bytes = (char *) std::malloc(size + 1);
        std::fread(bytes, size, 1, file);
        bytes[size] = '\0';

        std::fclose(file);
    }

    file::~file() {
        std::free((void *) bytes);
        bytes = nullptr;
    }

}// namespace util