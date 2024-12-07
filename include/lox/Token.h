#pragma once

#include <any>
#include <string>

#include "TokenType.h"


class Token {
public:
    Token(TokenType type, std::string lexeme, int line);
    Token(TokenType type, std::string lexeme, std::any literal, int line);

    TokenType getType() const { return type; }
    const std::string& getText() const { return lexeme; }
    const std::any& getLiteral() const { return literal; }
    int getLine() const { return line; }

    std::string toString() const;
    std::string literalToString() const;

private:
    TokenType type;
    std::string lexeme;
    std::any literal;
    int line;
};
