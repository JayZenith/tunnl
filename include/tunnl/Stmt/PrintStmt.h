#pragma once

#include <memory>
#include "Stmt.h"
#include "StmtVisitor.h"
#include "../Expr/Expr.h"

class PrintStmt : public Stmt {
public: 
    //holds the expression 
    PrintStmt(std::unique_ptr<Expr> expr);
    std::any accept(StmtVisitor<std::any>& visitor) const override;
    const Expr& getExpr() const { return *expr; }

private:
    std::unique_ptr<Expr> expr;

};

