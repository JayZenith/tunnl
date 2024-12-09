#include "../include/lox/Parser.h"

#include "../include/lox/Stmt/PrintStmt.h"

#include <memory>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens))
{}

