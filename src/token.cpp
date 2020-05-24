#include "token.h"

const std::string cppjlox::Token::NullLiteral = "\0";

std::ostream & operator<<(std::ostream & os, const cppjlox::Token & token) {
    return os << token.getType() << " " << token.getLexeme() << " " << token.getLine();
}