#pragma once

#include <string>
#include <iostream>
#include <variant>
#include "tokenTypes.h"

namespace cppjlox
{

class Token {
public:
    const static std::string NullLiteral;
    using LiteralT = std::variant<std::string, double>;

private:
    const TokenType type;
    const std::string lexeme;
    const LiteralT literal;
    const int line;

public:
    Token(TokenType type, std::string lexeme, LiteralT literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line){};
    ~Token(){};

    TokenType getType() const {
        return type;
    }

    std::string getLexeme() const {
        return lexeme;
    }

    LiteralT getLiteral() const {
        return literal;
    }

    int getLine() const {
        return line;
    }
};

}

std::ostream & operator<<(std::ostream & os, const cppjlox::Token & token);
