#include "file.h"
#include <cstdio>
#include <cstdlib>

namespace util {
    file::file(const char *name) {
        // abre o arquivo e determina o tamanho
        std::FILE *file = std::fopen(name, "r");
        std::fseek(file, SEEK_END, 0);  // move a agulha até o final do arquivo
        size = std::ftell(file);                      // obtém a posição da agulha no arquivo
        std::rewind(file);                            // repositiona a agulha para o início

        // copia os dados para o buffer
        bytes = (char*) std::malloc(size + 1);
        size_t bytes_read = std::fread(bytes,  size, 1, file);

        if (bytes_read == 1) {
            std::fprintf(stderr, "");
        }

        std::fclose(file);
    }

    file::~file() {
        std::free(bytes);
        bytes = nullptr;
    }
}