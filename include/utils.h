#ifndef SHERLOCK_UTILS_H
#define SHERLOCK_UTILS_H

#include <string>

#define MAX_ID 256

std::string extract_str(const char *start, const char *end);

template<class C, typename T>
bool contains(C&& c, T e) { return std::find(std::begin(c), std::end(c), e) != std::end(c); };

#endif //SHERLOCK_UTILS_H
