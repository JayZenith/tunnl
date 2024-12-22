#pragma once

#include <memory>
#include "Stmt.h"
#include "StmtVisitor.h"
#include "../Expr/Expr.h"
#include "../Token.h"

class VarStmt : public Stmt {
public: 
    //holds the expression 
    VarStmt(Token name, std::unique_ptr<Expr> expr);
    std::any accept(StmtVisitor<std::any>& visitor) const override;

    const Token& getName() const { return name; }

    bool hasInitializer() const { return expr != nullptr; }
    const Expr& getInitializer() const { return *expr; }

private:
    Token name;
    std::unique_ptr<Expr> expr;

};

