#ifndef SHERLOCK_INPUT_H
#define SHERLOCK_INPUT_H

#include <cstdio>
#include <memory>
#include <string>

static const size_t SIZE = 64 * 1024;

struct input_t {
    std::unique_ptr<char[]> buf;
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    bool eof = false;
    int max_fill;

    FILE *const file;

    input_t(const std::string &f, int max_fill);
    bool fill(size_t need);
    ~input_t();
};

#endif //SHERLOCK_INPUT_H
