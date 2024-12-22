#pragma once

#include <any>
#include <iosfwd>
#include <memory>
#include <vector>

#include "Expr/ExprVisitor.h"
#include "Stmt/StmtVisitor.h"

#include "Token.h"

class Environment;

class Expr;
class Stmt;

//deriving from Expr and Stmt Visitors 
//Derived class must override virtual classes in base class
class Interpreter : public ExprVisitor<std::any>, public StmtVisitor<std::any> {
public:
    Interpreter(std::ostream& out);
    ~Interpreter(); // for forward declaration of Environment
    void intepret(const std::vector<std::unique_ptr<Stmt>>& statements);

    Environment& getGlobalsEnvironment();

    void execute(const Stmt& stmt);
    // void executeBlock(const std::vector<std::unique_ptr<Stmt>>& statements,
    //                   std::unique_ptr<Environment> env);
    std::any evaluate(const Expr& expr);

private:
    bool isEqual(const std::any& left, const std::any& right) const;


    void checkNumberOperands(const Token& op, const std::any& left, const std::any& right) const;


    std::any visitBinaryExpr(const BinaryExpr& expr) override;
    std::any visitLiteralExpr(const LiteralExpr& expr) override;
    std::any visitPrintStmt(const PrintStmt& stmt) override;
    std::any visitVarExpr(const VarExpr& expr) override;

    std::any visitVarStmt(const VarStmt& stmt) override;

    //data
    std::unique_ptr<Environment> globals;
    Environment* globalEnvironment;
    std::unique_ptr<Environment> environment; // current environment

    class EnterEnviromentGuard {
    public:
        EnterEnviromentGuard(Interpreter& i, std::unique_ptr<Environment> env);
        ~EnterEnviromentGuard();

    private:
        Interpreter& i;
        std::unique_ptr<Environment> previous;
    };
    std::ostream& out;
};

