#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "token.h"

namespace cppjlox {

class Scanner {
private:
    std::string source;
    std::vector<Token> tokens {};

    int start = 0;
    int current = 0;
    int line = 1;

    const std::unordered_map<std::string, TokenType> keywords {
        {"and", AND},
        {"class", CLASS},
        {"else", ELSE},
        {"false", FALSE},
        {"for", FOR},
        {"fun", FUN},
        {"if", IF},
        {"nil", NIL},
        {"or", OR},
        {"print", PRINT},
        {"return", RETURN},
        {"super", SUPER},
        {"this", THIS},
        {"true", TRUE},
        {"var", VAR},
        {"while", WHILE}
    };

    bool isAtEnd();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, Token::LiteralT value);
    bool match(char expected);
    char peek();
    char peekNext();
    void string();
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    void number();
    void identifier();
    void scanToken();

public:
    Scanner(std::string source) : source(source) {};
    ~Scanner(){};

    std::vector<Token> scanTokens();
};

}