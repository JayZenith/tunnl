#pragma once

#include <optional>
#include <iostream>
#include <vector>
#include <string>
#include <map>

enum class TokenType{
    // Single-character TokenType.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,  SEMICOLON, 
    DOT, MINUS, PLUS, SLASH, STAR, COMMA,

    // One or two character TokenType.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    //literals.
    NUMBER, IDENTIFIER, STRING,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, LET, VAR, WHILE,
    LEAVE, 
    };

struct Token{
    TokenType type;
    std::optional<std::string> value {}; 
    int theLine; //hold lne where instruction is 
};

std::map<std::string, TokenType> HashMap = 
{ {"leave", TokenType::LEAVE},
  {"and", TokenType::AND},
  {"class", TokenType::CLASS},
  {"else", TokenType::ELSE},
  {"false", TokenType::FALSE},
  {"fun", TokenType::FUN},
  {"for", TokenType::FOR},
  {"if", TokenType::IF},
  {"nil", TokenType::NIL},
  {"or", TokenType::OR},
  {"print", TokenType::PRINT},
  {"return", TokenType::RETURN},
  {"super", TokenType::SUPER},
  {"this", TokenType::THIS},
  {"true", TokenType::TRUE},
  {"let", TokenType::LET},
  {"var", TokenType::VAR},
  {"while", TokenType::WHILE},
};
