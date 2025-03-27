#pragma once

// class BlockStmt;
// class ExpressionStmt;
class IfStmt;
// class FunctionStmt;
class PrintStmt;
// class ReturnStmt;
class VarStmt;
// class WhileStmt;

template<typename R>
class StmtVisitor {
public:
    ~StmtVisitor() = default;

    //R is any an dhen calling StmtVisitor by constructor,
    //we pass in the specific type 
    // virtual R visitBlockStmt(const BlockStmt& stmt) = 0;
    // virtual R visitExpressionStmt(const ExpressionStmt& stmt) = 0;
    virtual R visitIfStmt(const IfStmt& stmt) = 0;
    // virtual R visitFunctionStmt(const FunctionStmt& stmt) = 0;
    virtual R visitPrintStmt(const PrintStmt& stmt) = 0;
    // virtual R visitReturnStmt(const ReturnStmt& stmt) = 0;
    virtual R visitVarStmt(const VarStmt& stmt) = 0;
    // virtual R visitWhileStmt(const WhileStmt& stmt) = 0;
};