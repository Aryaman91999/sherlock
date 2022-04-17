#include "utils.h"

using std::string;

std::string extract_match(const unsigned char *start, const unsigned char *end) {
    string i;
    for (const unsigned char *f = start;  f < end; ++f) {
        i += *f;
    }

    return i;
}
