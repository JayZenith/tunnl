#include "../include/tunnl/Interpreter.h"
#include "../include/tunnl/Environment.h"

// #include "../include/lox/Lox.h"
#include "../include/tunnl/Token.h"

#include "../include/tunnl/Expr/LiteralExpr.h"
#include "../include/tunnl/Expr/BinaryExpr.h"
#include "../include/tunnl/Expr/VarExpr.h"

#include "../include/tunnl/Stmt/PrintStmt.h"
#include "../include/tunnl/Stmt/IfStmt.h"

#include "../include/tunnl/Stmt/VarStmt.h"
#include <any>
#include <cassert>
#include <cmath>
#include <ctime>
#include <memory>
#include <ostream>
#include <iostream>

namespace
{
    std::string stringify(const std::any &object)
    {
        if (!object.has_value())
        {
            return "nil";
        }

        if (object.type() == typeid(bool))
        {
            // return std::any_cast<bool>(object) ? "IM-TRUE" : "IM-FALSE";
            return std::any_cast<bool>(object) ? "True" : "False";
        }

        if (object.type() == typeid(double))
        {
            double n = std::any_cast<double>(object);
            if (std::trunc(n) == n)
            { // is int
                return std::to_string((int)n);
            }
            else
            {
                return std::to_string(n); // TODO: don't print trailing zeros
            }
        }

        if (object.type() == typeid(std::string))
        {
            return std::any_cast<std::string>(object);
        }

        return "";
    }
} // end of anonymous namespace

Interpreter::Interpreter(std::ostream &out) : out(out), globals(std::make_unique<Environment>()), globalEnvironment(globals.get())
{
    globals->define("clock", NULL);
    environment = std::move(globals);
}

Interpreter::~Interpreter() = default;

void Interpreter::intepret(const std::vector<std::unique_ptr<Stmt>> &statements)
{
    // try {
    for (const auto &ptr : statements)
    {
        assert(ptr != nullptr);

        execute(*ptr); // due to being pointers
    }
    // } catch (RuntimeError error) {
    //     Lox::ReportRuntimeError(error);
    // }
}

void Interpreter::checkNumberOperands(const Token &op, const std::any &left,
                                      const std::any &right) const
{
    if (left.type() == typeid(double) && right.type() == typeid(double))
    {
        return;
    }

    // throw RuntimeError(op, "Operands must be numbers");
}

void Interpreter::execute(const Stmt &stmt)
{
    // PrintStmt is derived from Stmt
    // PrintStmt has an accept function passing
    // in the StmtVisitor an the type of visitor
    stmt.accept(*this);
}

// MAKE SURE NOT NULL BY CALLING PrintStmt.cpo
std::any Interpreter::evaluate(const Expr &expr)
{

    return expr.accept(*this);
}

bool Interpreter::isTruthy(const std::any &object) const
{
    if (!object.has_value())
    {
        return false;
    }

    if (object.type() == typeid(bool))
    {
        return std::any_cast<bool>(object);
    }

    return true;
}

bool Interpreter::isEqual(const std::any &left, const std::any &right) const
{
    // nil is only equal to nil
    if (!left.has_value() && !right.has_value())
    {
        return true;
    }
    if (!left.has_value())
    {
        return false;
    }

    if (left.type() != right.type())
    {
        return false;
    }

    if (left.type() == typeid(bool))
    {
        return std::any_cast<bool>(left) == std::any_cast<bool>(right);
    }

    if (left.type() == typeid(double))
    {
        return std::any_cast<double>(left) == std::any_cast<double>(right);
    }

    if (left.type() == typeid(std::string))
    {
        return std::any_cast<std::string>(left) == std::any_cast<std::string>(right);
    }

    return false;
}

std::any Interpreter::visitBinaryExpr(const BinaryExpr &expr)
{
    // obtain left and right values
    const auto left = evaluate(expr.getLeftExpr());
    const auto right = evaluate(expr.getRightExpr());

    switch (expr.getOp().getType())
    {
        // equality operators
    case TokenType::BANG_EQUAL:
        return !isEqual(left, right);
    case TokenType::EQUAL_EQUAL:
        return isEqual(left, right);
    // comparison operators
    case TokenType::GREATER:
        checkNumberOperands(expr.getOp(), left, right);
        return std::any_cast<double>(left) > std::any_cast<double>(right);
    case TokenType::GREATER_EQUAL:
        checkNumberOperands(expr.getOp(), left, right);
        return std::any_cast<double>(left) >= std::any_cast<double>(right);
    case TokenType::LESS:
        checkNumberOperands(expr.getOp(), left, right);
        return std::any_cast<double>(left) < std::any_cast<double>(right);
    case TokenType::LESS_EQUAL:
        checkNumberOperands(expr.getOp(), left, right);
        return std::any_cast<double>(left) <= std::any_cast<double>(right);
    case TokenType::PLUS:
        if (left.type() == typeid(double) && right.type() == typeid(double))
        {
            return std::any_cast<double>(left) + std::any_cast<double>(right);
        }

        if (left.type() == typeid(std::string) && right.type() == typeid(std::string))
        {
            return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
        }
    }
}

std::any Interpreter::visitLiteralExpr(const LiteralExpr &expr)
{
    return expr.getLiteral();
}

std::any Interpreter::visitIfStmt(const IfStmt &stmt)
{
    if (isTruthy(evaluate(stmt.getCondition())))
    {
        execute(stmt.getThenBranch());
    }
    else
    {
        if (stmt.hasElseBranch())
        {
            execute(stmt.getElseBranch());
        }
    }
    return {};
}

// with EXECUTE we get here
std::any Interpreter::visitPrintStmt(const PrintStmt &stmt)
{
    // evaluate makes sure not NULL
    auto value = evaluate(stmt.getExpr());
    // we know what to do here
    std::cout << stringify(value) << std::endl;
    return {};
}

std::any Interpreter::visitVarExpr(const VarExpr &expr)
{
    assert(environment != nullptr);
    return environment->get(expr.getName());
}

std::any Interpreter::visitVarStmt(const VarStmt &stmt)
{
    std::any value;
    if (stmt.hasInitializer())
    {
        value = evaluate(stmt.getInitializer());
    }

    assert(environment != nullptr);
    environment->define(stmt.getName().getText(), value);
    return {};
}
