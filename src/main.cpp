#include "preprocessor.h"
#include "lexer.h"
#include <iostream>
#include <fstream>

int main() {
    std::ofstream preprocessed("compile.shr", std::ofstream::out);

    preprocess("test.shr", preprocessed);
    preprocessed.close();

    Lexer lexer("compile.shr");
    while (lexer.lex()) {
        std::cout << lexer.inFile() << ":" << lexer.lineNo() << "  " << (int)lexer.tokenType() << '\n';
    }
}
