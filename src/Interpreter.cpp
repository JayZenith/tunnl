#include "../include/lox/Interpreter.h"


// #include "../include/lox/Lox.h"
#include "../include/lox/Token.h"


#include "../include/lox/Expr/LiteralExpr.h"
#include "../include/lox/Expr/BinaryExpr.h"



#include "../include/lox/Stmt/PrintStmt.h"
#include <any>
#include <cassert>
#include <cmath>
#include <ctime>
#include <memory>
#include <ostream>
#include <iostream>


namespace
{
std::string stringify(const std::any& object)
{
    if (!object.has_value()) {
        return "nil";
    }

    if (object.type() == typeid(bool)) {
        //return std::any_cast<bool>(object) ? "IM-TRUE" : "IM-FALSE";
        return std::any_cast<bool>(object) ? "1" : "0";
    }

    if (object.type() == typeid(double)) {
        double n = std::any_cast<double>(object);
        if (std::trunc(n) == n) { // is int
            return std::to_string((int)n);
        } else {
            return std::to_string(n); // TODO: don't print trailing zeros
        }
    }

    if (object.type() == typeid(std::string)) {
        return std::any_cast<std::string>(object);
    }

    return "";
}
} // end of anonymous namespace






Interpreter::Interpreter() 
{ }

Interpreter::~Interpreter() = default;

void Interpreter::intepret(const std::vector<std::unique_ptr<Stmt>>& statements)
{
   // try {
        for (const auto& ptr : statements) {
            assert(ptr != nullptr);

            execute(*ptr); //due to being pointers 
        }
    // } catch (RuntimeError error) {
    //     Lox::ReportRuntimeError(error);
    // }
}



void Interpreter::execute(const Stmt& stmt)
{
    //PrintStmt is derived from Stmt
    //PrintStmt has an accept function passing
    //in the StmtVisitor an the type of visitor 
    stmt.accept(*this);
}


//MAKE SURE NOT NULL BY CALLING PrintStmt.cpo
std::any Interpreter::evaluate(const Expr& expr)
{

    return expr.accept(*this);
}


std::any Interpreter::visitBinaryExpr(const BinaryExpr& expr){
    //obtain left and right values
    const auto left = evaluate(expr.getLeftExpr());
    const auto right = evaluate(expr.getRightExpr());

    switch (expr.getOp().getType()){
        case TokenType::PLUS:
            if (left.type() == typeid(double) && right.type() == typeid(double)) {
                return std::any_cast<double>(left) + std::any_cast<double>(right);
            }

            if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
                return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
            }
    }
}


std::any Interpreter::visitLiteralExpr(const LiteralExpr& expr)
{
    
    return expr.getLiteral();
}


//with EXECUTE we get here 
std::any Interpreter::visitPrintStmt(const PrintStmt& stmt)
{
    //evaluate makes sure not NULL
    auto value = evaluate(stmt.getExpr());
    //we know what to do here 
    std::cout << stringify(value) << std::endl;
    return {};
}




