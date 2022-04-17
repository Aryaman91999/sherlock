#include "preprocessor.h"

int main() {
    try {
        preprocess("test.shr", std::cout);
    } catch (std::invalid_argument const&) {
        std::cerr << "file \"" << "test.shr" << "\" not found.\n";
    }
}
