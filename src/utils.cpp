#include "utils.h"

using std::string;

std::string extract_str(const char *start, const char *end) {
    string i;
    for (const char *f = start;  f < end; ++f) {
        i += *f;
    }

    return i;
}
