#ifndef SHERLOCK_LEXER_H
#define SHERLOCK_LEXER_H

#include "input.h"
#include <string>

enum class TokenType {
    ERROR = 0,
    SYMBOL,
    INT_CONST,
    STRING_CONST,
    IDENTIFIER,
    INC, DEC, // ++, --
    LE_OP, GE_OP, EQ_OP, NE_OP, NEG, // <=, >=, ==, !
    ASSIGN_OP, ADD_ASSIGN_OP, SUB_ASSIGN_OP, MULT_ASSIGN_OP, DIV_ASSIGN_OP, // =, +=, -=, *=, /=
    INT, BOOL, VOID,
    CLASS, STATIC,
    BREAK, CONTINUE, RETURN,
    IF, ELSE,
    FOR, WHILE
};

class Lexer {
private:
    struct input_t in;
    TokenType token;
    std::string in_file;
    unsigned int line_no;
    int int_val;
    std::string str_val;

    void set(TokenType tok, int val);
    void set(TokenType tok, const std::string &val);

    static TokenType int_types[];
    static TokenType str_types[];

public:
    explicit Lexer(const std::string &filename);

    TokenType tokenType();
    std::string inFile();
    unsigned int lineNo();
    int intVal();
    std::string strVal();

    bool lex();

};

#endif //SHERLOCK_LEXER_H
