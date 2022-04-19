#include "lexer.h"
#include <stdexcept>
#include "utils.h"

/*!re2c re2c:define:YYCTYPE = "char"; */
/*!maxnmatch:re2c*/

TokenType Lexer::int_types[] =  {TokenType::INT_CONST, TokenType::SYMBOL};
TokenType Lexer::str_types[] =  {TokenType::IDENTIFIER, TokenType::STRING_CONST};

Lexer::Lexer(const std::string &filename): in(filename, /*!max:re2c format="@@";*/+0), token(TokenType::ERROR) {}

TokenType Lexer::tokenType() {
    return token;
}


std::string Lexer::inFile() {
    return in_file;
}

unsigned int Lexer::lineNo() {
    return line_no;
}

int Lexer::intVal() {
    if (contains(int_types, token)) {
        return int_val;
    }
    throw std::logic_error("Cannot access integer value. Value type is string or there is no value.");
}


std::string Lexer::strVal() {
    if (token == TokenType::IDENTIFIER || token == TokenType::STRING_CONST) {
        return str_val;
    }
    throw std::logic_error("Cannot access string value. Value type is integer or there is no value.");
}

bool Lexer::lex() {
    in.tok = in.cur;

    const char *yypmatch[YYMAXNMATCH * 2];
    size_t yynmatch;

    /*!stags:re2c format = 'const char *@@;\n'; */

    /*!re2c
            re2c:yyfill:enable = 1;
            re2c:define:YYCURSOR = in.cur;
            re2c:define:YYMARKER = in.mar;
            re2c:define:YYLIMIT = in.lim;
            re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;
            re2c:posix-captures = 1;

            end = "\x00";

            *   { return false; }
            end {
                return false;
            }

            "# \"" (.+) "\" " ([0-9]+) "\n" {
                in_file = extract_str(yypmatch[2], yypmatch[3]);
                line_no = std::strtoul(extract_str(yypmatch[4], yypmatch[5]).c_str(), nullptr, 10);
                return lex();
            }

            wsp = [ \t\v\r]+;
            "\n" {
                line_no++;
                return lex();
            }
            wsp { return lex(); }

            [{}[\]()\.,;<>+*-/] { set(TokenType::SYMBOL, yych); return true; }
            "++" { token = TokenType::INC; return true; }
            "--" { token = TokenType::DEC; return true; }

            ( "and"|"&"|"&&" )  { set(TokenType::SYMBOL, '&'); return true; }
            ( "or"|"|"|"||" )   { set(TokenType::SYMBOL, '|'); return true; }

            "<="                { token = TokenType::LE_OP; return true; }
            ">="                { token = TokenType::GE_OP; return true; }
            "=="                { token = TokenType::EQ_OP; return true; }
            "!="                { token = TokenType::NE_OP; return true; }
            "!"                { token = TokenType::NEG; return true; }

            "="                 { token = TokenType::ASSIGN_OP; return true; }
            "+="                { token = TokenType::ADD_ASSIGN_OP; return true; }
            "-="                { token = TokenType::SUB_ASSIGN_OP; return true; }
            "*="                { token = TokenType::MULT_ASSIGN_OP; return true; }
            "/="                { token = TokenType::DIV_ASSIGN_OP; return true; }

            "class"             { token = TokenType::CLASS; return true; }
            "static"            { token = TokenType::STATIC; return true; }

            ("int"|"char")      { token = TokenType::INT; return true; }
            "bool"              { token = TokenType::BOOL; return true; }
            "void"              { token = TokenType::VOID; return true; }

            "for"               { token = TokenType::FOR; return true; }
            "while"             { token = TokenType::WHILE; return true; }

            "break"             { token = TokenType::BREAK; return true; }
            "continue"          { token = TokenType::CONTINUE; return true; }
            "return"            { token = TokenType::RETURN; return true; }

            "if"                { token = TokenType::IF; return true; }
            "else"              { token = TokenType::ELSE; return true; }

            id = [a-zA-Z_][a-zA-Z_0-9]{1,256};
            id {
                set(TokenType::IDENTIFIER, extract_str(in.tok, in.cur));
                return true;
            }

            int_const = [1-9][0-9]*;
            int_const {
                set(TokenType::INT_CONST, std::stoi(extract_str(in.tok, in.cur)));
                return true;
            }

            "\"" (.*) "\"" {
                set(TokenType::STRING_CONST, extract_str(yypmatch[2], yypmatch[3]));
                return true;
            }

            "'" (.) "'" {
                set(TokenType::INT_CONST, (*(in.tok+1)) - '0');
                return true;
            }
     */
}

void Lexer::set(TokenType tok, int val) {
    if (contains(int_types, tok)) {
        token = tok;
        int_val = val;
        return;
    }
    throw std::logic_error("Token type and value type do not match.");
}

void Lexer::set(TokenType tok, const std::string &val) {
    if (contains(str_types, tok)) {
        token = tok;
        str_val = val;
        return;
    }
    throw std::logic_error("Token type and value type do not match.");
}
