#include "../include/lox/Parser.h"
#include "../include/lox/Stmt/PrintStmt.h"
#include "../include/lox/Stmt/VarStmt.h"

#include "../include/lox/Token.h"
#include "../include/lox/Expr/LiteralExpr.h"
#include "../include/lox/Expr/BinaryExpr.h"
#include "../include/lox/Expr/VarExpr.h"

#include <iostream>

#include <memory>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens))
{}

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
    // program → declaration* EOF ;
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) { //true if at TokenEOF
        statements.push_back(declaration());
    }

    return statements;
}

std::unique_ptr<Stmt> Parser::declaration()
{
    // declaration → varDecl | statement ;
    if (match(TokenType::VAR)) {
        return varDeclaration();
    }
    return statement();
}

std::unique_ptr<Stmt> Parser::varDeclaration()
{
    // varDeclaration → IDENTIFIER ("=" expression)? ";";
    auto name = consume(TokenType::IDENTIFIER, "Expect variable name");

    std::unique_ptr<Expr> initializer;
    if (match(TokenType::EQUAL)) {
        initializer = expression();
    }

    consume(TokenType::SEMICOLON, "Expect ';' after variable declaration");
    return std::make_unique<VarStmt>(name, std::move(initializer));
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
 
    //match defined in Header 
    if (match(TokenType::PRINT)) {

        return printStatement();
    }

    return expressionStatement(); 

}

std::unique_ptr<Stmt> Parser::printStatement()
{
    // printStmt → "print" expression ";" ;
    //auto assumes type at compile time since 
    //we are not sure what expression is returned 
    auto value = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after value");
    return std::make_unique<PrintStmt>(std::move(value));
}

std::unique_ptr<Stmt> Parser::expressionStatement(){
    //expressionStmt -> expression ";" ;
    auto expr = expression();
    return NULL;
}

std::unique_ptr<Expr> Parser::expression()
{
    // expression → assignment ;
    return assignment();
}

std::unique_ptr<Expr> Parser::assignment()
{
    // assignment → IDENTIFIER "=" assignment | logic_or ;
    auto expr = orExpression();

    //auto expr = call();
    return expr;
}

std::unique_ptr<Expr> Parser::orExpression(){
    auto expr = andExpression();

    return expr;
}

std::unique_ptr<Expr> Parser::andExpression(){
    // logic_and  → equality ( "and" equality )* ;
    auto expr = equality();

    return expr;
}



std::unique_ptr<Expr> Parser::equality(){
    // equality → comparison ( ( "!=" | "==" ) comparison )* ;
    auto expr = comparison();

    return expr;
}

std::unique_ptr<Expr> Parser::comparison(){
    // comparison → addition ( ( ">" | ">=" | "<" | "<=" ) addition )* ;
    auto expr = addition();

    return expr;
}


std::unique_ptr<Expr> Parser::addition(){
    // addition → multiplication ( ( "-" | "+" ) multiplication )* ;
    auto expr = multiplication();
    //Should come back here after returning from arg1
    while (match(TokenType::MINUS, TokenType::PLUS)) {
        auto op = previous();
        auto right = multiplication();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::multiplication(){
    // multiplication → unary ( ( "/" | "*" ) unary )* ;
    auto expr = unary();

    return expr;
}


std::unique_ptr<Expr> Parser::unary(){

    return call();
}

std::unique_ptr<Expr> Parser::call()
{
    // call → primary ( "(" arguments? ")" )* ;
    auto expr = primary();
    // while (true) {
    //     if (match(TokenType::LEFTegg nog_PAREN)) {
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
        //return current token with its adrress of the literal 
        return std::make_unique<LiteralExpr>(previous().getLiteral());
    }

    if (match(TokenType::TRUE)) {
        return std::make_unique<LiteralExpr>(true);
    }

    if (match(TokenType::FALSE)) {
        return std::make_unique<LiteralExpr>(false);
    }

    if (match(TokenType::IDENTIFIER)) {
        return std::make_unique<VarExpr>(previous());
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
    //ELSE THROW ERROR PASSE AS ARG
    //throw error(peek(), message);
    if(message){
        std::cerr << message <<std::endl;
        exit(EXIT_FAILURE);

    }
    return tokens.at(current - 1); //IDK
}