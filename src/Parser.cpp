#include "../include/lox/Parser.h"

#include "../include/lox/Stmt/PrintStmt.h"

#include "../include/lox/Lox.h"

#include "../include/lox/Expr/VarExpr.h"
#include "../include/lox/Expr/LiteralExpr.h"
#include <iostream>

#include <memory>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens))
{}

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
    // program → declaration* EOF ;
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

std::unique_ptr<Stmt> Parser::declaration()
{
    return statement();
}

std::unique_ptr<Stmt> Parser::statement()
{
    // statement → exprStmt
    //             | forStmt
    //             | ifStmt
    //             | printStmt
    //             | returnStmt
    //             | whileStmt
    //             | block;
 
    if (match(TokenType::PRINT)) {
        std::cout << "here" << std::endl;

        return printStatement();
    }

    return NULL; //shouldnt reach here

    //return expressionStatement();
}

std::unique_ptr<Stmt> Parser::printStatement()
{
    // printStmt → "print" expression ";" ;
    auto value = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value");
    return std::make_unique<PrintStmt>(std::move(value));
}

std::unique_ptr<Expr> Parser::expression()
{
    // expression → assignment ;
    return assignment();
}

std::unique_ptr<Expr> Parser::assignment()
{
    // assignment → IDENTIFIER "=" assignment | logic_or ;
    auto expr = call();
    return expr;
}

std::unique_ptr<Expr> Parser::call()
{
    // call → primary ( "(" arguments? ")" )* ;
    auto expr = primary();
    // while (true) {
    //     if (match(TokenType::LEFT_PAREN)) {
    //         expr = finishCall(std::move(expr));
    //     } else {
    //         break;
    //     }
    // }
    return expr;
}

std::unique_ptr<Expr> Parser::primary()
{
    // primary        → NUMBER | STRING | "false" | "true" | "nil"
    //                  IDENTIFIER | "(" expression ")" ;
    if (match(TokenType::NUMBER, TokenType::STRING)) {
        return std::make_unique<LiteralExpr>(previous().getLiteral());
    }

    return NULL;
}

bool Parser::check(TokenType type) const
{
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

Token Parser::advance()
{
    if (!isAtEnd()) {
        ++current;
    }
    return previous();
}

Token Parser::peek() const
{
    return tokens.at(current);
}



Token Parser::previous() const
{
    return tokens.at(current - 1);
}

bool Parser::isAtEnd() const
{
    return peek().getType() == TokenType::TokenEOF;
}

Token Parser::consume(TokenType type, const char* message)
{
    if (check(type)) {
        return advance();
    }

    //throw error(peek(), message);
    return tokens.at(current - 1); //IDK
}