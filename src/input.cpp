#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <stdexcept>
#include <cstring>
#include "input.h"


input_t::input_t(const std::string &f, int max_fill)
        : buf(std::make_unique<unsigned char[]>(SIZE * max_fill)),
          lim(buf.get() + SIZE),
          cur(lim),
          mar(lim),
          tok(lim),
          max_fill(max_fill), file(fopen(f.c_str(), "r")) {
    if (file == nullptr) {
        throw std::invalid_argument("file not found.");
    }
}

bool input_t::fill(size_t need) {
    if (eof) {
        return false;
    }

    const size_t free = tok - buf.get();
    if (free < need) {
        return false;
    }

    memmove(buf.get(), tok, lim - tok);

    lim -= free;
    cur -= free;
    mar -= free;
    tok -= free;
    lim += fread(lim, 1, free, file);

    if (lim < buf.get() + SIZE) {
        eof = true;
        memset(lim, 0, max_fill);
        lim += max_fill;
    }

    return true;
}

input_t::~input_t() {
    fclose(file);
}
