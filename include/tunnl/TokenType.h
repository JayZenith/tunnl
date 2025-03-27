#pragma once

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

        TokenEOF
    };
