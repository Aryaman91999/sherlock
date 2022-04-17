#ifndef SHERLOCK_INPUT_H
#define SHERLOCK_INPUT_H

#include <cstdio>
#include <memory>

static const size_t SIZE = 64 * 1024;

struct input_t {
    std::unique_ptr<unsigned char[]> buf;
    unsigned char *lim;
    unsigned char *cur;
    unsigned char *mar;
    unsigned char *tok;
    bool eof = false;
    int max_fill;

    FILE *const file;

    input_t(const std::string &f, int max_fill);
    bool fill(size_t need);
    ~input_t();
};

#endif //SHERLOCK_INPUT_H
