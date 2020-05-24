#include "scanner.h"
#include "error.h"

namespace cppjlox
{

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    current++;
    return source[current - 1];
}

void Scanner::addToken(TokenType type) {
    addToken(type, Token::NullLiteral);
}

void Scanner::addToken(TokenType type, Token::LiteralT value) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, value, line);
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    // Unterminated string
    if (isAtEnd()) {
        Error::report(line, "", "Unterminated string.");
        return;
    }

    // Consume the closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, start - current);
    addToken(STRING, value);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    addToken(NUMBER, std::stod(source.substr(start, start - current)));
}

void Scanner::identifier() {
    while(isAlphaNumeric(peek())) advance();

    // See if we found a reserved word
    std::string text = source.substr(start, current - start);
    TokenType type;
    auto foundKeyword = keywords.find(text);
    if (foundKeyword == keywords.end()) {
        type = IDENTIFIER;
    } else {
        type = foundKeyword->second;
    }
    
    addToken(type);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
    case '(': addToken(LEFT_PAREN); break;
    case ')': addToken(RIGHT_PAREN); break;
    case '{': addToken(LEFT_BRACE); break;
    case '}': addToken(RIGHT_BRACE); break;
    case ',': addToken(COMMA); break;
    case '.': addToken(DOT); break;
    case '-': addToken(MINUS); break;
    case '+': addToken(PLUS); break;
    case ';': addToken(SEMICOLON); break;
    case '*': addToken(STAR); break;
    case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
    case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
    case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
    case '/':
        if (match('/')) {
            // Skip until the end of the line
            while (peek() != '\n' && !isAtEnd()) advance();
        } else {
            addToken(SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace
        break;
    case '\n':
        line++;
        break;
    case '"': string(); break;
    
    default:
        if (isDigit(c)) {
            number();
        } else if(isAlpha(c)) {
            identifier();
        } else {
            Error::report(line, "", "Unexpected character.");
        }
        break;
    }
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(EOFILE, "", Token::NullLiteral, line);
    return tokens;
}

}
