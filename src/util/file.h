#pragma once

namespace util {
    struct file {
        char* bytes;
        long size;

        explicit file(const char *name);
        ~file();
    };
}